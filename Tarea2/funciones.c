#include "tweets.h"

const int lineas_max = 2000;
//tamaño máximo de caracteres por línea

long int memoria_chars = 0;

int get_cantLineas(char arch[]){
	printf("\nInciando conteo de cantidad de lineas del archivo...");
	int cont = 0;
	FILE *txt = fopen(arch,"r");
	rewind(txt);
	char linea[lineas_max];
	while(fscanf(txt, "%[^\n] ", linea) != EOF)
		cont++;
	fclose(txt);
	printf("\nLectura de lineas terminada.\n");
	return cont;
}

void leer_arch(char arch[],tweet *tts){

	memoria_chars-=memoria_chars;
	printf("\nRecopilando informacion del archivo...");

	FILE *txt = fopen(arch,"r");
	rewind(txt);

	char linea[lineas_max];
	int cont = 0;
	while(fscanf(txt, "%[^\n] ", linea) != EOF){

		tts[cont].fecha = malloc(sizeof(char)*11);
		memoria_chars+=(sizeof(char)*11);
		char *token = strtok(linea,";");
		strcpy(tts[cont].fecha,token);

		token = strtok(NULL,";");
		tts[cont].hora = malloc(sizeof(char)*9);
		memoria_chars+=(sizeof(char)*9);
		strcpy(tts[cont].hora,token);

		token = strtok(NULL,";");
		tts[cont].user = malloc(sizeof(char)*(strlen(token)+1));
		memoria_chars+=(sizeof(char)*(strlen(token)+1));
		strcpy(tts[cont].user,token);

		token = strtok(NULL,"");
		if(token!=NULL){
			tts[cont].mensaje = malloc(sizeof(char)*(strlen(token)+1));
			memoria_chars+=(sizeof(char)*(strlen(token)+1));
			strcpy(tts[cont].mensaje,token);
		}
		else{tts[cont].mensaje = malloc(1);memoria_chars+=1;}

		cont++;
	}

	fclose(txt);
	printf("\nDatos de archivo recopilados.\n");
}

long int char_mem(){
	return memoria_chars;
}


void liberar(tweet *tts, int cant_tts){
	int cont = 0;
	while(cont<cant_tts){
		free(tts[cont].fecha);
		free(tts[cont].hora);
		free(tts[cont].user);
		free(tts[cont].mensaje);
		cont++;
	}
	free(tts);
}

int get_fecha(char *fecha_str){
	int resultado; //"2009-06-02" => 20090602
	char fecha[11];
	strcpy(fecha,fecha_str);

	char *date = strtok(fecha,"-"); //año
    resultado = atoi(date)*10000;
    date = strtok(NULL,"-"); //mes
    resultado += atoi(date)*100;
    date = strtok(NULL,""); //dia
    resultado += atoi(date);

    return resultado;
}

int get_hora(char *hora_str){
	int resultado; //"02:59:57" => 025957
	char hora[9];
	strcpy(hora,hora_str);

	char *hour = strtok(hora,":"); //hora
    resultado = atoi(hour)*10000;
    hour = strtok(NULL,":"); //min
    resultado += atoi(hour)*100;
    hour = strtok(NULL,""); //seg
    resultado += atoi(hour);

    return resultado;
}

void printArray(tweet *tts, int cant_tweets){
    int i;
    for(i=0; i<cant_tweets; i++)
        printf("fecha: %s | hora: %s | user: %s\n",tts[i].fecha,tts[i].hora,tts[i].user);
}

void generar_reporte(double tiempo[3],long int memoria[3]){
	FILE *arch = fopen("reporte.txt","w");
	fputs("Reporte comparativo de complejidad de los algoritmos utilizados en el programa.\n\n",arch);

	char temp[30];
	fputs("Tiempos de ordenamiento:\n",arch);
	fputs("Insertion Sort = ",arch);
	snprintf(temp, 15, "%f", tiempo[0]);
	fputs(temp,arch);
	fputs(" [s].\n",arch);
	fputs("Merge Sort = ",arch);
	snprintf(temp, 15, "%f", tiempo[1]);
	fputs(temp,arch);
	fputs(" [s].\n",arch);
	fputs("Radix Sort = ",arch);
	snprintf(temp, 15, "%f", tiempo[2]);
	fputs(temp,arch);
	fputs(" [s].\n\n",arch);

	double menor = tiempo[0];
	double mayor = tiempo[0];
	int i;
	for(i=1;i<3;i++){
		if(tiempo[i]<menor){menor=tiempo[i];}
		if(tiempo[i]>mayor){mayor=tiempo[i];}
		break; //Para no pasar a Radix Sort ya que no está funcionando correctamente.
	}

	fputs("Algoritmo con menor tiempo de ordenamiento: ",arch);
	if(menor==tiempo[0]){fputs("Insertion Sort.",arch);}
	if(menor==tiempo[1]){fputs("Merge Sort.",arch);}
	if(menor==tiempo[2]){fputs("Radix Sort.",arch);}

	fputs("\nAlgoritmo con mayor tiempo de ordenamiento: ",arch);
	if(mayor==tiempo[0]){fputs("Insertion Sort.",arch);}
	if(mayor==tiempo[1]){fputs("Merge Sort.",arch);}
	if(mayor==tiempo[2]){fputs("Radix Sort.",arch);}

	fputs("\n\nCantidad de memoria dinámica reservada a través de funciones 'malloc':",arch);
	fputs("\nInsertion Sort ≈ ",arch);
	snprintf(temp, 15, "%ld", memoria[0]);
	fputs(temp,arch);
	fputs(" bytes.",arch);
	fputs("\nMerge Sort ≈ ",arch);
	snprintf(temp, 15, "%ld", memoria[1]);
	fputs(temp,arch);
	fputs(" bytes.",arch);
	fputs("\nRadix Sort ≈ ",arch);
	snprintf(temp, 15, "%ld", memoria[2]);
	fputs(temp,arch);
	fputs(" bytes.\n",arch);

	long int mem_mayor = memoria[0];
	long int mem_menor = memoria[0];
	for(i=1;i<3;i++){
		if(memoria[i]<mem_menor){mem_menor=memoria[i];}
		if(memoria[i]>mem_mayor){mem_mayor=memoria[i];}
	}
	fputs("\nAlgoritmo con menor utilización de memoria dinámica:",arch);
	if(mem_menor==memoria[0]){fputs(" Insertion Sort.",arch);}
	if(mem_menor==memoria[1]){fputs(" Merge Sort.",arch);}
	if(mem_menor==memoria[2]){fputs(" Radix Sort.",arch);}
	fputs("\nAlgoritmo con mayor utilización de memoria dinámica:",arch);
	if(mem_mayor==memoria[0]){fputs(" Insertion Sort.",arch);}
	if(mem_mayor==memoria[1]){fputs(" Merge Sort.",arch);}
	if(mem_mayor==memoria[2]){fputs(" Radix Sort.",arch);}

	fputs("\n\n\n|Reporte realizado considerando problemas en el funcionamiento de Radix Sort.|",arch);

	fclose(arch);
}

void secreto(tweet *tts, char llaves[]){
	if(llaves!=NULL){
		FILE *keys = fopen(llaves,"r");
		char linea[lineas_max];
		fscanf(keys, "%[^\n] ", linea);
		char *token = strtok(linea," ");
		FILE *secreto = fopen("mensaje_secreto.txt","w");
		while(token!=NULL){
			fputs(tts[atoi(token)].mensaje,secreto);
			fputs("\n",secreto);
			token = strtok(NULL," ");
		}
		fclose(keys); fclose(secreto);
	}
}