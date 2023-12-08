#include "entradas.h"

const double pct_interno = 0.25;
const int cant_externo = 5000;

int main(int argc, char **argv){
	srand(time(NULL));
	stadium st, *ptr_st;
	ptr_st = &st;
	adquirir_datos(ptr_st,argv[1]);

	fans f, *ptr_f;
	ptr_f = &f;
	iniciar_clientes(&ptr_f, ptr_st);

	sector *sectores = ptr_st->secc;

	free_sectores(&sectores);
	free_clientes(&ptr_f);

	return 0;
}