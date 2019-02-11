#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void)
{
	int fd[2], nbytes;
	pid_t childpid;
	int users = 95;
	char mystring[80];
	char readbuffer[80];
	char digit1,digit2;

	digit1 = (char) users%10;
	digit2 = (char) users/10;

	mystring[0] = digit1;
	mystring[1] = digit2;
	printf("%d %d\n", mystring[0],mystring[1]);

	pipe(fd);

	if ((childpid = fork()) == -1) {
	perror("fork");
	exit(1);
	}
	if(childpid == 0) {
		close(fd[0]);
		write(fd[1], mystring, sizeof(mystring));
		exit(0);
	}

	else {
		close(fd[1]);
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Received string: %d %d\n", readbuffer[0], readbuffer[1]);
	}
}
