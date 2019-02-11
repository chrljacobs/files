#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd1;
	char * ages = "/tmp/ages";
	char mystring[80];
	int arr[10] = {5,7,9,2,6,3,4,1,7,9};
	for (int i = 0 ; i < 10; i++) {
		mystring[i]=(char) arr[i];
	}
	mkfifo(ages, 0666);
	fd1 = open(ages, O_WRONLY);
	write(fd1, mystring, sizeof(mystring));
	close(fd1);
	unlink(ages);
	return 0;
}
