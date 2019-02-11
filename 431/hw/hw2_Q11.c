#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int fd[2], nbytes, waiting;
	pid_t childpid;
	char mystring[80];
	char readbuffer[80];
	pipe(fd);

	if ((childpid = fork()) == -1) {
	perror("fork");
	exit(1);
	}
	if(childpid != 0) {
		int arr[10] = {5,7,9,2,6,3,4,1,7,9};
		for (int i = 0 ; i < 10; i++) {
			mystring[i]=(char) arr[i];
		}
		close(fd[0]);
		write(fd[1], mystring, sizeof(mystring));
		waiting = wait(&waiting);
		printf("\nChild Process has finished, wait over.\n");
		exit(0);
	}

	else {
		int sum = 0;
		close(fd[1]);
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		for (int i = 0; i < 10; i++) {
			sum = sum + (int)readbuffer[i];
		}
		printf("Sum of Recieved Array: %d", sum);
	}
}
