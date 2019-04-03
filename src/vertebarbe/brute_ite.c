#include <stdio.h>
#include <stdlib.h>


void bruteforce(int length)
{
	char charset[] = "abcdefghijklmnopqrstuvwxyz";//0123456789";//"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!_?.";
	int cur = length - 1;
	int max = length - 1;
	//int min = 0;
	int curInCharset = 0;
	int charsetLength = sizeof(charset) -1;
	char *pass = calloc(1, length);
	for (int i = 0; i < length; i++)
	{
		pass[i] = charset[0];
	}
	int *trVector = calloc(1, length * sizeof(int));

	while (cur >= 0)
	{
		curInCharset = 0;
		while (curInCharset < charsetLength)
		{
			pass[max] = charset[curInCharset];
			//test_password(pass);
			//printf("%s\n", pass);
			curInCharset++;
		}
		cur--;
		while (cur >= 0 && trVector[cur] >= charsetLength - 1)
		{
			trVector[cur] = 0;
			pass[cur] = charset[0];
			cur--;
		}
		if (cur < 0)
		{
			printf("Finished !!\n");
			break;
		}
		trVector[cur]++;
		pass[cur] = charset[trVector[cur]];
		cur = max;

	}

	printf("Length : %d\n", charsetLength);
	free(pass);
	free(trVector);

}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	bruteforce(atoi(argv[1]));
	return 0;
}
