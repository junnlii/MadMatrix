#include "DataStructure.h"
#include "Xtal.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


void Xtal::LoadNPUList() {

	ifstream NPUInput("NPU.list");
	if (!NPUInput.good())
	{
		std::cout << " cannot find input file: NPUs\n";
		exit(1);
	}
	NPUInput >> totalNPU;
	int nocc = totalNPU;
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
	
	std::cout << "Total NPUs: " << totalNPU << "\n";
	
	for (int i = 0;i < nocc;i++) {
		std::cout << "# " << i << " occupied NPU has vertices: " << occNPU[i].getNumVertice() << "\n";
		for (int j = 0;j < occNPU[i].getNumVertice();j++) {
			occNPU[i].getVerticePos()[j].vect3DPrint();
		}	
	
	}
	
}


void Xtal::PrintXtal() {
	std::cout << "Crystal: " << title << "\n";
	LatticePrint();
	printCell();
}

void pCell::setType(int type, string eleArray[], int numArray[])
{
	typElement = type;
	element = new string[type];
	numElement = new int[type];
	for (int i = 0; i < type; i++) {
		element[i] = eleArray[i];
		numElement[i] = numArray[i];
	}
}
void pCell::setNum(int type, double CoordArray[])
{
	totalAtom = type;
	coord = new double[3 * type];

	for (int i = 0; i < 3 * type; i++) {
		coord[i] = CoordArray[i];
	}
}


void pCell::printCell()
{
	for (int i = 0; i < typElement; i++) {
		std::cout << element[i] << ": " << numElement[i] << "\n";
	}
	cout << "Total atoms: " << totalAtom << "\n";
	cout << fixed << showpoint << setprecision(4);
	int j;
	for (int i = 0; i < totalAtom; i++) {
		j = i * 3;
		cout << coord[j] << coord[j + 1] << coord[j + 2] << "\n";
	}
}

void NPU::setVerticePos(int num, vect3D Pos[]) {
	verticePos = new vect3D[num];
	vPos = new vect3D[num];
	vCharge = new double[num];
	for (int i = 0; i < num; i++) {
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

void poscarLoad(std::string fileName, Xtal * rawData) {

	std::ifstream myInput(fileName, std::ios::in);

	int totalType = 0, nAtm = 0;
	double *coordinateOccuppied;
	string *chemSymbl;
	time_t now = time(0);
	// convert now to string form
	char str[26];
	ctime_s(str, sizeof str, &now);
	std::cout << "The local date and time is: " << str << "\n";
	std::cout << "This data is loaded from " << fileName << "\n";

	if (!myInput.is_open()) {
		std::cout << " data file not found in the working folder\n";
	}
	else
	{
		std::string line;

		int nline = 0;
		double scale = 0.0;
		while (getline(myInput, line))
		{
			std::stringstream ss(line);
			if (nline == 0) { std::cout << "The title is " << ss.str() << std::endl; }

			if (nline == 1) {
				ss >> scale;
				std::cout << "Lattice scaling factor: " << std::showpoint << scale << std::endl;
			}

			if (nline >= 2 && nline <= 4) {
				std::vector<double> tmp_v;
				double tmp;
				while (!ss.eof()) {
					if (!(ss >> tmp).fail()) {
						tmp_v.push_back(scale*tmp);
					}
				}
				vect3D tem3D;
				tem3D.setX(tmp_v[0]);
				tem3D.setY(tmp_v[1]);
				tem3D.setZ(tmp_v[2]);
				if (nline == 2)rawData->setAA(tem3D);
				if (nline == 3)rawData->setBB(tem3D);
				if (nline == 4)rawData->setCC(tem3D);
				//inLat.setOneVector(tmp_v, nline - 2);
				tmp_v.clear();
			}
			if (nline == 5) {
				std::string tmp;
				std::vector<std::string> tmp_s;
				while (!ss.eof()) {
					if (!(ss >> tmp).fail()) {
						tmp_s.push_back(tmp);
					}
				}
				//inAtm.setChemSymbol(tmp_s);
				totalType = tmp_s.size();
				chemSymbl = new string[totalType];
				for (int i = 0; i < totalType; i++) {
					chemSymbl[i] = tmp_s[i];
					std::cout << chemSymbl[i] << " , ";
				}
				//std::cout << "\n";
			}
			if (nline == 6) {

				int tmp;
				std::vector<int> tmp_i;
				while (!ss.eof()) {
					if (!(ss >> tmp).fail()) {
						tmp_i.push_back(tmp);
						nAtm += tmp;
					}
				}
				int typ;
				typ = tmp_i.size();
				int *numSymbl = new int[typ];
				if (typ != totalType) std::cout << "WARN: chemical elements not match!\n";
				for (int i = 0; i < totalType; i++) {
					numSymbl[i] = tmp_i[i];
					std::cout << numSymbl[i] << " , ";
				}
				rawData->setType(totalType, chemSymbl, numSymbl);
				std::cout << " Total atoms: " << nAtm << "\n";
				coordinateOccuppied = new double[3 * nAtm];
			}
			if (nline >= 8 && nline <= nAtm + 7) {
				std::vector<double> tmp_d;
				double tmp;
				while (!ss.eof()) {
					if (!(ss >> tmp).fail()) {
						tmp = normalizeD6(tmp);
						tmp_d.push_back(tmp);
					}
				}
				int j = (nline - 8) * 3;
				coordinateOccuppied[j] = tmp_d[0];
				coordinateOccuppied[j + 1] = tmp_d[1];
				coordinateOccuppied[j + 2] = tmp_d[2];
				tmp_d.clear();
			}
			nline++;
		}
	}
	rawData->setNum(nAtm, coordinateOccuppied);
	myInput.close();
}