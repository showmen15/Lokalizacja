
#include "Location.h"

int main(int argc, char* argv[])
{
	char* mapPath = "/home/szsz//git//Lokalizacja//Lokalizacja//Debug//labNowe3.roson";

	unsigned int numberParticles = 104;
	double epsilon = 0.96;
	int generation = 1;
	unsigned int ilosc_losowanych_nowych_czastek = 20;
	unsigned int przlieczenie_dla_pomiaru_skanera = 1;

	Location *lok = new Location(mapPath,numberParticles,epsilon,generation,ilosc_losowanych_nowych_czastek,przlieczenie_dla_pomiaru_skanera);

	lok->RunLocation();

	return 0;
}
