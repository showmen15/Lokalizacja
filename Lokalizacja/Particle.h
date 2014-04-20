
#include <stdio.h>
#include <sstream>
using namespace std;

struct Particle 
{
public:	
	unsigned long X;
	unsigned long Y;
	unsigned long Alfa;
	double Probability;

	void Move(unsigned long newX,unsigned long newY, unsigned long newAlfa);
	void Update();

	const char* TransmitParticle(int index)
	{
		stringstream temp;
		string tmp;
		
		temp << "#" << index << ";" << X << ";" << Y << ";" << Alfa << ";" << Probability << ";";	
		tmp = temp.str();

		return tmp.c_str();
	}
};
