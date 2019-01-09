//adhilos1.c

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NHILOS 3

int matriz[3][3]={1, 2, 3, 1, 3, 2, 2, 1, 3};
int vector[3]={1, 3, 2};
int *res[3];

int main(){
	pthread_t hilos[NHILOS];
	int status, v[NHILOS];
	void *multiplica(void *p);

	//CREACION DE NHILOS
	for(int i=0; i<NHILOS; i++){
		v[i]=i;
		if((status=pthread_create(&hilos[i], NULL, &multiplica, (void*)&v[i]))){
			printf("Error al crear al hijo %d\n", i);
			exit(status);
		}
	}

	//ESPERAMOS A QUE FINALICEN LOS HILOS
	for(int i=0; i<NHILOS; i++){
		pthread_join(hilos[i], (void**)&res[i]);
	}

	//IMPRIMIMOS RESULTADO FINAL
	printf("[%d]	[%d]	[%d]\n", *res[0], *res[1], *res[2]);
}

void *multiplica(void *p){
	int *fila=(int*)p;
	int res=0;

	for(int i=0; i<3; i++){
		res+=matriz[*fila][i]*vector[*fila];
	}
	printf("El resultado del hilo %d es %d\n", *fila, res);

	int *retorno=(int*)malloc(sizeof(int));
	*retorno=res;
	pthread_exit((void*)retorno);
}