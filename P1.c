#include <stdio.h>

#define IN 1 /*В слове*/
#define OUT 0 /*Не в слове*/

#define END 1 /*В слове*/
#define NEND 0 /*Не в слове*/



main(int argc, char **argv[])
{
	int c, str, bytes, word, state, endstr, i = 1;

	state = OUT;
	str = bytes = word = 0;
	endstr = END;

	FILE* f;
    #pragma warning(disable : 4996);
	f = fopen(argv[argc-1], "r");

	while ((c = fgetc(f)) != EOF)
	{
		++bytes;
		if (c == '\n')
		{
			++str;
			endstr = 1;
		}
		else
		{
			endstr = 0;
		}

		if (c == ' ' || c == '\t' || c == '\n')
			state = OUT;
		else
		{
			if (state == OUT)
			{
				state = IN;
				++word;
			}
		}
	}
	if (endstr == NEND) {
		str++;
		bytes = bytes + str - 1;
	}

	if (endstr != NEND)
		bytes = bytes + str;

	while (i < (argc - 1))
	{

		if ((strcmp(argv[i], "-c") == 0) || (strcmp(argv[i], "--bytes")) == 0)
			printf("%d\t", bytes);

		if ((strcmp(argv[i], "-w") == 0) || (strcmp(argv[i], "--words")) == 0)
			printf("%d\t", word);

		if ((strcmp(argv[i], "-l") == 0) || (strcmp(argv[i], "--lines")) == 0)
			printf("%d\t", str);

		i++;
	}

	return 0;
}