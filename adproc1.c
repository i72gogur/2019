//adproc1.c

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define NHIJOS 3

int matriz[3][3]={1, 2, 3, 1, 3, 2, 2, 1, 3};
int vector[3]={1, 3, 2};

int main(){
	key_t key;
	pid_t pid;
	int shmid, status;
	int *res=NULL;
	void multiplica(int i);

	//MEMORIA COMPARTIDA PARA RESULTADO
	key=ftok("adproc1.c", 1);
	shmid=shmget(key, 3*sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("Error al obtener id para el vector\n");
		exit(EXIT_FAILURE);
	}
	res=(int*)shmat(shmid, NULL, 0);
	if(res==0){
		printf("Error al obtener puntero al vector\n");
		exit(EXIT_FAILURE);
	}

	//CREACION DE NHIJOS
	for(int i=0; i<NHIJOS; i++){
		pid=fork();
		if(pid==-1){
			printf("Error al crear al hijo %d\n", i);
			exit(EXIT_FAILURE);
		}
		if(pid==0){
			multiplica(i);
			exit(0);
		}
	}

	//ESPERAMOS A QUE FINALICEN LOS NHIJOS
	for(int i=0; i<NHIJOS; i++){
		pid=wait(&status);
		printf("El hijo %d con pid %d finaliza con status %d\n", i, pid, WEXITSTATUS(status));
	}

	printf("[%d]	[%d]	[%d]\n", res[0], res[1], res[2]);

	shmdt(res);
	shmctl(shmid, IPC_RMID, NULL);
}

void multiplica(int i){
	key_t key;
	int shmid;
	int *res=NULL;
	int aux=0;

	//MEMORIA COMPARTIDA
	key=ftok("adproc1.c", 1);
	shmid=shmget(key, 3*sizeof(int), 0);
	if(shmid==-1){
		printf("Error al obtener id para la memoria compartida\n");
		exit(EXIT_FAILURE);
	}
	res=(int*)shmat(shmid, NULL, 0);
	if(res==NULL){
		printf("Error al obtener el puntero a la zona de memoria compartida\n");
		exit(EXIT_FAILURE);
	}

	for(int j=0; j<3; j++){
		aux+=matriz[i][j]*vector[i];
	}
	res[i]=aux;
	shmdt(res);
}