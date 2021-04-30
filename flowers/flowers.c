#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int setWithBounds(char, int, int);
int checkBounds(int, int, int, int);
void addFlower(int, int, char**);
void addOutline(int, int, char**);
void kill2Darray(int, char**);
void print2Darray(int, int, char**, char*);

int main(int argc, char* argv[]) {
	
	srand(time(NULL)); // set random seed
	
	char** canvas;
	
	int sizeX = 10;
	int sizeY = 10;
	
	sizeX = setWithBounds('X', 1, 9999);
	sizeY = setWithBounds('Y', 1, 9999);
	
	canvas = (char**) malloc(sizeof(char*) * sizeY);
	
	for (int y = 0; y < sizeY; y++) {
		canvas[y] = malloc(sizeof(char) * sizeX);
		for (int x = 0; x < sizeX; x++) {
			canvas[y][x] = ',';
		}
	}
	
	printf("\x1b[33mHow many flowers do you want?\n\x1b[0m");
	int flowers = 0;
	scanf("%d", &flowers);
	for (int f = 0; f < flowers; f++){
		addFlower(sizeX, sizeY, canvas);
	}
	
	char color[] = "\x1b[97m";
	int choice = 0;
	//big ass, ugly print statements go brrr
	printf("\x1b[92mWhat colour do you want the flowers to be\n\t\x1b[97m0 - White\n\t\x1b[91m1 - Red\n\t\x1b[93m2 - Yellow\n\t\x1b[96m3 - Cyan\n\t\x1b[95m4 - Magenta\n\t\x1b[94m5 - Blue\n\x1b[0m");
	scanf("%d", &choice);
	while (choice < 0 || choice > 5) {
		printf("\x1b[31mBad Value: \x1b[92mWhat colour do you want the flowers to be\n\t\x1b[97m0 - White\n\t\x1b[91m1 - Red\n\t\x1b[93m2 - Yellow\n\t\x1b[96m3 - Cyan\n\t\x1b[95m4 - Magenta\n\t\x1b[94m5 - Blue\n\x1b[0m");
		scanf("%d", &choice);
	}
	switch (choice) {
		//white
		case 0 :
			strcpy(color, "\x1b[97m");
			break;
		//Red
		case 1 :
			strcpy(color, "\x1b[91m");
			break;
		//Yellow
		case 2 :
			strcpy(color, "\x1b[93m");
			break;
		//Cyan
		case 3 :
			strcpy(color, "\x1b[96m");
			break;
		//Magenta
		case 4 :
			strcpy(color, "\x1b[95m");
			break;
		//Blue
		case 5 :
			strcpy(color, "\x1b[94m");
			break;
	}
	
	addOutline(sizeX, sizeY, canvas);
	
	print2Darray(sizeX, sizeY, canvas, color);
	
	char filePrompt = 'n';
	printf("\x1b[33mDo you want a copy of the field (saved as flowers.txt)?: Y/n\n\x1b[0m");
	scanf(" %c", &filePrompt);
	if (filePrompt == 'Y' || filePrompt == 'y') {
		FILE * outputFile = fopen("flowers.txt", "w");
		for (int y = 0; y < sizeY; y++) {
			for (int x = 0; x < sizeX; x++) {
				fprintf(outputFile, "%c", canvas[y][x]);
			}
			fprintf(outputFile, "\n");
		}
		fclose(outputFile);
	}
	
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
	printf("\x1b[35mEnter a number within \x1b[36m%d\x1b[35m to \x1b[36m%d \x1b[35mfor \x1b[32m%c \x1b[35m:\x1b[0m\n", lower, upper, varName);
	scanf("%d", &input);
	while (input < lower || input > upper) {
		printf("\x1b[31mBad Value: \x1b[95mEnter a number within \x1b[36m%d\x1b[35m to \x1b[36m%d \x1b[35mfor \x1b[32m%c \x1b[35m:\x1b[0m\n", lower, upper, varName);
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

void print2Darray (int sizeX, int sizeY, char** array, char* color) {

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			char current = array[y][x];
			switch (current) {
				//The middle of the flower
				case 'O' : 
					printf("\x1b[33m%c\x1b[0m", current);
					break;
				//The upper left/bottom right petal
				case '\\' : 
					printf("%s%c\x1b[0m", color, current);
					break;
				//can be either the outline or the top/bottom petal
				case '|' : 
					if (x != 0 && x != sizeX-1) {
						printf("%s%c\x1b[0m", color, current);
					} else {
						printf("\x1b[31m%c\x1b[0m", current);
					}
					break;
				//The upper right/bottom left petal
				case '/' : 
					printf("%s%c\x1b[0m", color, current);
					break;
				//Either the outline or the right/left petal
				case '-' : 
					if (y != 0 && y != sizeY-1) {
						printf("%s%c\x1b[0m", color, current);
					} else {
						printf("\x1b[31m%c\x1b[0m", current);
					}
					break;
				//The corners of the outline
				case '.' : 
					printf("\x1b[31m%c\x1b[0m", current);
					break;
				//Everything else is assumed to be grass
				default  :
					printf("\x1b[92m%c\x1b[0m", current);
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