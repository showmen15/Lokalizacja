#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

#include "Proxy/UdpClientLinux.h"
#include "Proxy/HokuyoProxy.h"
#include "Proxy/RoboclawProxy.h"
#include "Proxy/LocationProxy.h"

#include "BoundingBox.h"
#include "Particle.h"
#include <math.h>

#define M_PI 3.14159265358979323846

#define DIAGNOSTIC 1

using namespace std;

class Location
{
private:
	char* amberUdp;
	UdpClient *clinetAmber;

	BoundingBox* bBox;
	Room* rooms;
	int countBox;
	int countRoomAndBox;

	Particle* tablicaCzastek;
	unsigned int NumberParticles;
	int iloscCzastekDoUsuniacia;

	RoboclawProxy* roboClaw;
	double speedRoboClaw;
	double angleRoboClaw;

	HokuyoProxy* skaner;

	struct timeval start,end;

	double deletaTime;
	Room* currentRoom;

	double EPSILON;
	int GENERATION;
	unsigned int ILOSC_LOSOWANYCH_NOWYCH_CZASTEK;

	void RozmiescCzastki(BoundingBox* bBox,unsigned int BoundingBoxCount,Particle* tablicaCzastek,unsigned int ParticleCount);
	void InitTablicaCzastekLosowo(Particle *tablica,BoundingBox* bBox,int countBox);
	Room* GetRoom(Room* bBox,int length, double X,double Y);

	const char* SendParticle(string *diagnostic,Particle *tab,int *size);

    static int compareMyType (const void * a, const void * b);

	void UsunWylosujNoweCzastki2(Particle* tablicaCzastek,int length,int iloscCzastekDoUsuniecia,BoundingBox* bBox,unsigned int BoundingBoxCount);
	inline int wylosujBB(int fMin, int fMax);

	char* getRobotIPAdress();

	void UsunWylosujNoweCzastki3(Particle* tablicaCzastek,int length,int iloscCzastekDoUsuniecia,BoundingBox* bBox,unsigned int BoundingBoxCount);
	void UsunWylosujNoweCzastki4(Particle* tablicaCzastek,int length,int iloscCzastekDoUsuniecia,BoundingBox* bBox,unsigned int BoundingBoxCount);
	void UsunWylosujNoweCzastki5(Particle* tablicaCzastek,int length,int iloscCzastekDoUsuniecia,BoundingBox* bBox,unsigned int BoundingBoxCount);
	void UsunWylosujNoweCzastki6(Particle* tablicaCzastek,int length,int iloscCzastekDoUsuniecia,BoundingBox* bBox,unsigned int BoundingBoxCount);

	double RandomWalkMaxDistance;
	double StandardDeviation;

	/////// Diagnostic ////////////////
#if DIAGNOSTIC == 1
	char* IPPart;
	UdpClient *clientParticle;

	string diagnostic;
	int size;
	const char* wys;
#endif

public:
	Location(char* mapPath,unsigned int numberParticles,double epsilon,int generation,unsigned int ilosc_losowanych_nowych_czastek,unsigned int skipScan,double dRandomWalkMaxDistance,double dStandardDeviation);
	~Location();
	void RunLocation();

	double Pos_X;
	double Pos_Y;
	double Prop;

};


