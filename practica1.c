//practica1.c
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <time.h>


int main(){
	key_t key; //clave para memoria compartida
	pid_t pid; //identificador para los procesos hijos
	int status; //para guardar el estado con el que finalizan los hijos
	int shmid; //identificador para memoria compartida
	int *memoria=NULL; //vector compartido
	struct shmid_ds buf;
	srand(time(NULL)); //iniciamos semilla para numeros aleatorios
	int alea;
	void hijo1();
	void hijo2();
	void hijo3();

	//MEMORIA COMPARTIDA
	key=ftok("practica1.c", 1);
	shmid=shmget(key, 10*sizeof(int), IPC_CREAT | 0777);
	if(shmid==-1){
		printf("Error al obtener id para la memoria compartida\n");
		exit(EXIT_FAILURE);
	}
	memoria=(int*)shmat(shmid, NULL, 0);
	if(memoria==NULL){
		printf("Error al obtener el puntero a la zona de memoria compartida\n");
		exit(EXIT_FAILURE);
	}


	//EL PROCESO PADRE RELLENA EL VECTOR CON VALORES ALEATORIOS
	for(int i=0; i<10; i++){
		alea=rand()%1000;
		memoria[i]=alea;
	}

	//CREACION DEL HIJO 1
	pid=fork(); //devuelve 0 al hijo y el pid del hijo al padre
	if(pid==-1){
		printf("Error al crear al hijo 1\n");
		exit(EXIT_FAILURE);
	}
	if(pid==0){
		hijo1();
		exit(0);
	}

	//ESPERAMOS A QUE FINALICE EL HIJO 1
	pid=wait(&status);
	printf("El hijo 1 con pid=%d termina con status %d\n", pid, WEXITSTATUS(status));

	//CREACION DEL HIJO 2
	pid=fork();
	if(pid==-1){
		printf("Error al crear al hijo 2\n");
		exit(EXIT_FAILURE);
	}
	if(pid==0){
		hijo2();
		exit(0);
	}

	//ESPERAMOS A QUE FINALICE EL HIJO 2
	pid=wait(&status);
	printf("El hijo 2 con pid=%d termina con status %d\n", pid, WEXITSTATUS(status));

	//CREACION DEL HIJO 3
	pid=fork();
	if(pid==-1){
		printf("Error al crear al hijo 3\n");
		exit(EXIT_FAILURE);
	}
	if(pid==0){
		hijo3();
		exit(0);
	}

	//ESPERAMOS A QUE FINALICE EL HIJO 3
	pid=wait(&status);
	printf("El hijo 3 con pid=%d termina con status %d\n", pid, WEXITSTATUS(status));

	shmdt(memoria); //liberamos memoria
	shmctl(shmid, IPC_RMID, &buf); //borramos la memoria
}


void hijo1(){
	key_t key;
	int shmid;
	int *memoria=NULL;
	int indice, valor;

	//MEMORIA COMPARTIDA
	key=ftok("practica1.c", 1);
	shmid=shmget(key, 10*sizeof(int), 0);
	if(shmid==-1){
		printf("Error al obtener id para la memoria compartida desde el hijo 1\n");
		exit(EXIT_FAILURE);
	}
	memoria=(int*)shmat(shmid, NULL, 0);
	if(memoria==NULL){
		printf("Error al obtener puntero a la zona de memoria compartida desde el hijo 1\n");
		exit(EXIT_FAILURE);
	}

	//ACCIONES HIJO 1
	for(int i=0; i<10; i++){
		printf("Introduzca un indice y un valor\n");
		scanf("%d\n%d", &indice, &valor);
		memoria[indice]=valor;
		printf("Se ha almacenado el valor %d en el indice %d\n", valor, indice);
	}

	shmdt(memoria); //liberamos memoria

}

void hijo2(){
	key_t key;
	int shmid;
	int *memoria=NULL;
	int indice, valor;

	//MEMORIA COMPARTIDA
	key=ftok("practica1.c", 1);
	shmid=shmget(key, 10*sizeof(int), 0);
	if(shmid==-1){
		printf("Error al obtener id para la memoria compartida desde el hijo 2\n");
		exit(EXIT_FAILURE);
	}
	memoria=(int*)shmat(shmid, NULL, 0);
	if(memoria==NULL){
		printf("Error al obtener puntero a la zona de memoria compartida desde el hijo 2\n");
		exit(EXIT_FAILURE);
	}

	//ACCIONES HIJO 2
	for(int i=0; i<10; i++){
		indice=rand()%10;
		valor=rand()%200;
		memoria[indice]=valor;
		printf("Se ha introducido el valor %d en el indice %d\n", valor, indice);
		sleep(1);
	}

	shmdt(memoria);
}

void hijo3(){
	key_t key;
	int shmid;
	int *memoria=NULL;
	int suma=0;

	//MEMORIA COMPARTIDA
	key=ftok("practica1.c", 1);
	shmid=shmget(key, 10*sizeof(int), 0);
	if(shmid==-1){
		printf("Error al obtener id para la memoria compartida desde el hijo 3\n");
		exit(EXIT_FAILURE);
	}
	memoria=(int*)shmat(shmid, NULL, 0);
	if(memoria==NULL){
		printf("Error al obtener puntero a la zona de memoria compartida desde el hijo 3\n");
		exit(EXIT_FAILURE);
	}

	//ACCIONES HIJO 3
	for(int i=0; i<5; i++){
		for(int z=0; z<10; z++){
			printf("ELEMENTO %d=%d\n", z, memoria[z]);
		}
		for(int j=0; j<10; j++){
			suma+=memoria[j];
		}
		printf("La suma de los elementos del vector es: %d\n", suma);
		sleep(30);
	}

	shmdt(memoria);
}