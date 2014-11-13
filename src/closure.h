#ifndef __closure_h_
#define __closure_h_

typedef struct closure {
	int (*f)(int a, int b, int c);
	int x, y;
} closure;

int main(int argc, char* argvp[]);
void test_one();
void test_two();
int sum(int a, int b, int c);

#endif 
