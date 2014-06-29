#include "UdpClientLinux.h"
#include "HokuyoProxy.h"

//HokuyoProxy::HokuyoProxy(UdpClient *client_udp)
//{
//	udp = client_udp;
//
//	requestScanLength = 15;
//	requestScan = new char[requestScanLength];
//	char tempTab[] = { 0, 4, 8, 4, 16, 0, 0, 7, 16, 1, 24, 100, 224, 2, 1 };	
//	for(int i = 0; i < 	requestScanLength; i++)
//		requestScan[i] = tempTab[i];
//
//		
//	message = new amber::DriverMsg();
//	
//	char *packetBytes;
//	amber::hokuyo_proto::Scan* tmp_scan;
//	
//	udp->Send(requestScan,requestScanLength);
//	packetBytes = udp->Receive();
//	
//	tmp_scan = scanRequest(packetBytes);
//	
//	ScanLength = tmp_scan->distances_size();
//
//	angles = new double[ScanLength];
//	distances = new int[ScanLength];
//}

HokuyoProxy::~HokuyoProxy()
{
    delete []angles;
	delete [] requestScan;
	delete []distances;
	//delete message;
}

double HokuyoProxy::Angle(int index)
{
	return angles[index];
}	

int HokuyoProxy::Distance(int index)
{
	return distances[index];
}
	
void HokuyoProxy::GetScan()
{
	char *packetBytes;
	////amber::hokuyo_proto::Scan* tmp_scan;

	//udp->Send(requestScan,requestScanLength);
	//packetBytes = udp->Receive();
	
	//tmp_scan = scanRequest(packetBytes);
	
	for(int i = 0; i < ScanLength;i++)
	{
		//angles[i] = tmp_scan->angles(i);
		//distances[i] = tmp_scan->distances(i);
	}
}

//amber::hokuyo_proto::Scan* HokuyoProxy::scanRequest(char* packetBytes)
//{
//	int headerLen = (packetBytes[0] << 8) + (packetBytes[1] & 0xff);
//	int messageLen = (packetBytes[2 + headerLen] << 8) + (packetBytes[2 + headerLen + 1] & 0xff);
//	const char* shiftPacketBytes = &(packetBytes[2 + headerLen + 2]);
//
//	message->ParseFromArray(shiftPacketBytes,messageLen);
//
//	return  message->MutableExtension(amber::hokuyo_proto::scan);
//}


	double* HokuyoProxy::GetAngles()
	{
		return angles;
	}

	int* HokuyoProxy::GetDistances()
	{
		return distances;
	}