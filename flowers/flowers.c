#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANSI_RED      "\x1b[31m"
#define ANSI_GREEN    "\x1b[32m"
#define ANSI_YELLOW   "\x1b[33m"
#define ANSI_BLUE     "\x1b[34m"
#define ANSI_MAGENTA  "\x1b[35m"
#define ANSI_CYAN     "\x1b[36m"
#define ANSI_WHITE    "\x1b[37m"
#define ANSI_RED2     "\x1b[91m"
#define ANSI_GREEN2   "\x1b[92m"
#define ANSI_YELLOW2  "\x1b[93m"
#define ANSI_BLUE2    "\x1b[94m"
#define ANSI_MAGENTA2 "\x1b[95m"
#define ANSI_CYAN2    "\x1b[96m"
#define ANSI_WHITE2   "\x1b[97m"
#define ANSI_RESET    "\x1b[0m"

int setWithBounds(char, int, int);
int checkBounds(int, int, int, int);
void addFlower(int, int, char**);
void addOutline(int, int, char**);
void kill2Darray(int, char**);
void print2Darray(int, int, char**);

int main(int argc, char* argv[]) {
	
	srand(time(NULL)); // set random seed
	
	char** canvas;
	
	int sizeX = 10;
	int sizeY = 10;
	
	sizeX = setWithBounds('X', 1, 255);
	sizeY = setWithBounds('Y', 1, 255);
	
	canvas = (char**) malloc(sizeof(char*) * sizeY);
	
	for (int y = 0; y < sizeY; y++) {
		canvas[y] = malloc(sizeof(char) * sizeX);
		for (int x = 0; x < sizeX; x++) {
			canvas[y][x] = ',';
		}
	}
	
	printf(ANSI_YELLOW "How many flowers do you want?\n" ANSI_RESET);
	int flowers = 0;
	scanf("%d", &flowers);
	for (int f = 0; f < flowers; f++){
		addFlower(sizeX, sizeY, canvas);
	}
	
	addOutline(sizeX, sizeY, canvas);
	
	print2Darray(sizeX, sizeY, canvas);
	
	kill2Darray(sizeY, canvas);
	
	return 0;
}

int setWithBounds(char varName, int lower, int upper) {
	int input;
	if (upper < lower){
		input = lower; // store lower to temp 
		lower = upper; // overwrite lower with upper
		upper = input; // set upper to lower's value in temp
	}
	printf(ANSI_MAGENTA "Enter a number within " ANSI_CYAN "%d" ANSI_MAGENTA " to " ANSI_CYAN "%d " ANSI_MAGENTA "for " ANSI_GREEN "%c " ANSI_MAGENTA ":" ANSI_RESET "\n", lower, upper, varName);
	scanf("%d", &input);
	while (input < lower || input > upper) {
		printf(ANSI_RED "Bad Value: " ANSI_MAGENTA "Enter a number within " ANSI_CYAN "%d" ANSI_MAGENTA " to " ANSI_CYAN "%d " ANSI_MAGENTA "for " ANSI_GREEN "%c " ANSI_MAGENTA ":" ANSI_RESET "\n", lower, upper, varName);
		scanf("%d", &input);
	}
	return input;
}

int checkBounds(int boundX, int boundY, int testX, int testY) {
	//checks if testX and testY fall between 0-boundX and 0-boundY respectively.
	//1 = valid coordinate, 0 = out of bounds
	//assumes the bounds are the size of the box, so it is decremented to be a valid index
	if (testX < 0 || testY < 0) {
		return 0;
	} else if (testX >= boundX || testY >= boundY) {
		return 0;
	}
	return 1;
}

void addFlower(int sizeX, int sizeY, char** canvas) {
	int x = rand() % (sizeX-2);
	int y = rand() % (sizeY-2);
	x++;
	y++;
	canvas[y][x] = 'O';
	if (checkBounds(sizeX, sizeY, x-1, y-1) == 1){
		canvas[y-1][x-1] = '\\';
	}
	if (checkBounds(sizeX, sizeY, x, y-1) == 1){
		canvas[y-1][x] = '|';
	}
	if (checkBounds(sizeX, sizeY, x+1, y-1) == 1){
		canvas[y-1][x+1] = '/';
	}
	if (checkBounds(sizeX, sizeY, x-2, y) == 1){
		canvas[y][x-2] = '-';
	}
	if (checkBounds(sizeX, sizeY, x-1, y) == 1){
		canvas[y][x-1] = '-';
	}
	if (checkBounds(sizeX, sizeY, x+1, y) == 1){
		canvas[y][x+1] = '-';
	}
	if (checkBounds(sizeX, sizeY, x+2, y) == 1){
		canvas[y][x+2] = '-';
	}
	if (checkBounds(sizeX, sizeY, x-1, y+1) == 1){
		canvas[y+1][x-1] = '/';
	}
	if (checkBounds(sizeX, sizeY, x, y+1) == 1){
		canvas[y+1][x] = '|';
	}
	if (checkBounds(sizeX, sizeY, x+1, y+1) == 1){
		canvas[y+1][x+1] = '\\';
	}
}

void addOutline(int sizeX, int sizeY, char** canvas) {
	
	for (int x = 0; x < sizeX; x++) {
		canvas[0][x]	   = '-';
		canvas[sizeY-1][x] = '-';
	}
	for (int y = 0; y < sizeY; y++) {
		canvas[y][0]	   = '|';
		canvas[y][sizeX-1] = '|';
	}
	canvas[0][0] 			 = '.';
	canvas[0][sizeX-1]		 = '.';
	canvas[sizeY-1][0]		 = '.';
	canvas[sizeY-1][sizeX-1] = '.';
}

void print2Darray (int sizeX, int sizeY, char** array) {

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			char current = array[y][x];
			switch (current) {
				case 'O' : 
					printf(ANSI_YELLOW "%c" ANSI_RESET, current);
					break;
				case '\\' : 
					printf(ANSI_WHITE2 "%c" ANSI_RESET, current);
					break;
				case '|' : 
					if (x != 0 && x != sizeX-1) {
						printf(ANSI_WHITE2 "%c" ANSI_RESET, current);
					} else {
						printf(ANSI_RED2 "%c" ANSI_RESET, current);
					}
					break;
				case '/' : 
					printf(ANSI_WHITE2 "%c" ANSI_RESET, current);
					break;
				case '-' : 
					if (y != 0 && y != sizeY-1) {
						printf(ANSI_WHITE2 "%c" ANSI_RESET, current);
					} else {
						printf(ANSI_RED2 "%c" ANSI_RESET, current);
					}
					break;
				case '.' : 
					printf(ANSI_RED2 "%c" ANSI_RESET, current);
					break;
				default  :
					printf(ANSI_GREEN2 "%c" ANSI_RESET, current);
			}
		}
		printf("\n");
	}
}

void kill2Darray (int firstSize, char** array) {
	for (int y = 0; y < firstSize; y++) {
		free(array[y]);
	}
	free(array);
}