#include <stdio.h>
#include <assert.h>

#include "closure.h"

int main(int argc, char* argvp[])
{
	test_one();
	test_two();

	return 0;
}

void test_one()
{
	/* Out of line definition of the function */
	closure k;
	k.x = 5;
	k.y = 7;
	int value = 11;
	k.f = sum;

	int result = k.f(k.x, k.y, value);
	printf("Result: %d\n", result);
	assert(result == 23);
}

// ISO C forbids nested functions. I disagree.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
void test_two()
{
	closure k;
	k.x = 2;
	k.y = 6;
	int value = 14;
	int (*fun) (int a, int b, int c) = ({
		int sum_inline(int a, int b, int c) 
		{ 
			return a + b + c;
		} sum_inline; 
	});
	k.f = fun;

	int result = k.f(k.x, k.y, value);
	printf("Result: %d\n", result);
	assert(result == 22);
}
#pragma GCC diagnostic pop

int sum(int a, int b, int c) {
	return a + b + c;
}

