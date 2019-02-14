#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

FILE *plainFile, *keyFile;
char c, text[513], keyBuffer[1024], 
	*key, ciphertext[513];

/* 
	Open files and return 0 if no error 
*/
int openFiles(char *keyf, char* textf)
{
	if (!(keyFile = fopen(keyf, "r")))
	{
		fprintf(stderr, "Could not open \"%s\"\n", keyf);
		return -1;
	}
	
	if ( !(plainFile = fopen(textf, "r")) )
    {
        fprintf(stderr, "Could not open \"%s\"\n", textf);
        return -1;
    }
	
	return 0;
}

/*
	Take only alphabetic chars and make them lower
*/
int stripInput(FILE * fileptr, int mode)
{
	int i = 0;
	int charcnt = 0;
	
	if (mode == 1)
	{
		while (fscanf(fileptr,"%c",&c) != EOF && charcnt < 512)
		{
			//printf("ye");
			if(isalpha(c))
			{
				//printf("charhere");
				keyBuffer[i] = tolower(c);
				i++;
			}
			charcnt++;
		}
		keyBuffer[i] = '\0';
		key = malloc(sizeof(char) * strlen(keyBuffer) + 1);
		strcpy(key, keyBuffer);
		charcnt = 0;
	}
	
	if (mode == 2)
	{
		while(fscanf(fileptr,"%c",&c) != EOF && i < 512)
		{	
			if(isalpha(c))
			{
				//printf("charhere");
				text[i] = tolower(c);
				i++;
			}
		}
		for (i; i < 512; i++)
		{
			text[i] = 'x';
		}
		text[512] = '\0';
		//printf("\n\n\nchar %d, i %d",charcnt, i);
	}
	
	return 0;
}

int encrypt()
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
	
	if (openFiles(argv[1],argv[2]) != 0)
		return -1;
	
	if (stripInput(keyFile, 1) != 0)
		return -1;
	
	if (stripInput(plainFile, 2) != 0)
		return -1;
	
	if (encrypt() != 0)
		return -1;
	
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