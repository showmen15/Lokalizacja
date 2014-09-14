
#include "Location.h"

int main(int argc, char* argv[])
{
	char* mapPath = "/home/szsz//git//Lokalizacja//Lokalizacja//Debug//labNowe3.roson";

	unsigned int numberParticles = 104;
	double epsilon = 0.96;
	int generation = 1;
	unsigned int ilosc_losowanych_nowych_czastek = 10;

	Location *lok = new Location(mapPath,numberParticles,epsilon,generation,ilosc_losowanych_nowych_czastek);

	lok->RunLocation();

	return 0;
}
