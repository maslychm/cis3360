#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

FILE *plainFile, *keyFile;

char * stripInput(FILE * fileptr, int mode) {
	int i = 0;
	char c = 'x';
	char *array;
	
	array = malloc(sizeof(char) * 513);
	
	while (fscanf(fileptr,"%c",&c) != EOF && i < 512) {
		if(isalpha(c)) {
			array[i] = tolower(c);
			i++;
		}
	}
	
	if (mode == 1) {
		array[i] = '\0';
	}
	
	if (mode == 2) {
		for (i; i < 512; i++) {
			array[i] = 'x';
		}
		array[512] = '\0';
	}
	
	return array;
}

char * encrypt(char *text, char *key) {
	int i = 0;
	char *ciphertext;
	
	ciphertext = malloc(sizeof(char) * 513);
	
	for (i = 0; i < strlen(text); i++) {
		int c = (text[i] - 97 + key[i % strlen(key)] - 97) % 26  + 97;
		ciphertext[i] = c;// + 'a';
	}
	ciphertext[i] = '\0';
	return ciphertext;
}

int main(int argc, char **argv) {
	int i = 0;
	char *key, *text, *ciphertext;
	
	if (!(keyFile = fopen(argv[1], "r"))) {
		fprintf(stderr, "Could not open \"%s\"\n", argv[1]);
		return -1;
	}
	
	if (!(plainFile = fopen(argv[2], "r"))) {
        fprintf(stderr, "Could not open \"%s\"\n", argv[2]);
        return -1;
    }
	
	key = stripInput(keyFile, 1);
	text = stripInput(plainFile, 2);
	ciphertext = encrypt(text, key);
	
	printf("\n\nVigenere Key:\n");
	for (i = 0; i < strlen(key); i++)
	{
		if (i % 80 == 0)
			printf("\n");
		printf("%c",key[i]);
	}
	printf("\n\n");
	
	printf("Plaintext:\n");
	for (i = 0; i < strlen(text); i++)
	{
		if (i % 80 == 0)
			printf("\n");
		printf("%c",text[i]);
	}
	printf("\n\n");
	
	printf("Ciphertext:\n");
	for (i = 0; i < strlen(ciphertext); i++)
	{
		if (i % 80 == 0)
			printf("\n");
		printf("%c",ciphertext[i]);
	}
	printf("\n");
	return 0;
}