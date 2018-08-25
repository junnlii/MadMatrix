#pragma once
#include "DataStructure.h"



class NPU {
	int numVertice;
	int centerID;								//the occupied site, not necessary the geometric center
	double volume, *vCharge;
	double valence;
	double offset[3];
	vect3D *verticePos;							//for a virtual motion of the NPU center
	vect3D cPos, *vPos;							//Cardisian coordinates
public:
	void setCenterID(int num) { centerID = num; }
	int getCenterID() { return centerID; }
	void setValence(double val) { valence = val; }
	double getValence() { return valence; }
	void setNumVertice(int num) { numVertice = num; }
	int getNumVertice() { return numVertice; }
	void setVerticePos(int num, vect3D Pos[]);
	vect3D *getVerticePos() { return verticePos; }
	void setCPos(vect3D inPos) { cPos = inPos; }
	vect3D getCPos() { return cPos; }
	void setVPos(int index, vect3D inPos);
	vect3D getVPos(int index) { return vPos[index]; }

};
class Lattice {
	vect3D aa, bb, cc;
public:
	Lattice(vect3D a, vect3D b, vect3D c) :aa(a), bb(b), cc(c) {}				// loading three lattice vectors
	Lattice() {																// default unit cubic cell
		aa.setX(1.0); aa.setY(0.0); aa.setZ(0.0);
		bb.setX(0.0); bb.setY(1.0); bb.setZ(0.0);
		cc.setX(0.0); cc.setY(0.0); cc.setZ(1.0);
	}
	Lattice(Lattice &abc) {													// deep copy an input lattice
		aa = abc.aa; bb = abc.bb; cc = abc.cc;
	}
	void LatticePrint() {													// print onscreen the Lattice
		cout << fixed << showpoint << setprecision(4);
		cout << aa.getX() << "," << aa.getY() << "," << aa.getZ() << "\n";
		cout << bb.getX() << "," << bb.getY() << "," << bb.getZ() << "\n";
		cout << cc.getX() << "," << cc.getY() << "," << cc.getZ() << "\n";
	}
	void setAA(vect3D a) { aa = a; }
	void setBB(vect3D b) { bb = b; }
	void setCC(vect3D c) { cc = c; }
	vect3D getAA() { return aa; }
	vect3D getBB() { return bb; }
	vect3D getCC() { return cc; }


	~Lattice() {}
};

class pCell {
	int typElement;
	string * element;
	int *numElement;
	int totalAtom;
	double * coord;
public:

	void setType(int type, string eleArray[], int numArray[]);
	int getType() { return typElement; }
	string getElement() { return *element; }
	void setNum(int type, double CoordArray[]);
	int getNum() { return totalAtom; }
	vect3D getCoord(int ID);
	void printCell();

	~pCell() {}
};

class Xtal: public Lattice, public pCell {
	
	string title;
	int totalNPU;

public:

	NPU *occNPU;
	
	Xtal() {}
	~Xtal() {}

	void PrintXtal();		//print out setup of the lattice and cell
	void LoadNPUList();		//Load the GPU information
	int getNocc() { return totalNPU; }
	

};

void poscarLoad(std::string fileName, Xtal * rawData);