#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd1;
	char readbuffer[80];
	int sum = 0;
	char * ages = "/tmp/ages";
	fd1 = open(ages, O_RDONLY);
	read(fd1, readbuffer, 80);
	for (int i = 0; i < 10; i++) {
		sum = sum + (int)readbuffer[i];
	}
	printf("Sum of Recieved Array: %d\n", sum);
	close(fd1);
	return 0;
	}

