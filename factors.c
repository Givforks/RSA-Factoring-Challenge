#include "rsa.h"
#include "pollard-rho.c"

/**
 * init - Initializes the text buffer with null char
 *
 * @buffer: Array that will hold numbers
 *
 * Return: NULL (not successful)
 */

void init(char *buffer)
{
	int p = 0;

	for (p = 0; p < S_BUFFER; p++)
		buffer[p] = '\0';
}

/**
 * file2buffer - Reads argv[1] to buffer
 *
 * @filename: Pointer to file location
 *
 * @buffer: Array that holds the file data
 *
 * Return: Null (not successful)
 */

void file2buffer(char *filename, char *buffer)
{
	int opens = 0;

	opens = open(filename, O_RDONLY);
	if (opens < 0)
		exit(EXIT_FAILURE);

	if (read(opens, buffer, S_BUFFER) < 0)
	{
		close(opens);
		exit(EXIT_FAILURE);
	}
	close(opens);
}

/**
 * _atoi - ASCII -> int conversion
 *
 * @src: Input char array
 *
 * @dest: Converted data array
 *
 * Return: Number of elements copied
 */

long long unsigned int _atoi(char *src, long long unsigned int *dest)
{
	int p = 0;

	for (p = 0; src[p] && src[p] != '\n'; p++)
		dest[p] = src[p] - '0';

	return (p);
}

/**
 * _putint - General agnostic number printing function
 *
 * @dest: Array of newly converted data
 *
 * @n: Size of array (N is also the principle number in PRho)
 *
 * Return: NULL (not successful)
 */
void _putint(long long unsigned int *dest, long long unsigned int n)
{
	int p = 0;

	for (p = 0; p < n; p++)
		putchar(dest[p] + '0');
}

/**
 * compute - Converts int array to int
 *
 * @src: Array of integers forming number
 *
 * @n: Number of digits in number
 *
 * Return: Integer repr. of array of ints
 */

long long unsigned int compute(long long unsigned int *src, long long unsigned int n)
{
        int p;
	long long unsigned int result = 0;

        for (p = 0; p < n; p++)
	{
                result *= 10;
		result += src[p];
	}

	//printf("result is: %llu\n", result);
	return result;
}

/**
 * main - Entry point
 *
 * @argc: Size of argv array
 *
 * @argv: Array of CLI inputs
 *
 * Return: always 0
 */

int main(int argc, char **argv)
{
	char buffer[S_BUFFER]; /* original buffer */
	char *token; /* tokenized buffer */

	long long unsigned int number[VALUE]; /* integer repr. of number */
	long long unsigned int cv = 1;

	long long unsigned int n; /* final value to compute */
	long long unsigned int big = 1;

	if (argc != 2)
		return (EXIT_FAILURE);

	init(buffer);
	file2buffer(argv[1], buffer);
	token = strtok(buffer, " \n"); /* separates each number */

	while (token != NULL)
	{
		cv = _atoi(token, number); /* converted values */

		n = compute(number, cv);
		big = n / PollardRho(n);
		printf("%llu=%llu*%llu\n", n, big, PollardRho(n));

		//_putint(number, cv);
		//putchar('\n');
		token = strtok(NULL, " \n"); /* breaks up each number */
	}

	return (EXIT_SUCCESS);
}
