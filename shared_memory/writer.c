#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, const char *argv[])
{
	printf("Enter a message you want to send to shared memory...\n");
	char message[255];
	if(!fgets(message, 255, stdin)) {
		perror("Error on message read...");
		exit(-1);
	}

	printf("%s", message);


	//Allocate shared memory
       	int shm_id = shmget(124, 255, IPC_CREAT | 0600);
	printf("shm_id: %d", shm_id);

	if(!shm_id) {
		perror("shmget:");
		exit(-1);
	}

	//Attach shared memory to our address space
	void *shared_memory = shmat(shm_id,0,0);
	if(shared_memory == (void*) -1) {
		perror("shmat:");
		exit(-1);
	}

	//Write message to shared memory
	strcpy(shared_memory, message); 
	
	return 0;
}
