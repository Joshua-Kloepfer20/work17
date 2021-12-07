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

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buff;
};

int main(int argc, char *argv[]) {
	if (argc == 2 && strcmp(argv[1], "create") == 0) {
		int file = open("telephone.txt", O_CREAT | O_TRUNC, 0644);
		int semd = semget(KEY, 1, IPC_CREAT | 0644);
		union semun us;
		us.val = 1;
		semctl(semd, 0, SETVAL, us);
		int shmd = shmget(KEY, sizeof(int), IPC_CREAT | 0640);
	}
	else if (argc == 2 && strcmp(argv[1], "remove") == 0) {
		int shmd = shmget(KEY, sizeof(int), 0);
		int semd = semget(KEY, 0, 0);
		semctl(semd, IPC_RMID, 0);
		shmctl(shmd, IPC_RMID, 0);
		char story[1000];
		int fd_story = open("telephone.txt", O_RDONLY);
		int x = read(fd_story, story, 1000);
		story[x] = '\0';
		printf("%s", story);
	}
	return 0;
}
