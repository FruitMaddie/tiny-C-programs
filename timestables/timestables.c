#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	int** timestable;
	int sizeY = 10;
	int sizeX = 10;
	
	printf("Enter an int for X\n");
	scanf("%d", &sizeX);
	printf("Enter an int for Y\n");
	scanf("%d", &sizeY);
	printf("\n");
	
	timestable = (int**) malloc(sizeof(int*) * sizeY);
	
	for (int y = 0; y < sizeY; y++) {
		timestable[y] = (int*) malloc(sizeof(int) * sizeX);
		for (int x = 0; x < sizeX; x++) {
			timestable[y][x] = ((x+1) * (y+1));
			printf("%d\t", timestable[y][x]);
		}
		printf("\n");
	}
	
	int fuckX;
	int fuckY;
	
	printf("Enter an column to fuck up:\n");
	scanf("%d", &fuckX);
	while (fuckX > sizeX || fuckX-1 < 0) {
		printf("get it right dickweed:\n");
		scanf("%d", &fuckX);
	}
	
	printf("Enter an row to fuck up:\n");
	scanf("%d", &fuckY);
	while (fuckY > sizeY || fuckY-1 < 0) {
		printf("get it right dickweed:\n");
		scanf("%d", &fuckY);
	}
	fuckX--;
	fuckY--;
	
	for (int y = 0; y < sizeY; y++) {
		timestable[y][fuckX] = timestable[y][fuckX] * 10;
	}
	for (int x = 0; x < sizeX; x++) {
		timestable[fuckY][x] = timestable[fuckY][x] * -1;
	}
	
	printf("Fuckery done, enjoy:\n");
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			printf("%d\t", timestable[y][x]);
		}
		printf("\n");
	}
	
	//eliminate 2d array
	for (int y = 0; y < sizeY; y++) {
		free(timestable[y]);
	}
	free(timestable);
	
	return 0;
}
