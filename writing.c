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

int main() {
	int semd = semget(KEY, 1, 0);
	int shmd = shmget(KEY, sizeof(int), 0);
	int fd = open("telephone.txt", O_RDWR);
	int *len = shmat(shmd, 0, 0);
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_op = -1;
	semop(semd, &sb, 1);
	char line[100];
	lseek(fd, -(*len), SEEK_END);
	int x = r ead(fd, line, *len);
	line[x] = '\0';
	printf("last line of story: %s\n", line);
	printf("Addition: ");
	char add[100];
	fgets(add, 99, stdin);
	*len = strlen(add);
	write(fd, add, *len);
	shmdt(len);
	sb.sem_op = 1;
	semop(semd, &sb, 1);
	return 0;
}
