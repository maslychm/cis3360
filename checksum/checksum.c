#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int valid[3] = {8, 16, 32};

void print80(char *str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (i % 80 == 0)
			printf("\n");
		printf("%c",str[i]);
	}
}

char calc8bit(char *input)
{
	int8_t result = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		printf("int %d\n", input[i]);
		result += input[i];
		printf("res %d\n", result);
		//result = result % 255;
	}

	return result;
}

char calc16bit(char *input)
{
	// each two characters should be added to checksum so input[i+1]input[i]
	int16_t result = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		printf("int %d\n", input[i]);
		result += input[i];
		printf("res %d\n", result);
	}

	return result;
}

char calc32bit(char *input)
{
	int32_t result = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		printf("%x\n", input[i]);
		result += input[i];
	}

	return result;
}

int main(int argc, char **argv)
{
    FILE	*inputfile;
	char *input, *output, *checksum, c = 'x';
	int8_t res8bit = 0;
	int16_t res16bit = 0;
	int32_t res32bit = 0;
	int	i = 0, 
			checksum_size = 0;

	// Wrong number of arguments passed
    if (argc != 3)
    {
		fprintf(stderr, "Please run as `checksum.c filename.txt 8/16/32`\n");
        return -1;
    }

	// Make sure checksum size is correct
    if (!(atoi(argv[2]) == 8 || atoi(argv[2]) == 16 || atoi(argv[2]) == 32))
    {
        fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
		return -1;
    }
	else
	{
		checksum_size = atoi(argv[2]);
	}

	// Open the input file
    if (!(inputfile = fopen(argv[1],"r")))
    {
        fprintf(stderr, "Could not open \"%s\"\n", argv[1]);
		return -1;
    }

	// Read in the input file
    input = malloc(sizeof(char) * 1024);
	while (fscanf(inputfile, "%c", &c) != EOF && i < 1024)
	{
		input[i] = c;
		i++;
	}
	//input[i + 1] = '\0';
	
	print80(input);
	
	fclose(inputfile);

	switch (checksum_size)
	{
	case 8:
		res8bit = calc8bit(input);
		break;
	case 16:
		res16bit = calc16bit(input);
		break;
	case 32:
		res32bit = calc32bit(input);
		break;
	}

	printf("\n%x\n",res8bit);
	printf("\n%x\n", res16bit);
	printf("\n%x\n", res32bit);
	//printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);

    return 0;
}