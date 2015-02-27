#include <stdio.h>

#define GENERIC_MAX(type) \
    type type##_max(type a, type b)\
    {                              \
        return a>b?a:b;            \
    }

GENERIC_MAX(float);		/* generate float_max */

int main(void)
{
	float a = 3.1, b = 3.2;

	float (*fun) (float, float);
	fun = float_max;

	printf("%f\n", fun(a, b));
	return 0;
}
