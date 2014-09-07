
#include "drivermsg.pb.h"
#include "roboclaw.pb.h"
#include "hokuyo.pb.h"
//#include "UdpClientLinux.h"

#include <stdio.h>
#define M_PI       3.14159265358979323846

#define PRZLIECZENIE_DLA_POMIARU_SKANERA 1


class HokuyoProxy 
{
private:

	static const int DEVICE_TYPE = 4;
	static const int DEVICE_ID = 0;

	UdpClient* udp;
    double *angles;
	int *distances;

	char* requestScan;
	int requestScanLength;
	amber::hokuyo_proto::Scan* scanRequest(char* packetBytes);
	amber::DriverMsg *message;
	
	amber::DriverHdr  buildHeader();
	amber::DriverMsg* buildMsg(int synNum);
	void buildSendMessage(amber::DriverHdr header, amber::DriverMsg* message);

	int synNum;

public:

	HokuyoProxy(UdpClient* client_udp);
	~HokuyoProxy();
	
	int ScanLengthAll;
	int ScanLength;

	double Angle(int index);
	int Distance(int index);
	
    void GetScan();

    double* GetAngles(void);

    int* GetDistances(void);

    double ConvertToRadian(double degree);
};
