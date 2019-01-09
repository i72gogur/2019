//lamport.c

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ITER 10
#define NHILOS 4
#define FALSE 0
#define TRUE 1

typedef unsigned char BOOLEAN;
double counter = 0;
int ticket[NHILOS]; //para asignar numero de cola a los hilos
BOOLEAN Elegido[NHILOS];

int main()
{
	extern BOOLEAN Elegido[NHILOS];
	extern int ticket[NHILOS];
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    void *adder(void *);
    double *r_value;

    //Inicializamos las variables globales
    for(int i=0; i<NHILOS; i++){
    	Elegido[i]=TRUE;
    	ticket[i]=0;
    }

    // Create NHILOS threads
    for (i = 0; i < NHILOS; i++) {
		v[i] = i;
		if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i])))
	    exit(status);
    }

    // Wait threads
    for (i = 0; i < NHILOS; i++) {
		pthread_join(hilos[i], (void **) &r_value);
		printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    // Final result
    fprintf(stdout, "%f\n", counter);

    return 0;
}

int maximo(int *ticket, int n){
	int mayor=-1;
	for(int i=0; i<n; i++){
		if(ticket[i]>mayor){
			mayor=ticket[i];
		}
	}
	return mayor;
}

int comparar(int ticket1, int ticket2, int turno1, int turno2){
	if(ticket1>ticket2){
		return 1;
	}
	else{
		return 0;
	}
	if(ticket1==ticket2){
		if(turno2<turno1){
			return 1;
		}
		else{
			return 0;
		}
	}
}

void *adder(void *p)
{
    double l, *to_return;
    extern double counter;
    int *id, i;
    to_return = malloc(sizeof(double));

    id = (int *) p;
    extern BOOLEAN Elegido[NHILOS];
    extern int v[NHILOS];

    for (i = 0; i < ITER; i++) {
    	Elegido[*id]=TRUE;
    	ticket[*id]=maximo(ticket, NHILOS)+1;
    	Elegido[*id]=FALSE;
    	for(int j=0; j<NHILOS; j++){
    		while(Elegido[j]); //mientras esta dando valor al ticket de los otros hilos espera
    		while((ticket[j]!=0)&& comparar(ticket[*id], ticket[j], *id, j)); //mientras el ticket no sea 0 y si hay dos hilos que cogen el mismo ticket le da preferencia al que se ha creado primero
    	}
    	//Seccion critica
		l = counter;
		fprintf(stdout, "Hilo %d: %f\n", *id, counter);
		l++;
		counter = l;
		*to_return = counter;
		ticket[*id]=0; //ahora puede pasar el siguiente

    }
    pthread_exit((void *) to_return);
}