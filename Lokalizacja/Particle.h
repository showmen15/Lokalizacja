#include <stdio.h>
#include <sstream>
#include <math.h>
#include <iostream>
#include <stdlib.h>

#define TEST 1
#define PROMIEN 0.1

using namespace std;

#define M_PI       3.14159265358979323846
#define ODCHYLENIE 0.05
#define NEW_MIN 0
#define NEW_MAX 1

//bierzemy co 10 pomiar skanera
#define PRZLIECZENIE_DLA_POMIARU_SKANERA 2

struct Point
{
	public:
		double X;
		double Y;
};


struct Particle 
{
private:
	double MinX;
	double MaxX;
	double MinY;
	double MaxY;
	double MaxRadius;
	double rMAX;


	double alfaNew;
	double d;
public:	

	Particle()
	{

	}

	Particle(double dMinX,double dMaxX,double dMinY, double dMaxY,double dRMAX)
	{
		MinX = dMinX;
		MaxX = dMaxX;
		MinY = dMinY;
		MaxY = dMaxY;
		rMAX = dRMAX;
		MaxRadius = 360;

		Losuj2();
	}


	Particle(double dMaxX,double dMaxY,double dRMAX)
	{
		MaxX = dMaxX;
		MaxY = dMaxY;
		rMAX = dRMAX;
		MaxRadius = 360;

		Losuj();
	}

	double X;
	double Y;
	double Alfa;
	double AlfaStopnie;
	double Probability;

	short sMarkToDelete;

	void Move(double newX,double newY, double newAlfa);


	inline void Losuj() //Generuj czastki ograniczone do wielosci mapy 
	{
		X = ((double)rand() / RAND_MAX) * MaxX; 
		Y = ( (double)rand() / RAND_MAX) * MaxY;
		Alfa = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		Probability = 0.0;
		sMarkToDelete = 0;
	}

	inline double fRand(double fMin, double fMax)
	{
	    double f = (double)rand() / RAND_MAX;
	    return fMin + f * (fMax - fMin);
	}

	inline void LosujPozycje(double X1,double X2,double Y1, double Y2)
	{
		X = fRand(X1,X2);
		Y = fRand(Y1,Y2);

		#if TEST == 1
			if(X < 0)
				printf("LosujPozycje X UJEMNE,X1%e,X2%e,Y1%eY2%e",X1,X2,Y1,Y2);
			if(Y < 0)
				printf("LosujPozycje Y UJEMNE,X1%e,X2%e,Y1%eY2%e",X1,X2,Y1,Y2);
			fflush(NULL);
		#endif

		Alfa = fRand(0,2 * M_PI);
		AlfaStopnie = Alfa * (180 / M_PI);;
		Probability = 0.0;
		sMarkToDelete = 0;
	}

	inline void Losuj2()
	{
		X = abs((MaxX - MinX) * ( (double)rand() / (double)RAND_MAX ) + MinX); 	//(MinX + ((double)  rand()) / MaxX);  //X = (MinX +  (double)rand() / RAND_MAX) * MaxX; 
		Y =  abs((MaxY - MinY) * ( (double)rand() / (double)RAND_MAX ) + MinY); //Y = (MinY + ((double)rand() / MaxY); //Y = (MinY + (double)rand() / RAND_MAX) * MaxY;
		
		Alfa = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		Probability = 0.0;
		sMarkToDelete = 0;

	}

	inline void Losuj(double X0,double Y0, double alfa) //Generuj czastke w sasiedztwie innej czastki
	{
		double t = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		double R1 =  ((double)rand() / RAND_MAX) * rMAX; //kat ograniczony do 360 stopni 

		X = abs( X0 + R1 * cos(t)); 
		Y = abs(Y0 + R1 * sin(t)); 
		
		if(X > MaxX)
			X = MaxX;

		if(Y > MaxY)
			Y = MaxY;

		Alfa =  alfa; //((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		Probability = 0.0;
		sMarkToDelete = 0;
	}

	inline void LosujSasiada(double X0,double Y0, double alfa) //Generuj czastke w sasiedztwie innej czastki
	{
		double t = fRand(0,360);  //kat ograniczony do 360 stopni
		double R1 =  fRand(0,PROMIEN);  //kat ograniczony do 360 stopni

		X =  X0 + R1 * cos(t);
		Y = Y0 + R1 * sin(t);

		if(X < 0)
			X *= -1;

		if(Y < 0)
			Y *= -1;

		#if TEST == 1
			if(X < 0)
				printf("LosujPozycje X UJEMNE,%e",X);
			if(Y < 0)
				printf("LosujPozycje Y UJEMNE,%e",Y);
			fflush(NULL);
		#endif

		Alfa =  alfa; // //kat ograniczony do 360 stopni
		AlfaStopnie = Alfa * (180 / M_PI);
		Probability = 0.0;
		sMarkToDelete = 0;
	}

	/*inline Point getIntersection(double A,double B,double C,double X0,double Y0,double Alfa)
	{
		Point p;
		double A0 = tan(Alfa);
		double B1 = -1;
		double C1 = Y0 - (A0 * X0);

		double W;

		W =


	}*/

inline double getDistnace(MazeWall *wall,double alfa,double X2,double Y2)
{	
	double W;
	double Wx;
	double Wy;
	double dist = -1.0;
	double X;
	double Y;
	double a1 = wall->A;
	double b1 = wall->B;
	double c1 = wall->C;

	double a2 = - tan( (alfa * M_PI) / 180.0);
	double b2 = 1;
 	double c2 =  Y2 + (a2 * X2);

	W = a1 * b2 - b1 * a2;
	
	if(W != 0)
	{
		Wx = c1 * b2 - b1 * c2;
		Wy = a1 * c2 - c1 * a2;

		X = Wx / W;
		Y = Wy / W;

		if((wall->From_X <= X) && (X <= wall->To_X) && (wall->From_Y <= Y) && (Y <= wall->To_Y))
			dist = sqrt(pow(X - X2 ,2) + pow( Y - Y2,2)); //wartosc oczekiwana
	}

	return dist;
}

		inline void ZaktualizujPrzesuniecie4(double wheelTrack,double Vl, double  Vr, double dt)
		{
			if(Vl != Vr)
			{
				alfaNew = (((Vr - Vl) * dt) / wheelTrack);

				X += (wheelTrack * (Vr + Vl)) / (2*(Vr - Vl)) * (sin(alfaNew + Alfa) - sin(Alfa));
				Y -= (wheelTrack * (Vr + Vl)) / (2*(Vr - Vl)) * (cos(alfaNew + Alfa) - cos(Alfa));

				Alfa += alfaNew;

			}
			else
			{
				d = ((Vr + Vl) / 2) * dt;

				X += d * cos(Alfa);
				Y += d * sin(Alfa);
			}
		}

		inline double Normalize(double value,double min,double max) //normalizacja min max
		{
			return (((value - min) * (NEW_MAX - NEW_MIN)) / (max - min)) + NEW_MIN;
		}

		inline void UpdateCountProbability3(Room* box,int scanTable[],double angleTable[],int length)
		{
			double dist;
			double gauss;
			double sumProbability = 0.0;
			Probability = 0.0;
			int iloscScian = box->ContainerWallCount();
			double norm;
			double tablicaOdleglosci[length];
			double tablicaKatow[length];
			double tablicaSkan[length];
			double tablicaGauss[length];
			int index = 0;

			for (int i = 0; i < length; i = i + PRZLIECZENIE_DLA_POMIARU_SKANERA)
			{
				int test = 0;
				test++;

				for (int j = 0; j < iloscScian; j++)
				{
					dist =  getDistnace(&box->ContainerWallTable[j],this->AlfaStopnie + angleTable[i],this->X,this->Y); //wartosc oczekiwana

					if(dist > 0)
					{



						double scan = (((double) scanTable[i]) / 1000);
						gauss =  Gauss2(dist,scan); //exp((-1 * pow(scanTable[i] - dist,2)) / ( 2 * ODCHYLENIE * ODCHYLENIE)) / (2 * M_PI * ODCHYLENIE);

						tablicaOdleglosci[index] = dist;
						tablicaKatow[index] = angleTable[i];
						tablicaSkan[index] = scan;
						tablicaGauss[index] = gauss;
						index++;


						//Normalize(gauss,0,Gauss2(10,10)); //gauss;


					sumProbability += gauss;
					}
				}
			}


		/*	for(int i = 0; i < index;i++)
			{
				printf("Obliczone: %f Kat: %f Skan: %f Gaus: %f\n",tablicaOdleglosci[i],tablicaKatow[i],tablicaSkan[i],tablicaGauss[i]);
			}

			fflush(NULL);
*/

			double yy = ((double) index) * Gauss2(1,1);
			Probability =  Normalize(sumProbability,0,yy);  //(sumProbability / index);  /// (length / PRZLIECZENIE_DLA_POMIARU_SKANERA)); //sumProbability
		}


	inline double Gauss2(double prop,double real)
	{
	double a,b,c,d;
	double x = prop;
	double delta = sqrt(ODCHYLENIE);
	double ni = real;

	a = 1 / (delta  *sqrt(2 * M_PI));
	b = ni;
	c = delta;
	d = 0;

	return (a * exp( pow(x - b,2) / (-2 * pow(c,2)))) + d;
	}
};



/*
	inline void UpdateCountProbability(Room* box,int scanTable[],double angleTable[],int length)
	{
		double dist;
		double gauss;
		double sumProbability = 0.0;
		int iloscScian = box->ContainerWallCount();

		for (int i = 0; i < length; i = i + PRZLIECZENIE_DLA_POMIARU_SKANERA)
		{
			int test = 0;
			test++;

			for (int j = 0; j < iloscScian; j++)
			{
				dist =  getDistnace(&box->ContainerWallTable[j],angleTable[i],this->X,this->Y); //wartosc oczekiwana

				if(dist > 0)
				{
					double scan = (((double) scanTable[i]) / 1000);
				gauss =  Gauss2(scan,dist); //exp((-1 * pow(scanTable[i] - dist,2)) / ( 2 * ODCHYLENIE * ODCHYLENIE)) / (2 * M_PI * ODCHYLENIE);
				
				sumProbability +=  gauss;//Normalize(gauss,0,dist); 
				}
			}
		}

		Probability = sumProbability;
	}
	*/
		
/*
	inline void UpdateCountProbability1(Room* box,int scanTable[],double angleTable[],int length)
	{
		double dist;
		double gauss;
		double sumProbability = 0.0;
		int iloscScian = box->ContainerWallCount();

		for (int i = 0; i < length; i = i + PRZLIECZENIE_DLA_POMIARU_SKANERA)
		{
			printf("ID: %d Kat: %f Odleglosc: %d\n",i,angleTable[i],scanTable[i]);

			int test = 0;
			test++;

			for (int j = 3; j < iloscScian; )
			{
				double scan = 0;
				dist =  getDistnace(&box->ContainerWallTable[j],angleTable[i],this->X,this->Y); //wartosc oczekiwana

				if(dist > 0)
				{
				scan = (((double) scanTable[i]) / 1000);
				gauss =  Gauss2(scan,dist); //exp((-1 * pow(scanTable[i] - dist,2)) / ( 2 * ODCHYLENIE * ODCHYLENIE)) / (2 * M_PI * ODCHYLENIE);

				sumProbability +=  gauss;//Normalize(gauss,0,dist);
				}


			/*	for(int w = 0; w < iloscScian; w++)
				{
					printf("X %f, Y %f\n",(&box->ContainerWallTable[w])->From_X, (&box->ContainerWallTable[w])->From_Y);
					fflush(NULL);
				}*/


				/*if((&box->ContainerWallTable[j])->From_X == (&box->ContainerWallTable[j])->To_X)
				{
					int eee;

					eee = 00;

					;

				}

			}
		}

		Probability = sumProbability;
	}
*/


		
		/*
		double sumProbability = 0.0;
		double X;
		double Y;
		double dist;
		double alfa2;
		double b2;
		double gauss;

		double W;
		double Wx;
		double Wy;


		if(box != NULL)
		{
			for(int j = 0; j < box->ContainerWall.size(); j++)
			{
		for (int i = 0; i < length; i++)
		{
			/*alfa2 = tan(angleTable[i]);
			b2 = this->Y - (alfa2 * this->Y);*/

		//	X = (b2 - box->ContainerWall[j].B) / (box->ContainerWall[j].A - alfa2);			
		//	Y = ((box->ContainerWall[j].A  * b2) - (alfa2 * box->ContainerWall[j].B)) / (box->ContainerWall[j].A - alfa2);

		/*	W = alfa2 * box->ContainerWall[j].B + box->ContainerWall[j].A;
			Wx = b2 * box->ContainerWall[j].B + box->ContainerWall[j].C;
			Wy = alfa2 * box->ContainerWall[j].C - box->ContainerWall[j].A * b2;


			if(W == 0)
				continue;
			else*/

			/*{

			X = Wx/W;
			Y = Wy/W;*/


			/*if((box->ContainerWall[j].From_X <= X <= box->ContainerWall[j].To_X) && (box->ContainerWall[j].From_Y <= Y <= box->ContainerWall[j].To_Y))
			{
				dist =  getDistnace(&box->ContainerWall[j],angleTable[i],this->X,this->Y); //wartosc oczekiwana
					
					
					//sqrt(( X - this->X ) * ( X - this->X ) + ( Y - this->Y ) * ( Y - this->Y )); //wartosc oczekiwana
				gauss =  exp((-1 * pow(scanTable[i] - dist,2)) / ( 2 * ODCHYLENIE * ODCHYLENIE)) / (2 * M_PI * ODCHYLENIE);  
				
				sumProbability +=  Normalize(gauss,0,dist); 
			}
			else
	/*			continue;		
			}
		}
			}
		}
		Probability = sumProbability;

		
	}*/



	//inline double Distance(Room* box)
	//{


	//}

/*	inline void ZaktualizujPrzesuniecie2(double wheelTrack,int frontRightSpeed, int  rearRightSpeed, int frontLeftSpeed, int rearLeftSpeed ,double time)
	{
		double Vr = ((double) (frontRightSpeed +  rearRightSpeed)) / 2000 ;
	   double Vl = ((double)(frontLeftSpeed + rearLeftSpeed)) / 2000;

			double sr = Vr * time;
			double sl = Vl * time;

			double s = (sr + sl) / 2;

			double alfa = ((sr - sl) / wheelTrack);
			alfa += this->Alfa;


			this->X = s * cos((alfa * M_PI) / 180) + this->X;
		    this->Y = s * sin((alfa * M_PI) / 180) + this->Y;

		    Alfa = alfa;

			printf("X%f\nY%f",X,Y);
		    fflush(NULL);



	}

	inline double KatLuku(double l,double r)
	{
		return ((360 * l) / ( 2 * M_PI * r));
	}


	inline void ZaktualizujPrzesuniecie3(double wheelTrack,double frontRightSpeed, double  rearRightSpeed, double frontLeftSpeed, double rearLeftSpeed ,double time)
	{
		double Vr = ((double) (frontRightSpeed +  rearRightSpeed)) / 2 ;
	   double Vl = ((double)(frontLeftSpeed + rearLeftSpeed)) / 2;
	   double s;

	   if(Vr == Vl) //ok
	   {
		   s = ((Vr + Vl) / 2) * time; //droga w mm
		   s = s / 1000; //droga w m

		   X += s * cos((Alfa * M_PI) / 180 ); // A'= [x + Sx, ...]
		   Y += s * cos(((90 - Alfa) * M_PI) / 180); // A' [... ,y + Sy]
	   }
	   else if((Vr != 0) && (Vl == 0))
	   {
		   double r = wheelTrack;
		   double sr =  Vr * time; // droga ww mm
		   sr = sr / 1000; // droga w m
		   	double kat =   KatLuku(sr,r);

		    X += sr * cos(((Alfa + kat) * M_PI) / 180 ); // A'= [x + Sx, ...]
		 	Y += sr * cos(((90 - (Alfa + kat)) * M_PI) / 180); // A' [... ,y + Sy]

		 	Alfa += kat;

		 	if(Alfa > 360)
 		 		Alfa -= 360;

	   }
	   else if((Vr == 0) && (Vl != 0))
	   {
		   double r = wheelTrack;
		 		   double sl =  Vl * time; // droga ww mm
		 		   sl = sl / 1000; // droga w m
		 		   	double kat =   KatLuku(-sl,r);

		 		    X += sl * cos(((Alfa + kat) * M_PI) / 180 ); // A'= [x + Sx, ...]
		 		 	Y += sl * cos(((90 - (Alfa + kat)) * M_PI) / 180); // A' [... ,y + Sy]
		 		 	Alfa += kat;

		 		 	if(Alfa > 360)
		 		 		Alfa -= 360;
	   }
	   else
	   {
		   double sr =  Vr * time; // droga ww mm
		    sr = sr / 1000; // droga w m
		  double sl =  Vl * time; // droga ww mm
		 	sl = sl / 1000; // droga w m


			 double x;


		 	if(Vl > Vr)
		 	{
		 		x = (sr * wheelTrack) / (sl - sr);
		 	}
		 	else
		 	{
		 		x = (sl * wheelTrack) / (sr - sl);
		 	}

		 	  double r = x + wheelTrack;
		 	double s = (sr + sl) / 2;



		 		double kat =   KatLuku(s,r);

		    X += s * cos(((Alfa + kat) * M_PI) / 180 ); // A'= [x + Sx, ...]
		 	Y += s * cos(((90 - (Alfa + kat)) * M_PI) / 180); // A' [... ,y + Sy]

		 	Alfa += kat;

		 	if(Alfa > 360)
 		 		Alfa -= 360;
	   }

	} */

/*	inline void ZaktualizujPrzesuniecie(double V,double alfa,double dt) //liczy droge i aktualizuje przemieszczenie
	{
		double s = V * dt;

		ZaktualizujPrzesuniecie(s,alfa);
	}*/
	
	/*inline void ZaktualizujPrzesuniecie(double s,double  alfa)
	{
			X += s * cos((alfa * M_PI) / 180 ); // A'= [x + Sx, ...]
			Y += s * cos(((90 - alfa) * M_PI) / 180); // A' [... ,y + Sy]

			Alfa += alfa;
	}*/


//	inline void ObrotCzastkiKat(double alfaNew)
//	{
//		X = X * cos((alfaNew * M_PI) / 180) - Y * sin((alfaNew * M_PI) / 180);
	//	Y = X * sin((alfaNew * M_PI) / 180) + Y * cos((alfaNew * M_PI) / 180);

	//	Alfa += alfaNew;

//	}


	//const char* TransmitParticle(int index)
	//{
	//	stringstream temp; 
	//	string tmp = "rrrrrrwwww";
	//	//const char yy;
	//	
	//	temp << "#" << index << ";" << X << ";" << Y << ";" << Alfa << ";" << Probability << ";" << '\0';	
	//	//tmp = temp.str();

	//	//return tmp.c_str();
	//	return tmp.c_str();
	//}

