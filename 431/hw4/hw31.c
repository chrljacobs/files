#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

sem_t cabin, legRoom, first;

int cabAvail = 153;
int legAvail = 18;
int firstAvail = 16;
//struct to keep track of what each agent sold
struct agentTickets {
int cabSold;
int legSold;
int firstSold;
};
//initializing the agents to 0
struct agentTickets agent1 = {.cabSold = 0, .legSold = 0, .firstSold = 0};
struct agentTickets agent2 = {.cabSold = 0, .legSold = 0, .firstSold = 0};
struct agentTickets agent3 = {.cabSold = 0, .legSold = 0, .firstSold = 0};
//the function for the threads
void* agent(int *agentNum2) {
int sell = 1;
int randNum = 0;
//pthread requires a pointer for argument 4, which is why
//an int isn't passed directly
int agentNum1 = *agentNum2;
//a pointer to an agent that can be set based on if statements
struct agentTickets *pointer = NULL;
while(sell == 1) {
	//set the pointer to the right agent
	if (agentNum1 == 1) pointer = &agent1;
	else if (agentNum1 == 2) pointer = &agent2;
	else pointer = &agent3;
	randNum = rand()%3;
	//if there are no tickets, the threads are done
	if (cabAvail == 0 && legAvail == 0 && firstAvail == 0) sell = 0;
	//0 is cabin, 1 is extra leg room, and if not those, then first class
	else if (randNum == 0) {
		//protect race variable
		sem_wait(&cabin);
		//make sure it has tickets available
		if (cabAvail > 0) {
		//simulate customer buying a ticket very quickly (.1 sec)
			usleep(100);
			cabAvail--;
			pointer->cabSold++;
		}
		sem_post(&cabin);
	}
	else if (randNum == 1) {
		sem_wait(&legRoom);
                if (legAvail > 0) {
			usleep(100);
                        legAvail--;
                        pointer->legSold++;
                }
                sem_post(&legRoom);

	}
	else {
		sem_wait(&first);
                if (firstAvail > 0) {
			usleep(100);
                        firstAvail--;
                        pointer->firstSold++;
		}
                sem_post(&first);
	}
}
}

int main() {
srand(time(0));
pthread_t threads[3];
sem_init(&cabin, 0, 1);
sem_init(&legRoom, 0, 1);
sem_init(&first, 0, 1);
time_t currentTime;
time(&currentTime);
printf("I am Christopher Jacobs, the current time is %s.", ctime(&currentTime));
//again, for pthread arguement errors
int varI = 1;
int * varP = &varI;
pthread_create(&threads[0], NULL, agent, varP);
int varI2 = 2;
int * varP2 = &varI2;
pthread_create(&threads[1], NULL, agent, varP2);
int varI3 = 3;
int * varP3 = &varI3;
pthread_create(&threads[2], NULL, agent, varP3);
//start the threads
for (int i = 0; i < 3; i++) {
	pthread_join(threads[i], NULL);
}
int sum = 0;
//an array of the agents so I can use a for loop
struct agentTickets Arr[3] = {agent1,agent2,agent3};
for (int i = 0; i < 3; i++) {
printf("\nAgent%d sold %d cabin, %d extra leg room, and %d first class tickets.", 
	i+1, Arr[i].cabSold, Arr[i].legSold, Arr[i].firstSold);
//sum is the total number of tickets used for error checking. 
//fun fact, I think this was the only thing that worked first try
sum += Arr[i].cabSold+Arr[i].legSold+ Arr[i].firstSold;
}

printf("\nThe total number of tickets sold was %d.", sum);
return 0;
}
