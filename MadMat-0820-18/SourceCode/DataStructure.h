#pragma once
#include <iostream>
#include <iomanip>
using namespace std;


void peekWordinString(string const inString, int *Words);
void loadArrayinString(string const inString, string element[]);

class vect1D {
protected:
	double x;
public:
	vect1D() { x = 0.0; }													// default constructor
	vect1D(double nx) : x(nx) {}											// input data constructor
	vect1D(vect1D &o) {	x = o.x; }											// deep copy constructor
	void setX(double nx) { x = nx; }										// manually set the data
	double getX() { return x; }												// output data
	double scaleX(int i) { return double(i)*x; }							// increase x by input i

	~vect1D(){}
};

class vect2D: public vect1D {
protected:
	double y;
public:
	vect2D() { x = 0.0; y = 0.0; }											// default constructor
	vect2D(double nx, double ny) { x = nx; y = ny; }						// input data constructor
	vect2D(vect2D &o) { x = o.x; y = o.y; }									// deep copy constructor
	void setY(double ny) { y = ny; }										// manually set the data
	double getY() { return y; }												// output data
	double scaleY(int i) { return double(i)*y; }							// increase y by input i
	~vect2D() {}
};

class vect3D : public vect2D {
protected:
	double z;
public:
	vect3D() { x = 0.0; y = 0.0; z = 0.0; }									// default constructor
	vect3D(double nx, double ny, double nz) { x = nx; y = ny; z = nz; }		// input data constructor
	vect3D(vect3D &o) { x = o.x; y = o.y; z = o.z; }						// deep copy constructor
	void setZ(double nz) { z = nz; }										// manually set the data
	double getZ() { return z; }												// output data
	double scaleZ(int i) { return double(i)*z; }							// increase z by input i
	~vect3D() {}
	void vect3DPrint() {													// print onscreen the Lattice
		cout << fixed << showpoint << setprecision(4);
		cout << x << "," << y << "," << z << "\n";
	}
	
};
double vect3Ddot(vect3D, vect3D);
vect3D vect3DPlusScale(double, vect3D, double, vect3D);
double vect3Dlength(vect3D, vect3D);
double vect3DModule(vect3D aa, vect3D bb, vect3D cc, vect3D vec);

class Lattice {
	vect3D aa, bb, cc;
public:
	Lattice(vect3D a, vect3D b, vect3D c) :aa(a),bb(b),cc(c) {}				// loading three lattice vectors
	Lattice() {																// default unit cubic cell
		aa.setX(1.0);aa.setY(0.0);aa.setZ(0.0);
		bb.setX(0.0);bb.setY(1.0);bb.setZ(0.0);
		cc.setX(0.0);cc.setY(0.0);cc.setZ(1.0);
	}
	Lattice(Lattice &abc) {													// deep copy an input lattice
		aa = abc.aa;bb = abc.bb;cc = abc.cc;
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


	~ Lattice() {}
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
	string getElement(){ return *element; }
	void setNum(int type, double CoordArray[]);
	int getNum() { return totalAtom; }
	vect3D getCoord(int ID);
	void printCell();
	
	~pCell(){}
};

class NPU {
	int numVertice;
	int centerID;								//the occupied site, not necessary the geometric center
	double volume, *vCharge;
	double valence;
	double offset[3];
	vect3D *verticePos;							//for a virtual motion of the NPU center
	vect3D cPos,*vPos;							//Cardisian coordinates
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

