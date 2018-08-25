#include <iostream>
#include <string>
#include "DataStructure.h"
#include <locale> 
//#include "Xtal.h"
#include <fstream>
#include <vector>
#include <sstream>


double normalizeD6(double tem) {
	while (tem > 1.0) {
		tem--;
	}
	while (tem < 0.0) {
		tem++;
	}
	if (abs(tem) < 0.000001) tem = 0.0;
	return tem;
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


