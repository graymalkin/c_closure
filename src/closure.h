#ifndef __closure_h_
#define __closure_h_

typedef struct closure {
	int (*f)(int a, int b, int z);
	int x;
	int y;
} closure;

int main(int argc, char* argvp[]);


#endif 
