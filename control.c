#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define KEY 24016

int main(int argc, char *argv[]) {
	if (argc == 2 && strcmp(argv[1], "create") == 0) {
		int file = open("telephone.txt", O_CREAT | O_TRUNC, 0644);
		int semd = semget(KEY, 2, IPC_CREAT | 0644);
		int shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
	}
	else if (argc == 2 && strcmp(argv[1], "remove") == 0) {
		int shmd = shmget(KEY, sizeof(int), 0);
		int semid = semget(KEY, 1, 0);
		semctl(semid, IPC_RMID, 0);
		shmctl(shmd, IPC_RMID, 0);
	}
	return 0;
}
