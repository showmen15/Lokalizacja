#include "UdpClient.h"


UdpClient::UdpClient(char* sIP, unsigned short port)
{
	//echoBuffer = new char[ECHOMAX];	
	//echoServPort = port;


	servIP = sIP;
	echoServPort = port;


	if (WSAStartup(MAKEWORD(2, 0), &wsaData)!= 0) /* Load Winsock 2.0 DLL */
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(1);
	}
	/* Create a best-effort datagram socket using UDP */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))< 0)
		DieWithError("socket() failed");

	/* Construct the server address structure */
	memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
	echoServAddr.sin_family = AF_INET; /* Internet address family */
	echoServAddr.sin_addr.s_addr = inet_addr(servIP); /* Server IP address */
	echoServAddr.sin_port = htons(echoServPort); /* Server port */




	//if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
	//{
	//	fprintf(stderr, "WSAStartup() failed");
	//	exit(1);
	//}

	///* Create socket for sending/receiving datagrams */
	//if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	//	DieWithError("socket() failed");

	///* Construct local address structure */
	//memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
	//echoServAddr.sin_family = AF_INET; /* Internet address family */
	//echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	//echoServAddr.sin_port = htons(echoServPort); /* Local port */

	///* Bind to the local address */
	//if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
	//	DieWithError("bind() failed");

	//UdpClient(port,ECHOMAX);
}

UdpClient::UdpClient(unsigned short port,unsigned int bufforSize)
{
	//echoBuffer = new char[bufforSize];	
	//echoServPort = port;

	//if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
	//{
	//	fprintf(stderr, "WSAStartup() failed");
	//	exit(1);
	//}

	///* Create socket for sending/receiving datagrams */
	//if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	//	DieWithError("socket() failed");

	///* Construct local address structure */
	//memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
	//echoServAddr.sin_family = AF_INET; /* Internet address family */
	//echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
	//echoServAddr.sin_port = htons(echoServPort); /* Local port */

	///* Bind to the local address */
	//if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
	//	DieWithError("bind() failed");

}

UdpClient::~UdpClient()
{
	closesocket(sock);

	WSACleanup(); /* Cleanup Winsock */
	//delete[] echoBuffer;
}

//int ReceiveLength; /* Size of received message */

char* UdpClient::Receive()
{
	respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *) (int*)&fromAddr,(int*)&fromSize);


	//if ((ReceiveLength = recvfrom(sock, echoBuffer, ECHOMAX, 0,(struct sockaddr *) &echoClntAddr, &cliLen)) < 0)
	//	DieWithError("recvfrom() failed");	

	return echoBuffer;
}

void UdpClient::Send(const char* dgram)
{
	int bytes = strlen(dgram);
	sendto(sock, dgram, bytes, 0, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr));

	//	sendto(sock, dgram, bytes, 0, (struct sockaddr *) &echoClntAddr,sizeof(echoClntAddr));
}


void UdpClient::DieWithError(char *errorMessage)
{
	fprintf(stderr,"%s: %d\n", errorMessage, WSAGetLastError());
	exit(1);
}



