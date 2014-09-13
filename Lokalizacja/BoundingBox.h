#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1


#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

#include <string.h>
#include <string>
#include <vector>
#include <float.h>
#include <math.h>

using std::string;
using namespace std;


struct BoundingBox
{
public:
	double X_Left_Top;
	double Y_Left_Top;

	double X_Left_Bottom;
	double Y_Left_Bottom; 

	double X_Right_Top;
	double Y_Right_Top;

	double X_Right_Bottom;
	double Y_Right_Bottom; 

	BoundingBox()
	{
		X_Left_Top =
		X_Left_Bottom =
		Y_Left_Bottom = 
		X_Right_Bottom = DBL_MAX;//std::numeric_limits<double>::max();

		Y_Left_Top =
		X_Right_Top =
		Y_Right_Top = 
		Y_Right_Bottom = 0;
	}
};

class MazeWall 
{
private :
		double w;
	    double wa;
		double wb;


public :

	string Type;
	string		Id;
	double		Width;
	double		Height;
	string		Color;
	double 		From_X;
	double		From_Y;
	double		To_X;
	double		To_Y;

	double A;
	double B;
	double C;

	
	//void Calculate()
	//{
	//	A = (From_Y - To_Y) / (From_X - To_X);
	//	B = ((From_X * To_Y) - (To_X * From_Y)) / (From_X - To_X);
	//}

	void Calculate()
	{
		A = (From_Y - To_Y);
		A = round(A * 10000) / 10000;

		B = (To_X - From_X);
		B = round(B * 10000) / 10000;

		C =  (From_X * To_Y) - (From_Y * To_X);
 		C = round(C * 10000) / 10000;
	}
};

struct MazeSpaces
{
public:
	string Type;
	string SpaceId;
	string WallId;
};

struct Room
{
private:
	int iContainerWallCount;


public:
	string SpaceId;

	vector<MazeWall> ContainerWall;
	MazeWall *ContainerWallTable;

	BoundingBox Box; 

	void CreateContainerWall()
	{
		iContainerWallCount = ContainerWall.size();
		ContainerWallTable = new MazeWall[iContainerWallCount];
		copy(ContainerWall.begin(),ContainerWall.end(),ContainerWallTable);
	}

	int ContainerWallCount()
	{
		return iContainerWallCount;
	}
};


int conteins(vector<Room> rooms,string textToFind);

char* OpenFile(char *filename);

/*  Get Walls */
int GetMazeWalls(cJSON *json,MazeWall* & tableWalls);

int GetMazeSpaces(cJSON *json,MazeSpaces* & tableSpaces);

int GetRooms(MazeWall* wall,int WallsCount,MazeSpaces* spaces,int SpacesCount,Room* & rooms);

int AssignBoundingBox(Room* rooms,int RoomCount,BoundingBox* & box);

int  parseJasonFile(char *filename,BoundingBox* & bBox,Room* & rooms);
