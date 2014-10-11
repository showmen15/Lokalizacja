
#include "Location.h"

int main(int argc, char* argv[])
{
	char* mapPath = "/home/szsz//git//Lokalizacja//Lokalizacja//Debug//labNowe3.roson";
	//char* mapPath = "/home//panda//Lokalizacja//Lokalizacja//labNowe3.roson";

	unsigned int NumberParticles = 104;
	double epsilon = 0.80;
	int generation = 1;
	unsigned int ilosc_losowanych_nowych_czastek = 20;
	unsigned int przlieczenie_dla_pomiaru_skanera = 12;
	double RandomWalkMaxDistance = 0.7; //PROMIEN
	double StandardDeviation = 0.3; //ODCHYLENIE

	Location *lok = new Location(mapPath,NumberParticles,epsilon,generation,ilosc_losowanych_nowych_czastek,przlieczenie_dla_pomiaru_skanera,RandomWalkMaxDistance,StandardDeviation);

	lok->RunLocation();

	return 0;
}
