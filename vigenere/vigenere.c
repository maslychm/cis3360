#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

FILE *plainFile, *keyFile;
char *key, ciphertext[513];

/*
	Take only alphabetic chars and make them lower
*/
int stripInput(FILE * fileptr, char *array, int mode) {
	int i = 0;
	char c = 'x';
	
	while (fscanf(fileptr,"%c",&c) != EOF && i < 512) {
		if(isalpha(c))
		{
			array[i] = tolower(c);
			i++;
		}
	}
	
	if (mode == 1) {
		array[i] = '\0';
		key = malloc(sizeof(char) * strlen(array) + 1);
		strcpy(key, array);
	}
	
	if (mode == 2) {
		for (i; i < 512; i++)
		{
			array[i] = 'x';
		}
		array[512] = '\0';
	}
	
	return 0;
}

int encrypt(char *text)
{
	int i = 0, j = 0;
	for (i = 0; i < strlen(text); i++)
	{
		int c = (text[i] - 97 + key[i % strlen(key)] - 97) % 26  + 97;
		ciphertext[i] = c;// + 'a';
	}
	ciphertext[i] = '\0';
	return 0;
}

int main(int argc, char **argv)
{
	int i = 0;
	char keyBuffer[1024], text[513];
	
	if (!(keyFile = fopen(argv[1], "r"))) {
		fprintf(stderr, "Could not open \"%s\"\n", argv[1]);
		return -1;
	}
	
	if (!(plainFile = fopen(argv[2], "r"))) {
        fprintf(stderr, "Could not open \"%s\"\n", argv[2]);
        return -1;
    }
	
	stripInput(keyFile, keyBuffer, 1);
	stripInput(plainFile, text, 2);
	encrypt(text);
	
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