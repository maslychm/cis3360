#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char **argv)
{
    FILE *inputfile;
    char *input, *checksum;

    if (argc != 3)
    {
        return -1;
    }

    if (!(atoi(argv[2]) == 8 || atoi(argv[2]) == 16 || atoi(argv[2]) == 32))
    {
		//printf("%s \n",argv[2]);
		//printf("%d", atoi(argv[2]));
        fprintf(stderr,"Valid checksum sizes are 8, 16, or 32\n");
		return -1;
    }

    if (!(inputfile = fopen(argv[1],"r")))
    {
        fprintf(stderr, "Could not open \"%s\"\n", argv[1]);
		return -1;
    }

    char c = 'x';
    int i = 0;
    input = malloc(sizeof(char) * 1024);
	
	while (fscanf(inputfile, "%c", &c) != EOF && i < 1024)
	{
		input[i] = c;
		i++;
	}
	input[i + 1] = '/0';

	fclose(inputfile);

	print80(input);

	char result = 0;
	for (i = 0; i < strlen(input); i++)
	{
		printf("%x\n",input[i]);
		result += input[i];
	}

	printf("\n%x\n",result);
	//printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);

    return 0;
}