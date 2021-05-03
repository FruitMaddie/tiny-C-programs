#include <stdio.h>
//this is to check if letters are even or odd.

int main () {
	char letters [53]= {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'K', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};
	int i = 0;
	while (letters[i] != '\0') {
		if (letters[i] % 2 == 0) {
			printf("%c is even\n", letters[i]);
		} else {
			printf("%c is odd\n", letters[i]);
		}
		i++;
	}
	return 0;
}