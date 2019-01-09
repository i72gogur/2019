//adproc2.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <semaphore.h>

#define NHIJOS 4

int main(){
	key_t key;
	pid_t pid;
	int status, shmid;
	int *contador=NULL;
	sem_t *mutex;
	void adder(int i, sem_t *mutex);

	//MEMORIA COMPARTIDA PARA CONTADOR
	key=ftok("adproc2.c", 1);
	shmid=shmget(key, sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("Error al obtener id para el contador\n");
		exit(EXIT_FAILURE);
	}
	contador=(int*)shmat(shmid, NULL, 0);
	if(contador==NULL){
		printf("Error al obtener puntero para contador\n");
		exit(EXIT_FAILURE);
	}
	*contador=0;

	//MEMORIA COMPARTIDA PARA SEMAFORO
	key=ftok("adproc2.c", 2);
	shmid=shmget(key, sizeof(sem_t), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("Error al obtener id para el semaforo\n");
		exit(EXIT_FAILURE);
	}
	mutex=(sem_t*)shmat(shmid, NULL, 0);
	if(mutex==NULL){
		printf("Error al obtener puntero para el semaforo\n");
		exit(EXIT_FAILURE);
	}

	sem_init(mutex, 1, 1);

	//CREACION DE NHIJOS
	for(int i=0; i<NHIJOS; i++){
		pid=fork();
		if(pid==-1){
			printf("Error al crear al hijo %d\n", i);
			exit(EXIT_FAILURE);
		}
		if(pid==0){
			adder(i, mutex);
			exit(0);
		}
	}

	//ESPERAMOS A QUE FINALICEN LOS NHIJOS
	for(int i=0; i<NHIJOS; i++){
		pid=wait(&status);
		printf("El hijo %d con pid %d termina con status %d\n", i, pid, WEXITSTATUS(status));
	}

	printf("RESULTADO = %d\n", *contador);

	shmdt(contador);
	shmdt(mutex);
	shmctl(shmid, IPC_RMID, NULL);
}

void adder(int i, sem_t *mutex){
	key_t key;
	int shmid, tmp;
	int *contador=NULL;

	//MEMORIA COMPARTIDA
	key=ftok("adproc2.c", 1);
	shmid=shmget(key, sizeof(int), 0);
	if(shmid==-1){
		printf("Error al obtener id para el contador\n");
		exit(EXIT_FAILURE);
	}
	contador=(int*)shmat(shmid, NULL, 0);
	if(contador==NULL){
		printf("Error al obtener puntero al contador\n");
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<100; i++){
		sem_wait(mutex);
			tmp=*contador;
			tmp++;
			*contador=tmp;
		sem_post(mutex);
	}

	shmdt(contador);

}