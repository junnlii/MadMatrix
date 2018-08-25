#include "DataStructure.h"
#include "Xtal.h"
#include <fstream>
#include <iostream>
#include <string>


void Xtal::LoadNPUList() {

	ifstream NPUInput("NPU.list");
	if (!NPUInput.good())
	{
		std::cout << " cannot find input file: NPUs\n";
		exit(1);
	}
	NPUInput >> totalNPU>>nocc>>nvac;
	occNPU = new NPU[nocc];
	int num = 0;
	vect3D *vPos;
	double x, y, z;
	for (int i = 0;i < nocc;i++) {
		NPUInput >> num;
		occNPU[i].setCenterID(num);
	}
	for (int i = 0;i < nocc;i++) {
		NPUInput >> x;
		occNPU[i].setValence(x);
	}
	for (int i = 0;i <nocc;i++) {
		NPUInput >> num;
		vPos = new vect3D[num];
		for (int j = 0;j < num;j++) {
			NPUInput >> x >> y >> z;
			vPos[j].setX(x);
			vPos[j].setY(y);
			vPos[j].setZ(z);
		}
		occNPU[i].setNumVertice(num);
		occNPU[i].setVerticePos(num, vPos);
		delete[] vPos;
	}
	if (nvac > 0) { 
		vacNPU = new NPU[nvac]; 
		for (int i = 0;i <nvac;i++) {
			NPUInput >> num;
			vPos = new vect3D[num];
			for (int j = 0;j < num;j++) {
				NPUInput >> x >> y >> z;
				vPos[j].setX(x);
				vPos[j].setY(y);
				vPos[j].setZ(z);
			}
			vacNPU[i].setNumVertice(num);
			vacNPU[i].setVerticePos(num, vPos);
			delete[] vPos;
		}
	}

	std::cout << "Total NPUs: " << totalNPU << "\n";
	std::cout << "Occupied NPUs: " << nocc << "\n";
	for (int i = 0;i < nocc;i++) {
		std::cout << "# " << i << " occupied NPU has vertices: " << occNPU[i].getNumVertice() << "\n";
		for (int j = 0;j < occNPU[i].getNumVertice();j++) {
			occNPU[i].getVerticePos()[j].vect3DPrint();
		}	
	
	}
	std::cout << "Unoccupied NPUs: " << nvac << "\n";
	for (int i = 0;i < nvac;i++) {
		std::cout << "# " << i << " vacant NPU has vertices: " << vacNPU[i].getNumVertice() << "\n";
		for (int j = 0;j < vacNPU[i].getNumVertice();j++) {
			vacNPU[i].getVerticePos()[j].vect3DPrint();
		}
		std::cout << "\n";
	}
}

void Xtal::LoadingXtal() {

	ifstream myInput("POSCAR");
	if (!myInput.good())
	{
		std::cout << " cannot find input file: POSCAR\n";
		exit(1);
	}

	double scaleLat = 1.0;
	myInput >> title;
	myInput >> scaleLat;

	vect3D temp;
	double x, y, z;
	myInput >> x >> y >> z;
	temp.setX(scaleLat*x);temp.setY(scaleLat*y);temp.setZ(scaleLat*z);
	setAA(temp);						//Loading Lattice a
	myInput >> x >> y >> z;
	temp.setX(scaleLat*x);temp.setY(scaleLat*y);temp.setZ(scaleLat*z);
	setBB(temp);						//Loading Lattice b
	myInput >> x >> y >> z;
	temp.setX(scaleLat*x);temp.setY(scaleLat*y);temp.setZ(scaleLat*z);
	setCC(temp);						//Loading Lattice c

	string aString;
	getline(myInput, aString, '\n');
	getline(myInput, aString, '\n');
	int type;
	peekWordinString(aString, &type);

	std::cout << "Total elements: " << type << "\n";

	string *element = new string[type];
	loadArrayinString(aString, element);
	int *numElement = new int[type];
	int totalAtom = 0;
	for (int i = 0;i < type;i++) {
		myInput >> numElement[i];
		totalAtom += numElement[i];
	}
	setType(type, element, numElement);

	for (int i = 0;i < type;i++) {
		std::cout << element[i] << ": " << numElement[i] << "\n";
	}
	std::cout << "Total atoms: " << totalAtom << "\n";

	string dum;
	myInput >> dum;

	double *coordinateOccuppied = new double[3 * totalAtom];

	int j;
	for (int i = 0; i < totalAtom; i++) {
		j = i * 3;
		myInput >> coordinateOccuppied[j] >> coordinateOccuppied[j + 1] >> coordinateOccuppied[j + 2];

	}

	setNum(totalAtom, coordinateOccuppied);

	myInput.close();
	delete[]coordinateOccuppied;
	delete[]element;
	delete[]numElement;
}

void Xtal::PrintXtal() {
	std::cout << "Crystal: " << title << "\n";
	LatticePrint();
	printCell();
}

