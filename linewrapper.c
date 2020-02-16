/**
 *  @file linewrapper.c
 *  @version 0.1.0-dev0
 *  @date Sun Feb 16, 2020 04:51:18 PM CST
 *  @copyright 2019-2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <string.h>
#include <ctype.h>
#include "linewrapper.h"
#include "varstr.h"

#ifdef  IS_NULL
#undef  IS_NULL
#endif
#define IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  FREE
#undef  FREE
#endif
#define FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

struct linewrapper {
   struct varstr *s;
};

struct linewrapper *
lwrap_new(void)
{
   struct linewrapper *tp;

   tp = (struct linewrapper *) malloc(sizeof(struct linewrapper));
   if (IS_NULL(tp))
      return NULL;

   tp->s = NULL;

   return tp;
}

void
lwrap_free(struct linewrapper **pp)
{
   if (!IS_NULL((*pp)->s))
      varstr_free(&(*pp)->s);
   FREE(*pp);
   *pp = NULL;
}

const char *
lwrap_version(void)
{
   return "0.1.0-dev0";
}

static void
_insert_spaces(struct varstr *x, unsigned n)
{
   unsigned    i;

   for (i = 0; i < n; i++)
      varstr_catc(x, ' ');
}

char       *
lwrap_format(struct linewrapper *p, const unsigned indent, const unsigned width,
             const char *str)
{
   unsigned    i;
   enum states { init, in_ws, in_text };
   unsigned    state = init;
   unsigned    curr_width = 0;

   if (IS_NULL(p->s))
      p->s = varstr_new();
   else
      varstr_empty(p->s);

   _insert_spaces(p->s, indent);                 /* initial padding */
   curr_width = indent;

   for (i = 0; i < strlen(str); i++) {

      switch (state) {

         case init:
            if (isspace(str[i])) {
               state = in_ws;
            }
            else {
               varstr_catc(p->s, str[i]);
               curr_width += 1;
               state = in_text;
            }
            break;

         case in_ws:
            if (isspace(str[i])) {
               if (curr_width > width) {
                  varstr_catc(p->s, '\n');
                  _insert_spaces(p->s, indent);
                  curr_width = indent;
                  state = init;
               }
            }
            else {
               varstr_catc(p->s, str[i]);
               curr_width += 1;
               state = in_text;
            }
            break;

         case in_text:
            if (isspace(str[i])) {
               if (curr_width > width) {
                  varstr_catc(p->s, '\n');
                  _insert_spaces(p->s, indent);
                  curr_width = indent;
                  state = init;
               }
               else {
                  varstr_catc(p->s, ' ');
                  curr_width += 1;
                  state = in_ws;
               }
            }
            else {
               varstr_catc(p->s, str[i]);
               curr_width += 1;
            }
            break;

         default:
            ;
      }
   }

   return varstr_str(p->s);
}

#undef  IS_NULL
#undef  FREE
