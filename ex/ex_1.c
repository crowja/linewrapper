#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "linewrapper.h"

void
wrap(unsigned indent, unsigned width, char *str, char **newstr)
{
   unsigned    i, j;
   unsigned    max_lines = 1 + (strlen(str) + 1) / width;
   unsigned    max_len = max_lines * (1 + indent * width);
   unsigned    in_indent_count;
   unsigned    curr_width;
   enum states { in_indent, in_ws, in_text };
   enum states state;

   *newstr = realloc(*newstr, sizeof(char) * max_len);

   curr_width = 0;
   state = in_indent;

   i = 0;
   j = 0;

   for (;;) {

      if (i == strlen(str))
         break;

      switch (state) {

         case in_indent:
            if (curr_width < indent) {
               (*newstr)[j] = ' ';
               j++;
               curr_width++;
            }
            else {
               state = in_ws;
            }
            break;

         case in_ws:
            if (curr_width > width) {
               (*newstr)[j] = '\n';
               j++;
               curr_width = 0;
               state = in_indent;
            }
            else if (isspace(str[i])) {
               i++;
               ;                                 /* do nothing */
            }
            else {
               (*newstr)[j] = str[i];
               i++;
               j++;
               curr_width++;
               state = in_text;
            }
            break;

         case in_text:
            if (isspace(str[i])) {
               if (curr_width > width) {
                  (*newstr)[j] = '\n';
                  j++;
                  curr_width = 0;
                  state = in_indent;
               }
               else {
                   (*newstr)[j] = ' ';
                   j++;
                   curr_width++;
                   state = in_ws;
               }
            }
            else {
               (*newstr)[j] = str[i];
               j++;
               curr_width++;
            }

            i++;

            break;

         default:
            ;
      }
   }

   (*newstr)[j] = '\0';
}

int
main(void)
{
   char *cp;
   char        text[] =
#if 0
    "now is the time for allllll good men to come to the aid of their country. "
    "now, not later, is the time for allllll good men to come to the aid of their country. "
    "now is the time for allllll good men to come to the aid of their country. "
    "it seems clear that now is the time for allllll good men to come to the aid of their country. "
    "now is the time for allllll good men to come to the aid of their country. "
    "it's the case that now is the time for allllll good men to come to the aid of their country. ";
#else
    "Lorem        ipsum dolor sit amet, consectetur adipiscing elit. Proin et urna fermentum, consequat ex "
    "eget, pharetra velit. Vestibulum lectus eros, efficitur eu hendrerit ac, semper et leo. Etiam "
    "ultrices erat eget ligula condimentum sagittis. Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit. Nulla facilisi. Aenean maximus interdum semper. Vivamus feugiat arcu sapien, sit "
    "amet semper leo pretium quis. Sed in enim nunc. Aenean tristique vitae neque a fringilla. Quisque "
    "sodales cursus massa vel elementum. Maecenas lobortis efficitur sagittis. Nullam nec condimentum "
    "augue. Quisque condimentum, purus eget ullamcorper aliquam, diam dolor volutpat felis, eget "
    "maximus turpis arcu sit amet neque.\n"
    "123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789.";
#endif

#if 0

   struct linewrapper *f = lwrap_new();
   printf("INITIAL TEXT IS\n");
   printf("%s\n", text);
   printf("FORMATTED TEXT IS\n");
   printf("%s\n", lwrap_format(f, 5, 80, text));

   lwrap_free(f);

#else

   printf("ALT FORMATTED TEXT IS\n");
   cp = NULL;
   wrap(5, 80, text, &cp);
   printf("%s\n", cp);
   free(cp);

#endif

  
   return 0;
}
