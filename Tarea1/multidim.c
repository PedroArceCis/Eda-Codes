 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
	int a[3][2];
	int b[2] = {8,9};
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = b[0];
	a[1][1] = b[1];
	printf("segunda pos, primer num = %d\n",a[1][0]);
	return 0;
}