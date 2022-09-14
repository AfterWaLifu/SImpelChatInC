#include<stdio.h>
#include<winsock2.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 8888

int main(void)
{
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);
	SOCKET socketfd;
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsadata;

	printf("\ninitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		printf("failed to init Winsock, error: %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if ((socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("failed to create socket, error: %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	memset((char*)&si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	while (1)
	{
		printf("\nenter message: ");
		gets(message);

		if (sendto(socketfd, message, strlen(message), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("failed to send, error: %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		memset(buf, '\0', BUFLEN);
	}

	closesocket(socketfd);
	WSACleanup();

	return EXIT_SUCCESS;
}