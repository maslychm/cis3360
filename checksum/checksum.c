#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

int calc8bit(char *input)
{
	int result = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		result += input[i];
	}

	return result;
}

int calc16bit(char *input)
{
	int res16bit = 0;
	for (int i = 0; i < strlen(input);)
	{
		res16bit += input[i] << 8;
		res16bit += (input[i + 1]);
		i+=2;
	}

	return res16bit;
}

int calc32bit(char *input)
{
	unsigned long long int res32bit = 0;
	for (int i = 0; i < strlen(input);)
	{
		res32bit += input[i] << 24;
		res32bit += (input[i + 1]) << 16;
		res32bit += (input[i + 2]) << 8;
		res32bit += (input[i + 3]);
		i+=4;
	}
	
	return res32bit;
}

int main(int argc, char **argv)
{
    FILE	*inputfile;
	char *input, *output, *checksum, c = 'x';
	int res8bit = 0;
	int res16bit = 0;
	int res32bit = 0;
	int	i = 0; 
	int checksum_size = 0;

	// Wrong number of arguments passed
    if (argc != 3)
    {
		fprintf(stderr, "Please run as `checksum.c filename.txt 8/16/32`\n");
        return -1;
    }

	// Make sure checksum size is correct
	checksum_size = atoi(argv[2]);
    if (!(checksum_size == 8 || checksum_size == 16 || checksum_size == 32))
    {
        fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
		return -1;
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
	input[i + 1] = '\0';
	
	// Close the file
	fclose(inputfile);
	
	switch (checksum_size)
	{
	case 8:
		res8bit = calc8bit(input);
		print80(input);
		printf("\n");
		printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, res8bit & 0xff, strlen(input));
		//printf("%x\n",res8bit & 0xff);
		break;
	case 16:
		if (strlen(input) % 2)
			strcat(input,"X");
		print80(input);
		printf("\n");
		res16bit = calc16bit(input);
		printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, res16bit & 0xffff, strlen(input));
		//printf("%x\n",res16bit & 0xffff);
		break;
	case 32:
		while (strlen(input) % 4)
			strcat(input,"X");
		print80(input);
		printf("\n");
		res32bit = calc32bit(input);
		printf("%2d bit checksum is %8lx for all %4d chars\n", checksum_size, res32bit & 0xffffffff, strlen(input));
		//printf("%llx\n",res32bit & 0xffffffff);
		break;
	}
	
    return 0;
}