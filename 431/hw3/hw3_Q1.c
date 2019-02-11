#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

struct page {
int pageNum;
int R;
};

int findPage(struct page frames[], int pageNum) {
	for (int i = 0; i < 10; i++) {
		if (frames[i].pageNum == pageNum) return i;
	}
	return 0;
}

int isFull(struct page frames[]) {
	for(int i = 0; i < 10; i++) {
		if (frames[i].pageNum == 0) return i;
	}
	return -1;
}

int main() {
srand(time(0));
int randNum = 0;
int place = -1;
int pageFaults = 0;
int pageFound = 0;
int full = 0;
struct page pageReq;
struct page frames[10] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
for (int i = 0; i < 50; i++) {
	randNum = rand() % 30 + 1;
	printf("%d, ", randNum);
	pageReq.pageNum = randNum;
	pageReq.R = 0;
	pageFound = findPage(frames, pageReq.pageNum);
	if (pageFound == 0) {
		full = isFull(frames);
		if (full == -1) {
			pageFaults++;
			for (int i = 0; i < 11; i++) {
				place++;
				if (i == 10) {
					frames[place%10] = pageReq;
					break;
				}
				if (frames[place%10].R == 0) {
					frames[place%10] = pageReq;
					break;
				}
				else {
					frames[place%10].R = 0;
				}
			}
		}
		else {
			frames[full] = pageReq;
		}
	}
	else {
		frames[pageFound].R = 1;
	}
}
printf("\nThe number of page faults was %d.\n", pageFaults);
for (int i = 0; i < 10; i++) {
	printf("%d ",frames[i].pageNum);
}
printf("\n");
return 0;
}
