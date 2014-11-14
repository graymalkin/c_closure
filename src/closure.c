#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#include "closure.h"

int main(int argc, char* argvp[])
{
	test_one();
	test_two();
	test_three();
	test_four();
	test_five_1();
	
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

	// Generate a random scale factor to prevent the compiler trying to optimise
	//  a constant out.
	srand(time(NULL));
	int scale_factor = rand() % 10;


	void (*fun) (int *a) = ({
		void scale(int *a)
		{
			(*a) = (*a) * scale_factor;
		} scale;
	});

	// Map our closure against the array of values
	map(fun, values, length);

	// Print out the results, and assert them against the expected results
	printf("Results: {");
	int expected_result[] = {1 * scale_factor, 2 * scale_factor,
							 3 * scale_factor, 4 * scale_factor,
							 5 * scale_factor, 6 * scale_factor,
							 7 * scale_factor, 8 * scale_factor,
							 9 * scale_factor};
	for(int i = 0; i < length - 1; i++){
		printf("%d, ", values[i]);
		assert(expected_result[i] == values[i]);
	}
	assert(expected_result[length - 1] == values[length - 1]);
	printf("%d} (scale_factor: %d)\n", values[length - 1], scale_factor);
}
#pragma GCC diagnostic pop

// ISO C forbids nested functions. I really insist this is wrong.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
void test_five_1()
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
	test_five_2(k);
}
#pragma GCC diagnostic pop

void test_five_2(closure_strict clj)
{	
	int result = clj.f(clj.x, clj.y);
	printf("Result: %d\n", result);
	assert(result == 22);
}

void map(void (*function)(int *value), int values[], int length)
{
	for(int i = 0; i < length; i++)
		function(&values[i]);
}

int sum(int a, int b, int c) {
	return a + b + c;
}

