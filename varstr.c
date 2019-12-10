/**
 *  @file varstr.c
 *  @version 1.3.0-dev0
 *  @date Tue Dec 10 13:43:59 CST 2019
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "varstr.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

struct varstr {
   unsigned    size;
   unsigned    extend;
   char       *x;
};

struct varstr *
varstr_new(void)
{
   struct varstr *tp;

   tp = (struct varstr *) malloc(sizeof(struct varstr));
   if (_IS_NULL(tp))
      return NULL;

   tp->x = (char *) calloc(1, sizeof(char));
   tp->size = 0;
   tp->extend = 0;

   return tp;
}

int
varstr_free(struct varstr **pp)
{
   _FREE((*pp)->x);
   _FREE(*pp);
   *pp = NULL;

   return 0;
}

const char *
varstr_version(void)
{
   return "1.3.0-dev0";
}

int
varstr_buffersize(struct varstr *p, unsigned size, unsigned extend)
{
   char       *cp;

   if (size > p->size) {

      cp = realloc(p->x, size * sizeof(char));

      if (_IS_NULL(cp))
         return 1;

      p->x = cp;
      p->size = size;
   }

   p->extend = (extend > 0 ? extend : 1);

   return 0;
}

void
varstr_cat(struct varstr *p, char *x)
{
   unsigned    need = 1 + strlen(p->x) + strlen(x);

   if (need >= p->size) {
      p->x = (char *) realloc(p->x, (need + p->extend) * sizeof(char));
      if (_IS_NULL(p->x)) {
         fprintf(stderr, "[ERROR] %s %d: Cannot allocate memory\n", __FILE__, __LINE__);
         exit(1);
      }

      p->size = need + p->extend;
   }

   strcat(p->x, x);
}

void
varstr_catc(struct varstr *p, char x)
{
   unsigned    len = strlen(p->x);
   unsigned    need = 2 + len;

   if (need >= p->size) {
      p->x = (char *) realloc(p->x, (need + p->extend) * sizeof(char));
      if (_IS_NULL(p->x)) {
         fprintf(stderr, "[ERROR] %s %d: Cannot allocate memory\n", __FILE__, __LINE__);
         exit(1);
      }
      p->size = need + p->extend;
   }

   (p->x)[len] = x;
   (p->x)[len + 1] = '\0';
}

void
varstr_chomp(struct varstr *p)
{
   char       *cp = varstr_str(p);
   int         i = strlen(cp);

   while (i > 0) {
      i -= 1;
      if (!isspace(cp[i]))
         break;
   }

   cp[i + 1] = '\0';
}

void
varstr_compact(struct varstr *p)
{
   int         i, j;
   int         len = strlen(p->x);

   for (i = 0, j = 0; i < len; i++) {

      if (isspace((p->x)[i]))
         continue;

      (p->x)[j] = (p->x)[i];

      j += 1;
   }

   (p->x)[j] = '\0';
}

void
varstr_empty(struct varstr *p)
{
   (p->x)[0] = '\0';
}

unsigned
varstr_extend(struct varstr *p, unsigned extend)
{
   if (extend > 0)
      p->extend = extend;

   return p->extend;
}

unsigned
varstr_init(struct varstr *p, unsigned extend)
{
   return varstr_extend(p, extend);
}

void
varstr_lrtrim(struct varstr *g)
{
   char       *cp = g->x;
   unsigned    i = 0, j = 0;
   unsigned    len = strlen(cp);

   while (i < len) {
      if (!isspace(cp[i]))
         break;
      i += 1;
   }

   while (i < len) {
      cp[j] = cp[i];
      i += 1;
      j += 1;
   }

   cp[j] = '\0';

   varstr_chomp(g);
}

char       *
varstr_str(struct varstr *p)
{
   return p->x;
}

char       *
varstr_to_s(struct varstr *p)
{
   char       *str = (char *) malloc((1 + strlen(p->x)) * sizeof(char));
   return strcpy(str, p->x);
}

#undef _IS_NULL
#undef _FREE
