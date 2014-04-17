struct Particle 
{
public:	
	unsigned long X;
	unsigned long Y;
	unsigned long Alfa;

	void Move(unsigned long newX,unsigned long newY, unsigned long newAlfa);
	void Update();
};
