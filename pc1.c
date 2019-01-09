//pc1.c

#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>


#define iteraciones 30
#define N 20

sem_t mutex; //seccion critica
sem_t full; //llenos
sem_t empty; //vacios
int buffer[N];

int main(){
	pthread_t hilos[2];
	int status, v[2];
	int *resProd, *resCons;
	void *productor(void *p);
	void *consumidor(void *p);

	v[0]=0;
	v[1]=1;

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);

	//CREACION DEL HILO PRODUCTOR
	if((status=pthread_create(&hilos[0], NULL, &productor, (void*)&v[0]))){
		printf("Error al crear al hijo productor\n");
		exit(status);
	}

	//CREACION DEL HILO CONSUMIDOR
	if((status=pthread_create(&hilos[1], NULL, &consumidor, (void*)&v[1]))){
		printf("Error al crear al hijo consumidor\n");
		exit(status);
	}

	//RECOGEMOS EL HILO PRODUCTOR
	pthread_join(hilos[0], (void**)&resProd);
	

	//RECOGEMOS EL HILOS CONSUMIDOR
	pthread_join(hilos[1], (void**)&resCons);

	//RESULTADO FINAL
	printf("PRODUCIDO = %d\n", *resProd);
	printf("CONSUMIDO = %d\n", *resCons);

	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);

}

void *productor(void *p){
	srand(time(NULL));
	int indice=-1, valor, aux=0;
	for(int i=0; i<iteraciones; i++){
		sem_wait(&empty);
			indice=(indice+1)%N;
			valor=rand()%1000;
			aux+=valor;
		sem_wait(&mutex);
			buffer[indice]=valor;
			printf("Se ha introducido el valor %d en el indice %d\n", valor, indice);
		sem_post(&mutex);
		sem_post(&full);
	}

	int *retorno=(int*)malloc(sizeof(int));
	*retorno=aux;
	pthread_exit((void*)retorno);
}

void *consumidor(void *p){
	int indice=-1, valor, aux=0;
	for(int i=0; i<iteraciones; i++){
		sem_wait(&full);
			indice=(indice+1)%N;
		sem_wait(&mutex);
			valor=buffer[indice];
			aux+=valor;
			printf("Se lee el dato %d del indice %d\n", valor, indice);
		sem_post(&mutex);
		sem_post(&empty);
	}

	int *retorno=(int*)malloc(sizeof(int));
	*retorno=aux;
	pthread_exit((void*)retorno);

}