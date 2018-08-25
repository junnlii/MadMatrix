#include <iostream>
#include <string>
#include "DataStructure.h"
#include <locale> 


void peekWordinString(string const inString, int *Words)
{
	std::locale loc;
	bool turnon = false;
	*Words = 0;
	
	char c;
	for (int i = 0; i < inString.length(); ++i)
	{
		c = inString[i];
		if (std::isalpha(c, loc) && !turnon) {
			turnon = true; (*Words)++;
		}
		else
		{
			if (!std::isalpha(c, loc)) turnon = false;
		}
	}
}

void loadArrayinString(string const inString, string element[])			//white space needed for the last element
{
	bool turnon = false;
	std::locale loc;
	int id = 0;
	char c;
	string sdum = "";
	for (int i = 0; i<inString.length(); ++i)
	{
		c = inString[i];
		if (std::isalpha(c, loc) && !turnon) {
			turnon = true; sdum += c; id++;
		}
		else
		{
			if (std::isalpha(c, loc)) { sdum += c; }
			else if (!std::isalpha(c, loc) && turnon) {
				element[id - 1] = sdum; sdum = ""; turnon = false;
			}
		}
	}
}

double vect3Ddot(vect3D vec1, vect3D vec2) {
	return vec1.getX()*vec2.getX() + vec1.getY()*vec2.getY() + vec1.getZ()*vec2.getZ();
}
double vect3Dlength(vect3D vec1, vect3D vec2) {
	double length,x,y,z;
	x = vec1.getX() - vec2.getX();
	y = vec1.getY() - vec2.getY();
	z = vec1.getZ() - vec2.getZ();
	length = x*x + y*y + z*z;
	return  sqrt(length);
}
vect3D vect3DPlusScale(double w1,vect3D vec1, double w2,vect3D vec2) {	//linear plus of two 3D vectors
	double x = w1*vec1.getX() + w2*vec2.getX();
	double y = w1*vec1.getY() + w2*vec2.getY();
	double z = w1*vec1.getZ() + w2*vec2.getZ();
	vect3D temp(x, y, z);
	return temp;
}

double vect3DModule(vect3D aa, vect3D bb, vect3D cc, vect3D vec) {
	//calculate a lattice length or vector module
	double xx = vec.getX();
	double yy = vec.getY();
	double zz = vec.getZ();
	vect3D zero(0.0, 0.0, 0.0);
	double one = 1.0;
	zero=vect3DPlusScale(xx, aa, yy, bb);
	zero = vect3DPlusScale(one, zero, zz, cc);
	one=vect3Ddot(zero, zero);
	return sqrt(one);
}

void pCell::setType(int type, string eleArray[], int numArray[])
{
	typElement = type;
	element = new string[type];
	numElement = new int[type];
	for (int i = 0;i < type;i++) {
		element[i] = eleArray[i];
		numElement[i] = numArray[i];
	}
}
void pCell::setNum(int type, double CoordArray[])
{
	totalAtom = type;
	coord = new double[3 * type];

	for (int i = 0;i < 3 * type;i++) {
		coord[i] = CoordArray[i];
	}
}


void pCell::printCell()
{
	for (int i = 0;i < typElement;i++) {
		std::cout << element[i] << ": " << numElement[i] << "\n";
	}
	cout << "Total atoms: " << totalAtom << "\n";
	cout << fixed << showpoint << setprecision(4);
	int j;
	for (int i = 0;i < totalAtom;i++) {
		j = i * 3;
		cout << coord[j] << coord[j + 1] << coord[j + 2] << "\n";
	}
}

void NPU::setVerticePos(int num, vect3D Pos[]) {
	verticePos = new vect3D[num];
	vPos =new vect3D[num];
	vCharge = new double[num];
	for (int i = 0;i < num;i++) {
		verticePos[i] = Pos[i];
	}
}

void NPU::setVPos(int index, vect3D inPos) {
	vPos[index] = inPos;
}
vect3D pCell::getCoord(int ID) {
	int i = 3 * ID;
	vect3D pickCoord(coord[i], coord[i + 1], coord[i + 2]);
	return pickCoord;
}

