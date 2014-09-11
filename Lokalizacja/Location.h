#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>


#include "Proxy/UdpClientLinux.h"
#include "Proxy/HokuyoProxy.h"
#include "Proxy/RoboclawProxy.h"
#include "Proxy/LocationProxy.h"
#include "BoundingBox.h"
#include "Particle.h"

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

	/////// Diagnostic ////////////////
#if DIAGNOSTIC == 1
	char* IPPart;
	UdpClient *clientParticle;

	string diagnostic;
	int size;
	const char* wys;
#endif

public:
	Location(char* mapPath,unsigned int numberParticles,double epsilon,int generation,unsigned int ilosc_losowanych_nowych_czastek);
	~Location();
	void RunLocation();


};


