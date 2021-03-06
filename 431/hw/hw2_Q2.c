#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sema;
sem_t sema2;
int number = 0;

void* getUser(){
while (1) {
sem_wait(&sema);
printf("Please enter a number between 0 and 20: ");
scanf("%d", &number);
sem_post(&sema2);
}
}

void* getRand() {
srand(time(0));
while(1) {
int random = rand() % 20;
sem_wait(&sema2);
if (random == number)
	printf("Correct!\n");
else
	printf("Incorrect\n");
sem_post(&sema);
}
}

int main() {
sem_init(&sema, 0, 1);
sem_init(&sema2,0,0);
pthread_t threads[2];
pthread_create(&threads[0], NULL, getUser, NULL);
pthread_create(&threads[1], NULL, getRand, NULL);
pthread_join(threads[0], NULL);
pthread_join(threads[1], NULL);

return 0;
}
