//#include "UdpClientLinux.h"
//
//UdpClient::UdpClient(char* sIP, unsigned short port)
//{
//	UdpClient(sIP,port,BUFLEN);
//}
//
//UdpClient::UdpClient(char* sIP,unsigned short port,unsigned int bufforSize)
//{
//	
//	//send
//	slen = sizeof(serv_addr);
//	//cli_slen=sizeof(cli_addr);
//
//	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
//	        err((char*) "socket");
//	
//	bzero(&serv_addr, sizeof(serv_addr));
//	serv_addr.sin_family = AF_INET;
//        serv_addr.sin_port = htons(port);
//
// 	if (inet_aton(sIP, &serv_addr.sin_addr)==0) 	
//		err((char*) "inet_aton() failed");      	
//
//	//recive
//
//	slen_recive=sizeof(cli_addr);
//
//	if ((sockfd_recive = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
//      err((char*)"socket revive");
//
//	bzero(&my_addr, sizeof(my_addr));
//    my_addr.sin_family = AF_INET;
//    my_addr.sin_port = htons(port);
//    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     
//    if (bind(sockfd_recive, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
//      err((char*)"bind Recive");
//
//}
//
//UdpClient::~UdpClient()
//{
//    close(sockfd);
//}
//
//char* UdpClient::Receive()
//{
//	respStringLen = recvfrom(sockfd_recive, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen_recive);
//
//	return buf;
//}
//
//void UdpClient::Send(const char* dgram)
//{
//	if (sendto(sockfd, dgram, strlen(dgram), 0, (struct sockaddr*)&serv_addr, slen)==-1)
//            err((char*) "Send()");
//}
//
//void UdpClient::err(char *s)
//{
//    perror(s);
//    exit(1);
//}
// 
