//adproc3.c

#include <stdio.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define NHIJOS 4
#define M 25

int main(){
	key_t key;
	pid_t pid;
	int shmid, suma=0, status;
	int *vector=NULL;
	sem_t *mutex;
	void funcion(int i, sem_t *mutex);

	//MEMORIA COMPARTIDA PARA VECTOR
	key=ftok("adproc3.c", 1);
	shmid=shmget(key, M*sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("Error al obtener id para el vector\n");
		exit(EXIT_FAILURE);
	}
	vector=(int*)shmat(shmid, NULL, 0);
	if(vector==NULL){
		printf("Error al obtener puntero para vector\n");
		exit(EXIT_FAILURE);
	}

	//inicializamos el vector a 0
	for(int i=0; i<M; i++){
		vector[i]=0;
	}

	//MEMORIA COMPARTIDA PARA SEMAFORO
	key=ftok("adproc3.c", 2);
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

	//CREAMOS NHIJOS
	for(int i=0; i<NHIJOS; i++){
		pid=fork();
		if(pid==-1){
			printf("Error al crear al hijo %d\n", i);
			exit(EXIT_FAILURE);
		}
		if(pid==0){
			funcion(i, mutex);
			exit(0);
		}
	}

	//ESPERAMOS A QUE FINALICEN LOS NHIJOS
	for(int i=0; i<NHIJOS; i++){
		pid=wait(&status);
		printf("El proceso %d con pid %d termina con status %d\n", i, pid, WEXITSTATUS(status));
	}

	//RESULTADO
	for(int i=0; i<M; i++){
		suma+=vector[i];
	}
	printf("RESULTADO = %d\n", suma);

	shmdt(vector);
	shmdt(mutex);
	shmctl(shmid, IPC_RMID, NULL);
}

void funcion(int i, sem_t *mutex){
	key_t key;
	int shmid, indice;
	int *vector=NULL;
	srand(time(NULL));

	//MEMORIA COMPARTIDA
	key=ftok("adproc3.c", 1);
	shmid=shmget(key, M*sizeof(int), 0);
	if(shmid==-1){
		printf("Error al obtener id para mem compartida\n");
		exit(EXIT_FAILURE);
	}
	vector=(int*)shmat(shmid, NULL, 0);
	if(vector==NULL){
		printf("Error al obtener puntero al vector\n");
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<100; i++){
		sem_wait(mutex);
			indice=rand()%M;
			vector[indice]++;
		sem_post(mutex);
	}

	shmdt(vector);
}