#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linewrapper.h"
#include "t/tinytest.h"

#ifdef  COLOR_CODE
#undef  COLOR_CODE
#endif
#define COLOR_CODE       0x1B

#ifdef  COLOR_RED
#undef  COLOR_RED
#endif
#define COLOR_RED        "[1;31m"

#ifdef  COLOR_GREEN
#undef  COLOR_GREEN
#endif
#define COLOR_GREEN      "[1;32m"

#ifdef  COLOR_YELLOW
#undef  COLOR_YELLOW
#endif
#define COLOR_YELLOW     "[1;33m"

#ifdef  COLOR_RESET
#undef  COLOR_RESET
#endif
#define COLOR_RESET      "[0m"


static void
printf_test_name(char *name, char *info)
{
   printf("%c%s%s%c%s", COLOR_CODE, COLOR_YELLOW, name, COLOR_CODE, COLOR_RESET);

   if (NULL != info)
      printf(" [%s]\n", info);
   else
      printf("\n");
}


static void
test_constr(void)
{
   struct linewrapper *z;

   printf_test_name("test_constr()", NULL);

   z = lwrap_new();
   ASSERT("Constructor test", z);
   lwrap_free(&z);
   ASSERT_EQUALS(NULL, z);
}


int
main(void)
{
   printf("%s\n", lwrap_version());

   RUN(test_constr);

   return TEST_REPORT();
}
