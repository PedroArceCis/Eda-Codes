 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Ejemplo aprenderaprogramar.com
int main() {
	srand(time(NULL));
	int num = rand()%21;
	while(num>=0 && num<=4){
		printf("ay no num = %d\n",num);
		num=rand()%21;
	}
	printf("Numero aleatorio entre 5 y 20 es %d\n" ,num);

	int n = 123456;
	printf("pos 2 = %d\n",n[1]);

	return 0;
}