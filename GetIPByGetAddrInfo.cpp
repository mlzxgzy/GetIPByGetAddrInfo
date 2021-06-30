#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

void GetMyIP(char* hostname) {
	struct addrinfo phint;
	struct addrinfo* pResult;
	memset(&phint, 0, sizeof(struct addrinfo));

	phint.ai_family = AF_INET;
	phint.ai_flags = AI_PASSIVE;
	phint.ai_protocol = IPPROTO_IP;

	int ret = getaddrinfo(hostname, NULL, &phint, &pResult);
	for (addrinfo* tmp = pResult; tmp != nullptr; tmp = tmp->ai_next) {
		sockaddr_in* addr = (sockaddr_in*)tmp->ai_addr;
		char str[INET_ADDRSTRLEN];
		std::cout << inet_ntop(AF_INET, (char*)&addr->sin_addr, str, sizeof(str)) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	WSAData wsData;
	WSAStartup(MAKEWORD(2, 2), &wsData);

	char hostname[256];

	if (argc < 2) gethostname(hostname, sizeof(hostname));
	else memcpy(hostname, argv[1], sizeof(hostname));

	GetMyIP(hostname);

	WSACleanup();
}