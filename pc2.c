//pc2.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define P 2
#define C 4
#define N 20
#define iteraciones 30


sem_t mutex;
sem_t empty;
sem_t full;
int buffer[N];
int indiceProd=-1;
int indiceCons=-1;

int main(){
	pthread_t hProd[P], hCons[C];
	int vProd[P], vCons[C];
	int status;
	int *resProd, *resCons;
	int totalProd=0, totalCons=0;
	void *productor(void *p);
	void *consumidor(void *p);

	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, N);

	//CREACION DE P HILOS PRODUCTORES
	for(int i=0; i<P; i++){
		vProd[i]=i;
		if((status=pthread_create(&hProd[i], NULL, &productor, (void*)&vProd[i]))){
			printf("Error al crear al hilo productor %d\n", i);
			exit(status);
		}
	}

	//CREACION DE C HILOS CONSUMIDORES
	for(int i=0; i<C; i++){
		vCons[i]=i;
		if((status=pthread_create(&hCons[i], NULL, &consumidor, (void*)&vCons[i]))){
			printf("Error al crear al hilo consumidor %d\n", i);
			exit(status);
		}
	}

	//ESPERAMOS A QUE FINALICEN LOS P HILOS PRODUCTORES
	for(int i=0; i<P; i++){
		pthread_join(hProd[i], (void**)&resProd);
		totalProd+=*resProd;
	}

	//ESPERAMOS A QUE FINALICEN LOS C HILOS CONSUMIDORES
	for(int i=0; i<C; i++){
		pthread_join(hCons[i], (void**)&resCons);
		totalCons+=*resCons;
	}

	//RESULTADO FINAL
	printf("TOTAL PRODUCIDO = %d\n", totalProd);
	printf("TOTAL CONSUMIDO = %d\n", totalCons);

	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);

}

void *productor(void *p){
	int valor, aux=0;
	srand(time(NULL));

	for(int i=0; i<iteraciones; i++){
		sem_wait(&empty);
			valor=rand()%1000;
			aux+=valor;
		sem_wait(&mutex);
			indiceProd=(indiceProd+1)%N;
			buffer[indiceProd]=valor;
			printf("Se ha introducido el valor %d en el buffer %d\n", valor, indiceProd);
		sem_post(&mutex);
		sem_post(&full);

	}

	int *retorno=(int*)malloc(sizeof(int));
	*retorno=aux;
	pthread_exit((void*)retorno);
}

void *consumidor(void *p){
	int valor, aux=0;
	int iteracionesCons=(iteraciones*P/C);

	for(int i=0; i<iteracionesCons; i++){
		sem_wait(&full);
		sem_wait(&mutex);
			indiceCons=(indiceCons+1)%N;
			valor=buffer[indiceCons];
			aux+=valor;
			printf("Se ha consumido %d del indice %d\n", valor, indiceCons);
		sem_post(&mutex);
		sem_post(&empty);
	}

	int *retorno=(int*)malloc(sizeof(int));
	*retorno=aux;
	pthread_exit((void*)retorno);
}