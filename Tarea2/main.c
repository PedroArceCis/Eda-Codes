#include "tweets.h"

int main(int argc, char **argv){
    int cant_tweets = get_cantLineas(argv[1]);
    double tiempo[3];
    long int memoria[3];

    int cont;
    for(cont=0;cont<3;cont++){
        printf("\nReservando memoria...\n");
        tweet *tweets = malloc(cant_tweets*sizeof(tweet));
        printf("Memoria reservada.\n");
        leer_arch(argv[1],tweets);

        double time_spent = 0.0;
        clock_t begin = clock();

        if(cont==0){
            printf("\nProcediendo a ordenar los datos con Insertion Sort...\n");
            insertionSort(tweets,cant_tweets);
            //printArray(tweets,cant_tweets);

            clock_t end = clock();
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
            tiempo[cont] = time_spent;

            memoria[cont] = (cant_tweets*sizeof(tweet))+char_mem();

            //secreto(tweets,argv[2]);
        }
        else if(cont==1){
            printf("\nProcediendo a ordenar los datos con Merge Sort...\n");
            mergeSort(tweets,0,cant_tweets-1);
            //printArray(tweets,cant_tweets);

            clock_t end = clock();
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
            tiempo[cont] = time_spent;

            memoria[cont] = (cant_tweets*sizeof(tweet))+char_mem()+get_mem(cont);

            secreto(tweets,argv[2]);
        }
        else if(cont==2){
            printf("\nProcediendo a ordenar los datos con Radix Sort...\n");
            //radixSort(tweets,cant_tweets);
            //No funciona correctamente: problemas en implementación.
            //printArray(tweets,cant_tweets);

            clock_t end = clock();
            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
            tiempo[cont] = time_spent;

            memoria[cont] = (cant_tweets*sizeof(tweet))+char_mem()+get_mem(cont);

            //secreto(tweets,argv[2]);
        }
        printf("\nOrdenamiento terminado.\n");

        printf("\nLiberando memoria...\n");
        liberar(tweets,cant_tweets);
        printf("Memoria liberada.\n");

        if(cont!=2){
            printf(" ___________________________________________ \n");
            printf("|                                           |\n");
            printf("|Procediendo a una nueva lectura del archivo|\n");
            printf("|___________________________________________|\n");
        }
    }

    generar_reporte(tiempo,memoria);
    return 0;
}