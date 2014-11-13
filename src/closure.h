#ifndef __closure_h_
#define __closure_h_

typedef struct closure {
	int (*f)(int a, int b, int c);
	int x, y;
} closure;

typedef struct closure_strict {
	int (*f)(int a, int b);
	int x, y;
} closure_strict;

int main(int argc, char* argvp[]);
void test_one();
void test_two();
void test_three();
int sum(int a, int b, int c);

#endif 
