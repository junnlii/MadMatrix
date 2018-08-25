#pragma once
#include <iostream>
#include <iomanip>
//#include "Xtal.h"

using namespace std;

double normalizeD6(double tem);

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

