#include <stdlib.h>
#include <stdio.h>

void main() {
//fork to produce a child process
if (fork()) {
//if fork is true, then this is the parent process
	printf("\nThis is the parent.\n");
	//simple for loop to print even numbers from 0 to 100
	for (int i = 0; i<=100; i+=2)
	{
	printf("%d ",i);
	}
}
else {
	printf("\nANd this one is the child.\n");
//another simple for loop that prints the odd numbers... but backwards!
	for (int i = 99; i>=1; i-=2)
	{
	printf("%d ",i);
	}
}
}
