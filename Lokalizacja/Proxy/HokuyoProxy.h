
#include "drivermsg.pb.h"
#include "roboclaw.pb.h"
#include "hokuyo.pb.h"
//#include "UdpClientLinux.h"

#include <stdio.h>

class HokuyoProxy 
{
private:
	UdpClient* udp;
        double *angles;
	int *distances;

	char* requestScan;
	int requestScanLength;
	amber::hokuyo_proto::Scan* scanRequest(char* packetBytes);
	amber::DriverMsg *message;
	
public:

	HokuyoProxy(UdpClient* client_udp);
	~HokuyoProxy();
	
	int ScanLength;	
        double Angle(int index);	
	int Distance(int index);
	
    void GetScan();

    double* GetAngles(void);

    int* GetDistances(void);
};
