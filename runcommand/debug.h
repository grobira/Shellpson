#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* Report system error */

#define fault(expression)   do {if (expression) {fprintf (stderr, \
                           "%s : %d : %s\n", __FILE__, __LINE__,  \
                           strerror(errno));}} while (0)

/* Report system error and return with specified value. */

#define fail(expression, status)   do {if (expression) {fprintf (stderr, \
                           "%s : %d : %s\n", __FILE__, __LINE__,  \
                           strerror(errno)); return status;}} while (0)

/* Report system error and exits with value EXIT_FAILURE. */

#define fatal(expression)   do {if (expression) {fprintf (stderr, \
                            "%s : %d : %s\n", __FILE__, __LINE__,  \
                            strerror(errno)); exit(EXIT_FAILURE) ;}} \
                            while (0)
#endif	/* DEBUG_H */

/* Notice the trick

   #define foo(bar)  if (bar) { do_something(); }

   works ok when you use it like in

   bar = 1;
   foo (bar);
   go_on();

   but what if you do

   bar = 1;
   if (expression)
      foo (bar);
   else
      go_on();

   The extra ; after the curly braces of if block will work as a blank statement
   ending the if clause; compiler will see a "floating" else without an if.
   
   #define foo(bar) do{if(bar) do_something;} while(0)

   does require a trailing; to be syntactically correct.  Most moderns
   compiler will notice the constant in while() clause and will perform
   optimization, actually removing the unnecessary test. So the trick 
   does costs runtime performance.

 */
