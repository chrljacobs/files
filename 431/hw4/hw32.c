#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

sem_t passAirArr, checkPer, secPer, checkLine, secLine, gateLine;
sem_t checkReady, secReady, gateReady, semDone, checkDone, gateDone;
int passNum = 0;
int checkNum = 0;
int secNum = 0;
int done = 0;
int checkDoneVar = 0;
int gateDoneVar = 0;

//the function for the passengers
void* passenger() {
//keep track of which passenger
int myPassNum;
sem_wait(&passAirArr);
passNum++;
myPassNum = passNum;
sem_post(&passAirArr);
//now passenger has number, can go through system
printf("\nPassenger %d has arrived at the airport.", myPassNum);
sem_post(&checkReady);
sem_wait(&checkLine);
printf("\nPassenger %d has a boarding pass.", myPassNum);
sem_post(&secReady);
sem_wait(&secLine);
printf("\nPassenger %d has cleared security.", myPassNum);
sem_post(&gateReady);
sem_wait(&gateLine);
printf("\nPassenger %d has boarded the plane.", myPassNum);
 pthread_exit(NULL);
}

//function for check in personel
void* checkin() {
sem_wait(&checkPer);
checkNum++;
int myCheckNum = checkNum;
sem_post(&checkPer);
while(1) {
	//code to break infinite loop
	sem_wait(&checkDone);
	if (checkDoneVar >= 25) {
		printf("\nCheck is done from %d.", myCheckNum);
		//release the other checkin from wait hell
		sem_post(&checkDone);
		sem_post(&checkReady);
		pthread_exit(NULL);
	}
	sem_post(&checkDone);
	sem_wait(&checkReady);
	//if released, make sure not done
	if (checkDoneVar >= 25) {}
	else
		printf("\nCheck-In agent %d has checked in a passenger.", myCheckNum);
	sem_wait(&checkDone);
	checkDoneVar++;
	sem_post(&checkDone);
	sem_post(&checkLine);
	}
}

void * security() {
sem_wait(&secPer);
secNum++;
int mySecNum = secNum;
sem_post(&secPer);
while(1) {
	sem_wait(&semDone);
	if (done >= 25) {
		printf("\nSecurity is done from %d.", mySecNum);
		sem_post(&semDone);
		sem_post(&secReady);
		 pthread_exit(NULL);

	}
	sem_post(&semDone);

        sem_wait(&secReady);
        if (done >= 25) {}
        else
                printf("\nSecurity guard %d has approved a passenger.", mySecNum);
	sem_wait(&semDone);
	done++;
	sem_post(&semDone);
	sem_post(&secLine);
        }
}

void * gate() {
while(1) {
	sem_wait(&gateDone);
	if (gateDoneVar >= 25) {
		printf("\nGate is done.");
		 pthread_exit(NULL);
	}
	sem_post(&gateDone);
        sem_wait(&gateReady);
        printf("\nThe gate gaurd has allowed a passenger to pass.");
	sem_wait(&gateDone);
	gateDoneVar++;
	sem_post(&gateDone);
	sem_post(&gateLine);
        }
}

int main() {

pthread_t threads[30];
sem_init(&passAirArr, 0, 1);
sem_init(&checkPer, 0, 1);
sem_init(&secPer, 0, 1);
sem_init(&gateReady, 0 ,0);
sem_init(&checkLine, 0, 2);
sem_init(&secLine, 0, 2);
sem_init(&gateLine, 0, 1);
sem_init(&checkReady, 0, 0);
sem_init(&secReady, 0, 0);
sem_init(&semDone, 0, 1);
sem_init(&checkDone, 0, 1);
sem_init(&gateDone, 0, 1);

time_t currentTime;
time(&currentTime);
printf("I am Christopher Jacobs, the current time is %s.", ctime(&currentTime));
//again, for pthread arguement errors
for (int i = 0; i < 25; i++) {
	pthread_create(&threads[i], NULL, passenger, i);
}
pthread_create(&threads[25], NULL, checkin, NULL);
pthread_create(&threads[26], NULL, checkin, NULL);
pthread_create(&threads[27], NULL, security, NULL);
pthread_create(&threads[28], NULL, security, NULL);
pthread_create(&threads[29], NULL, gate, NULL);

//start the threads
for (int i = 0; i < 30; i++) {
	pthread_join(threads[i], NULL);
}
return 0;
}
