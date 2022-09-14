#include<stdio.h>
#include<winsock2.h>

#define BUFLEN 512
#define PORT 8888

int main()
{
	SOCKET socketfd;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsadata;

	slen = sizeof(si_other);

	printf("\ninitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		printf("failed to init Winsock, error: %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("failed to create socket, error: %d", WSAGetLastError());
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	if (bind(socketfd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("failed to create socket, error: %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		printf("waiting for data\n");
		fflush(stdout);

		memset(buf, '\0', BUFLEN);

		if ((recv_len = recvfrom(socketfd, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		printf("received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("message: %s\n", buf);

	}

	closesocket(socketfd);
	WSACleanup();

	return 0;
}