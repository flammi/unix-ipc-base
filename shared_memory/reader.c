#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, const char *argv[])
{
	//Allocate shared memory
       	int shm_id = shmget(124, 255, 0);
	printf("shm_id: %d\n", shm_id);

	if(shm_id == -1) {
		perror("shmget:");
		exit(-1);
	}
	
	//Attach shared memory to our address space
	void *shared_memory = shmat(shm_id,0,0);
	if(shared_memory == (void*) -1) {
		perror("shmat:");
		exit(-1);
	}

	printf("Message: %s", (char*) shared_memory);

	//Detach memory
	if(-1 == shmdt(shared_memory)) {
		perror("shmdt:");
		exit(-1);
	}

	//Destroy memory
	shmctl(shm_id, IPC_RMID, NULL);

	return 0;
}
