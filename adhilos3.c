//adhilos3.c

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#define M 25
#define NHILOS 4

int vector[M];
sem_t mutex;

int main(){
	pthread_t hilos[NHILOS];
	int status, v[NHILOS], res=0;
	extern int vector[M];
	sem_init(&mutex, 0, 1);
	void *funcion(void *p);

	//INICIALIZAMOS VECTOR
	for(int i=0; i<M; i++){
		vector[i]=0;
	}

	//CREACION DE NHILOS
	for(int i=0; i<NHILOS; i++){
		if((status=pthread_create(&hilos[i], NULL, &funcion, (void*)&v[i]))){
			printf("Error al crear al hijo %d\n", i);
			exit(status);
		}
	}

	//RECOGEMOS NHILOS
	for(int i=0; i<NHILOS; i++){
		pthread_join(hilos[i], NULL);
	}

	//RESULTADO FINAL
	for(int i=0; i<M; i++){
		res+=vector[i];
	}
	printf("Resultado final = %d\n", res);

}

void *funcion(void *p){
	extern int vector[M];
	int *id=(int*)p;
	int indice;

	for(int i=0; i<100; i++){
		sem_wait(&mutex);
			indice=rand()%M;
			vector[indice]++;
		sem_post(&mutex);
	}

	pthread_exit(NULL);

}