//adhilos2.c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define NHILOS 3

int contador=0;
sem_t mutex;

int main(){
	pthread_t hilos[NHILOS];
	int status, v[NHILOS];
	int *resultado;
	extern int contador;
	void *adder(void *p);

	//INICIALIZAMOS EL SEMAFORO
	sem_init(&mutex, 0, 1);

	//CREAMOS NHILOS
	for(int i=0; i<NHILOS; i++){
		v[i]=i;
		if((status=pthread_create(&hilos[i], NULL, &adder, (void*)&v[i]))){
			printf("Error al crear al hilo %d\n", i);
			exit(status);
		}
	}

	//RECOGEMOS NHILOS
	for(int i=0; i<NHILOS; i++){
		pthread_join(hilos[i], (void**)&resultado);
		printf("HILO %d = %d\n", v[i], *resultado);
	}

	//MOSTRAMOS EL RESULTADO FINAL
	printf("CONTADOR FINAL = %d\n", contador);
}

void *adder(void *p){
	extern int contador;
	int tmp;

	for(int i=0; i<100; i++){
		sem_wait(&mutex);
			tmp=contador;
			tmp++;
			contador=tmp;
		sem_post(&mutex);
	}

	int *retorno=(int*)malloc(sizeof(int));
	*retorno=contador;
	pthread_exit((void*)retorno);
}