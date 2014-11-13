#include <stdio.h>
#include <assert.h>

#include "closure.h"

int main(int argc, char* argvp[])
{
	test_one();
	test_two();
	test_three();
	test_four();

	return 0;
}

void test_one()
{
	/* Out of line definition of the function */
	closure k;
	k.x = 4;
	k.y = 7;
	int value = 11;
	k.f = sum;

	int result = k.f(k.x, k.y, value);
	printf("Result: %d\n", result);
	assert(result == 22);
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

// ISO C forbids nested functions. I still disagree.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
void test_three()
{
	closure_strict k;
	k.x = 9;
	k.y = 12;
	int value = 1;
	int (*fun) (int a, int b) = ({
		int sum_inline(int a, int b) 
		{ 
			return a + b + value;
		} sum_inline; 
	});
	k.f = fun;

	int result = k.f(k.x, k.y);
	printf("Result: %d\n", result);
	assert(result == 22);
}
#pragma GCC diagnostic pop

// ISO C forbids nested functions. I really insist this is wrong.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
void test_four()
{
	int values[] = {1,2,3,4,5,6,7,8,9};
	int length = 9;
	int scale_factor = 2;
	int (*fun) (int a) = ({
		int scale(int a)
		{
			return a * scale_factor;
		} scale;
	});

	map(fun, values, length);

	printf("Results: {");
	int expected_result[] = {2,4,6,8,10,12,14,16,18};
	for(int i = 0; i < length - 1; i++){
		printf("%d, ", values[i]);
		assert(expected_result[i] == values[i]);
	}
	assert(expected_result[length - 1] == values[length - 1]);
	printf("%d}\n", values[length - 1]);
}
#pragma GCC diagnostic pop


void map(int (*function)(int value), int values[], int length)
{
	for(int i = 0; i < length; i++)
		values[i] = function(values[i]);
}

int sum(int a, int b, int c) {
	return a + b + c;
}

