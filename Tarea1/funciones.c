#include "entradas.h"
#include<string.h>

void adquirir_datos(stadium *s, char arch[]){
	FILE *txt = fopen(arch,"r");
	rewind(txt);

	char linea[25];
	fscanf(txt, "%[^\n] ",linea);
	char espacio[] = " ";
	char *token = strtok(linea, espacio);

	token = strtok(NULL, espacio); //llegamos al num_sec
	s->cant_sec = atoi(token);

	token = strtok(NULL, espacio);
	token = strtok(NULL, espacio); //llegamos al precio base
	s->pbase = atoi(token);

	sector *sec = NULL;
	int cont = 0;
	while(fscanf(txt, "%[^\n] ", linea) != EOF){
		char *retoken = strtok(linea,espacio); //id
		int id = atoi(retoken);
		retoken = strtok(NULL, espacio); //llegamos a la cantidad de entradas
		int asientos = atoi(retoken);
		retoken = strtok(NULL, espacio); //legamos al factor multiplicador de precio
		float factor = atof(retoken);

		/*Aca elegi trabajar con los sectores como una lista simple enlazada de estos
		para asi para poder utilizar los nodos de dichos sectores en el main de nuestro programa
		y conseguir localizar y acceder a los datos de cada uno de estos de la forma mas
		sencilla posible dentro de los distintos tipos de datos abstractos vistos.*/
		add_sector(&sec,id,asientos,factor,cont);
		
		cont++;
	}

	s->secc = sec;

	fclose(txt);
}

int al_azar(int min, int max){
	if(min>max){
		printf("Limites para random mal establecidos.\n");
		exit(-1);
	}
	int lim_sup = max+1;
	int num = rand()%lim_sup;
	if(min!=0){
		int lim_inf = min-1;
		while(num>=0 && num<=lim_inf){num = rand()%lim_sup;}
	}
	return num;
}

int cant_entradas(sector *sec){
	int total=0;
	if(sec == NULL){
		printf("Fallo al intentar obtener cantidad de entradas.\n");
		exit(-1);
	}else{
		sector *rec = sec;
		while(rec!=NULL){
			int num = rec->asientos;
			total+=num;
			rec=rec->sgte;
		}
	}
	return total;
}

int caro_barato(sector *cabeza, int pbase, int num){
	//num==0 <=> sector barato
	//num==1 <=> sector caro
	int precio;
	if(cabeza == NULL){
		printf("Fallo al buscar sector mas barato / caro.\n");
		exit(-1);
	}else{
		precio = pbase*(cabeza->factor);
		sector *rec = cabeza;
		rec = rec->sgte;
		while(rec!=NULL){
			int nuevo = pbase*(rec->factor);
			if(num==0 && nuevo<precio){precio=nuevo;}
			else if(num==1 && nuevo>precio){precio=nuevo;}
			rec = rec->sgte;
		}
	}
	return precio;
}

void comprar(sector *cabeza, int presupuesto, int pbase, int lista[2]){
														//[0] entradas compradas, [1] n_sector
	if(cabeza == NULL){
		printf("Fallo al introducir nodo de sector al comprar.\n");
		exit(-1);
	}else{
		int respaldo_dinero = presupuesto;
		int precio = 0;
		int unicaentrada; //0 == hay mas de una entrada disponible.
		sector *rec = cabeza;
		while(rec!=NULL){
			int nuevo = pbase*(rec->factor);
			if(nuevo>=precio && presupuesto>=nuevo && (rec->asientos)>0){
				precio = nuevo;
				if((rec->asientos)==1){unicaentrada=1;}
				else{unicaentrada=0;}
			}
			rec = rec->sgte;
		}

		if(presupuesto-(precio*2)>=0 && unicaentrada==0){
			lista[0] = 2;
			respaldo_dinero-=precio*2;
		}else{
			lista[0] = 1;
			respaldo_dinero-=precio;
		}

		if(presupuesto==respaldo_dinero){//se agotaron las entradas
			lista[0]=0;
			lista[1]=0;
		}else{
			sector *nuevorec = cabeza;
			while(nuevorec!=NULL){
				int dinero = pbase*(nuevorec->factor);
				if(dinero==precio){
					(nuevorec->asientos)-=lista[0];
					lista[1] = nuevorec->id;
					break;
				}
				nuevorec = nuevorec->sgte;
			}
		}

	}
}

void localidades_agotadas(sector *cabeza){
	if(cabeza == NULL){
		printf("Fallo al introducir nodo de sector al buscar sectores agotados.\n");
		exit(-1);
	}else{
		sector *rec = cabeza;
		while(rec!=NULL){
			if(rec->asientos==0){
				printf("Localidad N°%d AGOTADA.\n",rec->id);
			}
			rec = rec->sgte;
		}
	}
}

void sponsor(){
	int num = al_azar(1,3);
	if(num==1){
		printf("\n");
		printf("***********************************************************\n");
		printf("*       PunteroTicket trae a Chile a: Conejo !Bueno       *\n");
		printf("*                                                         *\n");
		printf("*                                                         *\n");
		printf("*                    CONEJO !BUENO                        *\n");
		printf("*                                                         *\n");
		printf("*                                                         *\n");
		printf("* ¡No te quedes sin tu entrada, la venta ya ha comenzado! *\n");
		printf("*                                                         *\n");
		printf("*                                                         *\n");
		printf("*                    CONEJO !BUENO                        *\n");
		printf("*                                                         *\n");
		printf("*                                                         *\n");
		printf("*       PunteroTicket trae a Chile a: Conejo !Bueno       *\n");
		printf("***********************************************************\n");
	}
	else if(num==2){
		printf("\n");
		printf(" _________________________________________________________\n");
		printf("|                                                         |\n");
		printf("|           Para refrescarte prefiere siempre...          |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|        <3             ***PYPSI***             <3        |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|  La bebida auspiciadora del concierto de Conejo !Bueno  |\n");
		printf("|                                                         |\n");
		printf("|                                                         |\n");
		printf("|        <3             ***PYPSI***             <3        |\n");
		printf("|                                                         |\n");
		printf("|_________________________________________________________|\n");
	}

}

void iniciar_clientes(fans *f, stadium *s){
	int capac_st, cant_clientes, i;

	sector *sectores = s->secc;
	capac_st = cant_entradas(sectores); //=68.500
	cant_clientes = al_azar(5*capac_st, 20*capac_st);

	int barato = caro_barato(sectores,s->pbase,0);
	int caro = caro_barato(sectores,s->pbase,1);
	int ide = 0;
	int cont = 0;
	int n_reporte = 0;
	int cant_disp = capac_st;
	int clientes_agregados = 0;

	for(i=0;i<cant_clientes;i++){
		int dinero = al_azar(barato/2,caro*3);
		int entradasnum,seccionnum;
		if(dinero<barato){
			entradasnum=0;
			seccionnum=0;
		}else{
			int lista[2];
			comprar(sectores,dinero,s->pbase,lista);
			entradasnum = lista[0];
			seccionnum = lista[1];
			cont+=entradasnum;
			cant_disp-=entradasnum;
		}
		ide++;
		char *id;
		sprintf(id, "%d", ide);

		/*Aca decidi tambien utilizar una lista simple enlazada para los clientes,
		ya que es la estructura de datos mas comun y la cual mejor me puedo manejar a la hora
		de realizar lo necesario con cada uno de sus nodos, si bien se que puede no ser
		la opcion mas rentable a la hora de hablar de recorrer los nodos y realizar una cantidad
		de acciones innecesarias y poco optimas.*/
		add_fan(f,dinero,seccionnum,entradasnum,id,cant_clientes,i);
		clientes_agregados++;

		if(cont>=cant_externo){
			///////////REPORTE PUBLICO///////////////
			n_reporte++;
			printf("\n\n||||||||||| REPORTE N°%d ||||||||||||||||\n",n_reporte);
			printf("Cantidad de entradas disponibles = %d\n",cant_disp);
			localidades_agotadas(sectores);
			sponsor();

			cont-=cant_externo;
		}
	}
	if(cant_disp==0){//se agotaron todas las entradas
		printf("\n\n\n\n||||||||||||||||||||||||||| E N T R A D A S    ");
		printf("A G O T A D A S |||||||||||||||||||||||||||||||||||||||\n\n\n\n\n");
	}

}