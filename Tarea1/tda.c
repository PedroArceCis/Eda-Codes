#include "entradas.h"

void add_sector(sector **cabeza, int id, int asientos, double factor, int pos){
	sector *nuevo = malloc(sizeof(sector));
	sector *recorredor = (*cabeza);
	int cont;

	if(nuevo == NULL){
		printf("Error al crear el nodo de sector.\n");
		exit(-1);
	}
	nuevo->id = id;
	nuevo->asientos = asientos;
	nuevo->factor = factor;

	if(recorredor==NULL || pos==0){
		nuevo->sgte=(*cabeza);
		*cabeza = nuevo;
	}else{
		for(cont=0;cont<pos-1;cont++){
			if(recorredor->sgte == NULL)
				break;
			recorredor = recorredor->sgte;
		}
		nuevo->sgte = recorredor->sgte;
		recorredor->sgte = nuevo;
	}
}

void add_fan(fans **cabeza, int presupuesto, int n_seccion, int n_entradas, char *id, int total_clientes, int pos){
	fans *nuevo = malloc(sizeof(fans));
	fans *recorredor = (*cabeza);
	int cont;

	if(nuevo == NULL){
		printf("Error al crear el nodo de cliente.\n");
		exit(-1);
	}
	nuevo->id = id;
	nuevo->presupuesto = presupuesto;
	nuevo->n_seccion = n_seccion;
	nuevo->n_entradas = n_entradas;
	nuevo->total_clientes = total_clientes;

	if(recorredor==NULL || pos==0){
		nuevo->sgte=(*cabeza);
		*cabeza = nuevo;
	}else{
		for(cont=0;cont<pos-1;cont++){
			if(recorredor->sgte == NULL)
				break;
			recorredor = recorredor->sgte;
		}
		nuevo->sgte = recorredor->sgte;
		recorredor->sgte = nuevo;
	}
}

void free_sectores(sector **sec){
	sector *rec = *sec;
	while(*sec != NULL){
		*sec = rec->sgte;
		free(rec);
		rec = *sec;
	}
}

void free_clientes(fans **cabeza){
	int i = (*cabeza)->total_clientes;
	int cont = 0;
	fans *temp = *cabeza;
	while(*cabeza != NULL){
		*cabeza = temp->sgte;
        free(temp);
        temp = *cabeza;
        cont++;
        if(cont==i){break;}
	}
}