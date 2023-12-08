#include "tweets.h"

long int memoria_merge=0, memoria_radix=0;

void insertionSort(tweet *tts, int cant_tweets){
    int i, j;
    long int key, key2;
    char fecha1[11],fecha2[11],hora1[9],hora2[9];
    tweet resp;

    for(i=1;i<cant_tweets;i++){
        resp = tts[i];

        strcpy(fecha1,tts[i].fecha);
        strcpy(hora1,tts[i].hora);
        key = get_fecha(fecha1); //"2009-06-02" => 20090602
        key*=1000000;
        key+=get_hora(hora1); //"2009-06-02;02:59:57" => 20090602025957

        j = i-1;
        strcpy(fecha2,tts[j].fecha);
        strcpy(hora2,tts[j].hora);
        key2 = get_fecha(fecha2);
        key2*=1000000;
        key2+=get_hora(hora2);

        while(j>=0 && key2>key){
            tts[j+1] = tts[j];
            j--;
            if(j>=0){
                strcpy(fecha2,tts[j].fecha);
                strcpy(hora2,tts[j].hora);
                key2 = get_fecha(fecha2);
                key2*=1000000;
                key2+=get_hora(hora2);
            }
        }
        tts[j+1] = resp;
    }
}

////////////////////////////////////////////////////////////////////////

void merge(tweet *tts,int l,int m,int r){
    int i,j,k;
    int n1 = m-l+1;
    int n2 = r-m;
    char fecha1[11],fecha2[11],hora1[9],hora2[9];

    tweet *L = malloc(n1*sizeof(tweet)); //arreglos temporales
    tweet *R = malloc(n2*sizeof(tweet));
    memoria_merge+=(n1*sizeof(tweet)+n2*sizeof(tweet));

    for(i=0;i<n1;i++){L[i]=tts[l+i];}
    for(j=0;j<n2;j++){R[j]=tts[m+1+j];}

    i=0;j=0;k=l; //mezcla
    while(i<n1 && j<n2){
        long int L_comp,R_comp;
        strcpy(fecha1,L[i].fecha);
        strcpy(hora1,L[i].hora);
        strcpy(fecha2,R[j].fecha);
        strcpy(hora2,R[j].hora);
        L_comp = get_fecha(fecha1); //"2009-06-02" => 20090602
        L_comp*=1000000;
        L_comp+=get_hora(hora1); //"2009-06-02;02:59:57" => 20090602025957
        R_comp = get_fecha(fecha2);
        R_comp*=1000000;
        R_comp+=get_hora(hora2);

        if(L_comp<=R_comp){tts[k]=L[i];i++;}
        else{tts[k]=R[j];j++;}
        k++;
    }

    while(i<n1){tts[k]=L[i];i++;k++;}
    while(j<n2){tts[k]=R[j];j++;k++;}

    free(L); free(R);
}

void mergeSort(tweet *tts,int l,int r){
    if(l<r){
        int m = l+(r-l) / 2;

        mergeSort(tts,l,m);
        mergeSort(tts,m+1,r);

        merge(tts,l,m,r);
    }
}

////////////////////////////////////////////////////////////////////////

long int maximo(tweet *tts, int tam){
    int i;
    char fecha1[11],fecha2[11],hora1[9],hora2[9];
    strcpy(fecha1,tts[0].fecha);
    strcpy(hora1,tts[0].hora);
    long int mayor = get_fecha(fecha1); //"2009-06-02" => 20090602
    mayor*=1000000;
    mayor+=get_hora(hora1); //"2009-06-02;02:59:57" => 20090602025957
    
    for(i=1;i<tam;i++){
        strcpy(fecha2,tts[i].fecha);
        strcpy(hora2,tts[i].hora);
        long int comp = get_fecha(fecha2);
        comp*=1000000;
        comp+=get_hora(hora2);
        if(comp>mayor)
            mayor=comp;
    }

    return mayor;
}

void countingSort(tweet *A,int tam,int pos){
    long int lugar = pow(10,pos);
    //printf("lugar = %ld\n",lugar);
    tweet *B = malloc(tam*sizeof(tweet));
    memoria_radix+=(tam*sizeof(tweet));
    int i, ind_sgte, veces;
    char fecha1[11],hora1[9], fecha2[11], hora2[9];
    strcpy(fecha1,A[0].fecha);
    strcpy(hora1,A[0].hora);
    long int temp = get_fecha(fecha1);
    temp*=1000000;
    temp+=get_hora(hora1);
    int max = (temp/lugar) % 10;

    for(i=1;i<tam;i++){
        strcpy(fecha2,A[i].fecha);
        strcpy(hora2,A[i].hora);
        long int temp2 = get_fecha(fecha2);
        temp2*=1000000;
        temp2+=get_hora(hora2);
        if( ((temp2/lugar) % 10) > max)
            max = (temp2/lugar) % 10;
    }

    int C[max+1];
    for(i=0;i<max;++i)
        C[i]=0;

    for(i=0;i<tam;i++){
        strcpy(fecha2,A[i].fecha);
        strcpy(hora2,A[i].hora);
        long int temp2 = get_fecha(fecha2);
        temp2*=1000000;
        temp2+=get_hora(hora2);
        C[(temp2/lugar) % 10]++;
    }
    ind_sgte = 0;

    for(i=0;i<tam;i++){
        veces=C[i];
        C[i]=ind_sgte;
        ind_sgte+=veces;
    }

    for(i=0;i<tam;i++){
        strcpy(fecha2,A[i].fecha);
        strcpy(hora2,A[i].hora);
        long int temp2 = get_fecha(fecha2);
        temp2*=1000000;
        temp2+=get_hora(hora2);
        B[C[(temp/lugar) % 10]] = A[i];
        C[(temp/lugar) % 10]++;
    }

    free(B);
}

void radixSort(tweet *tts, int tam){
    int pos;
    long int max = maximo(tts,tam);
    for(pos=0;(max/pow(10,pos))>0;pos++){
        countingSort(tts,tam,pos);
    }
}

////////////////////////////////////////////////////////////////////////

long int get_mem(int sort){
    if(sort==1){return memoria_merge;}
    if(sort==2){return memoria_radix;}
    return -1;
}

/*void countingSort(tweet *tts,int tam,int comp){
    //comp=0 ordenar por fecha; comp=1 ordenar por hora
    int i;
    tweet *output = malloc(tam*sizeof(tweet));
    char fecha1[11],fecha2[11];//,hora1[9],hora2[9];
    strcpy(fecha1,tts[0].fecha);
    //strcpy(hora1,tts[0].hora);
    int mayor = get_fecha(fecha1); //"2009-06-02" => 20090602
    //mayor*=1000000;
    //mayor+=get_hora(hora1); //"2009-06-02;02:59:57" => 20090602025957

    for(i=1;i<tam;i++){
        strcpy(fecha2,tts[i].fecha);
        //strcpy(hora2,tts[i].hora);
        long int comp = get_fecha(fecha2);
        //comp*=1000000;
        //comp+=get_hora(hora2);
        if(comp>mayor)
            mayor=comp;
    }
    printf("mayor = %d\n",mayor);

    int *count = malloc(20221231*sizeof(int));

    for(i=0;i<=mayor;i++){
        count[i]=0;
    }

    for(i=0;i<=mayor;i++){
        strcpy(fecha2,tts[i].fecha);
        //strcpy(hora2,tts[i].hora);
        int comp = get_fecha(fecha2);
        //comp*=1000000;
        //comp+=get_hora(hora2);
        count[comp]++;
    }

    for(i=1;i<=mayor;i++){
        count[i] += count[i-1];
    }

    for(i=tam-1;i>=0;i--){
        strcpy(fecha2,tts[i].fecha);
        //strcpy(hora2,tts[i].hora);
        int comp = get_fecha(fecha2);
        //comp*=1000000;
        //comp+=get_hora(hora2);
        output[count[comp] - 1] = tts[i];
        count[comp]--;
    }

    for(i=0;i<tam;i++){
        tts[i] = output[i];
    }

    free(output); free(count);
}*/