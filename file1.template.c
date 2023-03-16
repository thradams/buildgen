/*file1*/
#include "file1.h"


int sum(int a, int b)
{
    return a + b;
}

#ifdef TEST
#include "unit_test.h"
void sum_test()
{
    assert(sum(2, 2) == 5);
}
#endif


