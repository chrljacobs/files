#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

sem_t sem1, sem2, sem3;
char colArr[5][6] = {"green","red","yellow","orange","purple"};
char color1[6];
char color2[6];
char color3[6];

void strCop(char arr[], char arr2[]) {
for (int i = 0; i < 6; i++) {
	arr[i] = arr2[i];
	}
}

int strCmp(char arr[], char arr2[]) {
for (int i = 0; i < 6; i++) {
       if ( arr[i] != arr2[i]) return 1;
        }
return 0;
}

void* getCol1(){
	int random = rand() % 5 + 1;
	strCop(color1, colArr[random-1]);
	sem_post(&sem1);
}

void* getCol2(){
        int random = rand() % 5 + 1;
        strCop(color2, colArr[random-1]);
	sem_post(&sem2);
}

void* getCol3(){
        int random = rand() % 5 + 1;
        strCop(color3, colArr[random-1]);
	sem_post(&sem3);
}

int main() {
srand(time(0));
pthread_t threads[3];
sem_init(&sem1, 0, 0);
sem_init(&sem2, 0, 0);
sem_init(&sem3, 0, 0);
time_t currentTime;
time(&currentTime);
printf("I am Christopher Jacobs, the current time is %s", ctime(&currentTime));
pthread_create(&threads[0], NULL, getCol1, NULL);
pthread_create(&threads[1], NULL, getCol2, NULL);
pthread_create(&threads[2], NULL, getCol3, NULL);
pthread_join(threads[0], NULL);
pthread_join(threads[1], NULL);
pthread_join(threads[2], NULL);
sem_wait(&sem1);
sem_wait(&sem2);
sem_wait(&sem3);
if (strCmp(color1, color2) == 0) {
	printf("Threads 1 and 2 are the winner!\n");
	}
else if (strCmp(color3, color2) == 0) {
	printf("Threads 2 and 3 are the winner!\n");
	}
else if (strCmp(color1, color3) == 0) {
	printf("Threads 1 and 3 are the winner!\n");
	}
else {
	printf("There were no winners in this game of chance.\n");
	}
return 0;
}
