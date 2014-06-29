//#include <arpa/inet.h>
//#include <netinet/in.h>
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define BUFLEN 512
//
//class UdpClient
//{
//public:
//UdpClient(char* sIP, unsigned short port);
//UdpClient(char* sIP,unsigned short port,unsigned int bufforSize);
//~ UdpClient();
//
//char* Receive();
//
////void Send(const char* dgram,int bytes);
//void Send(const char* dgram);
//
//
//private:
//	
//	// send
//	struct sockaddr_in serv_addr;
//	//struct sockaddr_in cli_addr;
//	int sockfd;
//	int i;
//	int slen;
//	//socklen_t cli_slen;
//
//	
//	
//
//	//recive
//	struct sockaddr_in my_addr;
//	struct sockaddr_in cli_addr;
//	int sockfd_recive;
//	int	i_recive;
//
//	socklen_t slen_recive;
//	char buf[BUFLEN];
//	int respStringLen; /* Length of response string */
//
//void err(char *s);
//
//};
