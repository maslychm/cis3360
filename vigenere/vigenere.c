#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char * stripInput(FILE * fileptr, char mode) 
{
	int i = 0;
	char c = 'x', *str;
	
	str = malloc(sizeof(char) * 513);
	
	while (fscanf(fileptr,"%c",&c) != EOF && i < 512) 
	{
		if(isalpha(c)) 
		{
			str[i] = tolower(c);
			i++;
		}
	}
	
	if (mode == 'k')
	{
		str[i] = '\0';
	}
	
	if (mode == 'p') 
	{
		for (i; i < 512; i++)
		{
			str[i] = 'x';
		}
		str[512] = '\0';
	}
	
	return str;
}

char * encrypt(char *text, char *key) 
{
	int i = 0;
	char *ciphertext;
	
	ciphertext = malloc(sizeof(char) * 513);
	
	for (i = 0; i < strlen(text); i++) {
		int c = (text[i] - 97 + key[i % strlen(key)] - 97) % 26  + 97;
		ciphertext[i] = c;
	}
	ciphertext[i] = '\0';
	return ciphertext;
}

void printOut(char *str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (i % 80 == 0)
			printf("\n");
		printf("%c",str[i]);
	}
}

int main(int argc, char **argv) 
{
	FILE *plainFile, *keyFile;
	char *key, *text, *ciphertext;
	
	if (!(keyFile = fopen(argv[1], "r"))) 
	{
		fprintf(stderr, "Could not open \"%s\"\n", argv[1]);
		return -1;
	}
	
	if (!(plainFile = fopen(argv[2], "r"))) 
	{
        fprintf(stderr, "Could not open \"%s\"\n", argv[2]);
        return -1;
    }
	
	key = stripInput(keyFile, 'k');
	text = stripInput(plainFile, 'p');
	ciphertext = encrypt(text, key);
	
	printf("\n\nVigenere Key:\n");
	printOut(key);
	
	printf("\n\n\nPlaintext:\n");
	printOut(text);
	
	printf("\n\n\nCiphertext:\n");
	printOut(ciphertext);
	printf("\n");
	
	free(key);
	free(text);
	free(ciphertext);
	
	return 0;
}