#include <stdio.h> /* for printf(), fprintf() */
#include <winsock.h> /* for socket(),... */
#include <stdlib.h> /* for exit() */

#define ECHOMAX 255 /* Longest string to echo */

class  UdpClient
{
public:
	UdpClient(char* sIP, unsigned short port);
	UdpClient(unsigned short port,unsigned int bufforSize);
	~ UdpClient();

	int ReceiveLength; /* Size of received message */
	
	char* Receive();

	//void Send(const char* dgram,int bytes);
void Send(const char* dgram);

private:
	int sock; /* Socket descriptor */
	struct sockaddr_in echoServAddr; /* Echo server address */
	struct sockaddr_in fromAddr; /* Source address of echo */
	unsigned short echoServPort; /* Echo server port */
	unsigned int fromSize; /* In-out of address size for recvfrom() */
	char *servIP; /* IP address of server */
	char *echoString; /* String to send to echo server */
	char echoBuffer[ECHOMAX]; /* Buffer for echo string */
	int echoStringLen; /* Length of string to echo */
	int respStringLen; /* Length of response string */
	WSADATA wsaData; /* Structure for WinSock setup communication */

	//int sock; /* Socket */
	//struct sockaddr_in echoServAddr; /* Local address */
	//struct sockaddr_in echoClntAddr; /* Client address */
	//char* echoBuffer; /* Buffer for echo string */ //char echoBuffer[ECHOMAX]; 
	//unsigned short echoServPort; /* Server port */
	//int cliLen; /* Length of incoming message */
	////int recvMsgSize; 
	//WSADATA wsaData; /* Structure for WinSock setup communication */

	void DieWithError(char *errorMessage);
};


