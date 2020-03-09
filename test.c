#include <stdio.h>
#include <winsock.h>

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	printf("Hello niggass");
	return 0;
}