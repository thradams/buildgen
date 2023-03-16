/*
* This is a hello world program
*/

#include <stdio.h>

#ifndef TEST
int main()
{
    printf("Hello world!");
}
#else
#include "unit_test.c"
int main(int argc, char** argv)
{
    int r = test_main();
    printf("%d tests failed, %d tests passed\n", g_unit_test_error_count, g_unit_test_success_count);
}
#endif
