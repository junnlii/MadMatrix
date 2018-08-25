
#include "DataStructure.h"
#include "Xtal.h"
#include <iostream>
#include <fstream>


double offdiagonalMM(int, NPU, int, NPU,vect3D);

void MadEng(Xtal FirstModel, double convergence)
{
	system("cls");
	std::cout << "\n";
	std::cout << "Set up the polyhedral structure of the first crystal model \n";
	std::cout << "Input the control file: \n";
	
	double one = 1.0;
		
	int mMD = FirstModel.getNocc();		//the dimension of MadMat: mMD
	int totalME = mMD*(mMD + 1) / 2;
	double *madMat = new double[totalME];
	double *preMat = new double[totalME];

	//initialize all upper right elements of Madelung Matrix

	for (int i = 0;i < totalME;i++) {
		madMat[i] = 0.0;
	}
	
	ofstream madOutput;
	madOutput.open("MadEnergy", ios::app);

	//calculate all the diagonal elements of Madelung Matric for the center cell's NPUs
	int centerID, numVertice;
	int diaElemIndex = 0;
	vect3D centerCoord;
	vect3D *verticeCoord;
	vect3D centerPos,*verticePos;
	vect3D temA, temB, temC;

	for (int i = 0;i < mMD;i++) {
		
		diaElemIndex = i*mMD - i*(i - 1) / 2;
		centerID= FirstModel.occNPU[i].getCenterID();
		centerCoord = FirstModel.getCoord(centerID);
		temA = FirstModel.getAA();
		temB = FirstModel.getBB();
		temC = FirstModel.getCC();
		centerPos = vect3DPlusScale(centerCoord.getX(), temA,
			centerCoord.getY(), temB);
		centerPos = vect3DPlusScale(one, centerPos,
			centerCoord.getZ(),temC );

		FirstModel.occNPU[i].setCPos(centerPos);				//store center position for later use

		numVertice = FirstModel.occNPU[i].getNumVertice();
	
		verticeCoord = new vect3D[numVertice];
		verticePos = new vect3D[numVertice];
	
		for (int j = 0;j < numVertice;j++) {
			verticeCoord[j] = FirstModel.occNPU[i].getVerticePos()[j];
			temA = FirstModel.getAA();
			temB = FirstModel.getBB();
			temC = FirstModel.getCC();
			verticePos[j] = vect3DPlusScale(verticeCoord[j].getX(), temA,
				verticeCoord[j].getY(), temB);
			verticePos[j] = vect3DPlusScale(one, verticePos[j],
				verticeCoord[j].getZ(), temC);

			FirstModel.occNPU[i].setVPos(j, verticePos[j]);					//store vertice postions for each NPU for later use

			madMat[diaElemIndex] += -2.0/ vect3Dlength(centerPos, verticePos[j])/double(numVertice);
			if (j > 0 & numVertice > 1) {
				for (int k=0;k<j;k++) madMat[diaElemIndex] += 2.0/ vect3Dlength(verticePos[k], verticePos[j]) / double(numVertice*numVertice);
			}
				
		}

		
		delete[]verticeCoord;
		delete[]verticePos;
		//
	}
	//calculate all the off-diagonal elements of upper-right Madelung Matrix for the center cell's NPUs
	int offDiaInd = 0;
	vect3D zero(0.0, 0.0, 0.0);
	if (mMD > 1) {
		for (int i = 0;i < mMD;i++) {
			offDiaInd = i*mMD - i*(i - 1) / 2;
			for (int j = i + 1;j < mMD;j++) {
				offDiaInd += 1;
				madMat[offDiaInd] += offdiagonalMM(mMD, FirstModel.occNPU[i], mMD, FirstModel.occNPU[j], zero);
	
			}
		}
	}
	madOutput << " Madelung matrix dimension: " << mMD << " X " << mMD << "\n";
	double calErrors=1.0,diff,mag;
	int iteration = 10;
	int it = 1;
	vect3D latVec;
	int total;
	int id;
	double madEnergy=0.0,chargeI,chargeJ;


	while (calErrors>convergence&it<iteration){
		std::cout << "\niteration= " << it << "\n";
		total = 0;
		for (int i = 0;i < mMD;i++) {
			for (int j = i;j < mMD;j++) {
				preMat[total] = madMat[total];
				if (i > 0) {
					for (int k = 0;k < i;k++) { std::cout << "	"; }
				}
				std::cout << preMat[total] << "	";
				total++;
			}
			std::cout << "\n";
		}
		total = 0;
		//loop over lattice summation for NPUS
		
		for (int i = -it;i < it + 1;i++) {
			for (int j = -it;j < it + 1;j++) {
				for (int k = -it;k < it + 1;k++) {
					if (abs(i) > (it - 1) | abs(j) > (it - 1) | abs(k) > (it - 1)) {
						temA = FirstModel.getAA();
						temB = FirstModel.getBB();
						temC = FirstModel.getCC();
							latVec = vect3DPlusScale(double(i), temA,
								double(j), temB);
							latVec = vect3DPlusScale(one, latVec,
								double(k), temC);
							for (int ic = 0;ic < mMD;ic++) {					//index for NPUs in center cell
								id = ic*mMD - ic*(ic - 1) / 2;
								for (int il = ic;il < mMD;il++) {
									madMat[id] += offdiagonalMM(mMD, FirstModel.occNPU[ic], mMD, FirstModel.occNPU[il], latVec);
									id += 1;
								}
							}
							total++;
						}
				}
			}
		}
		it ++ ;
		std::cout << " Total cell summation= " << total << "\n";
		//check convergence
		calErrors= abs(preMat[0] - madMat[0]);
		mag = preMat[0];
		for (int i = 0;i < totalME;i++) {
			diff = abs(preMat[i] - madMat[i]);
			if (calErrors < diff) {
				calErrors = diff;mag = preMat[i];
			}
		}
		calErrors = abs(calErrors / mag);
		std::cout << " max diff= " << calErrors;
	}
	if (it >= iteration&calErrors > convergence) {
		
		std::cout << " Warning: the calculation of Madelung Matrix did not converge after iteration " << iteration << "\n";
		exit (-1);
	}
	std::cout << "Finish the Regular Madelun Energy Calculation moduel\n";

	madOutput<< fixed << showpoint << setprecision(4);
	for (int i = 0;i < mMD;i++) {
		id = i*mMD - i*(i - 1) / 2;
		for (int j = 0;j < mMD;j++) {

			if (i > j) {
				it = j*mMD - j*(j - 1) / 2 + i - j;
			}
			else {
				it = id + j - i;
			}
			madOutput << madMat[it]<<"	";
		}
		madOutput << "\n";
	}
	//check the regular Madelung energy and constant
	for (int i = 0;i < mMD;i++) {
		id = i*mMD - i*(i - 1) / 2;
		chargeI = FirstModel.occNPU[i].getValence();
		for (int j = 0;j < mMD;j++) {
			chargeJ = FirstModel.occNPU[j].getValence();
			if (i> j) {
				it= j*mMD - j*(j - 1)/2 + i-j;
				madEnergy += chargeI*madMat[it]*chargeJ/2.0;
			}
			else {
				it = id + j - i;
				madEnergy += chargeI*madMat[it] * chargeJ / 2.0;
			}
		}
	}

	std::cout << "\n Regular Madelung energy per cell= " << madEnergy << "\n";
	std::cout << "\n Regular Madelung constant per NPU= " << madEnergy/double(mMD) << "\n";
	
	madOutput << "\n To convert to the conventional Madelung constant, you need to time the bond length unit\n";
	std::cout << "check Main results in the text file: MadEnergy" << "\n";
	

	delete[] madMat;
	madOutput.close();
}

double offdiagonalMM(int aSet, NPU A, int bSet, NPU B, vect3D latticeR) {
	double value = 0.0, one = 1.0, mone=-1.0;
	double distance = 0.0;
	int aVer, bVer;
	vect3D temA, temB, temC;
	aVer = A.getNumVertice();
	bVer = B.getNumVertice();
	temB = B.getCPos();
	vect3D far;
	far= vect3DPlusScale(one, temB, one, latticeR);
	temA = A.getCPos();
	distance = vect3Dlength(temA, far);

	value += one / distance;							//calculate the center to far center;

	for (int i = 0;i < aVer;i++) {						//calculate the center vertice to far center;
		temA = A.getVPos(i);
		distance = vect3Dlength(temA, far);

		if (distance > 0.001) {
			value += mone / distance / double(aVer);
		}
	}
	for (int i = 0;i < bVer;i++) {						//calculate the center to far vertice;
		temB = B.getVPos(i);
		temA = A.getCPos();
		far = vect3DPlusScale(one,temB, one, latticeR);
		distance = vect3Dlength(temA, far);

		if (distance > 0.001) {
			value += mone / distance/double(bVer);
		}
	}

	for (int i = 0;i < bVer;i++) {						//calculate the center vertice to far vertice;
		temB = B.getVPos(i);
		far = vect3DPlusScale(one, temB, one, latticeR);

for (int j = 0; j < aVer; j++) {
	temA = A.getVPos(j);
	distance = vect3Dlength(temA, far);

	if (distance > 0.001) {
		value += one / distance / double(bVer*aVer);
	}
}
	}

	return value;
}

// calculate cationic nearest nighbor list
void createNPUs(Xtal first) {
	std::cout << "To create a set of NPUs, a criteria needed\n";
	std::cout << "Please prepare a NPU paramenter file: NPUpar.txt\n";
	std::cout << "		1st line:  total NPU number  \n";
	std::cout << "		2nd - totalNpus-th lines: cationic index, valence, cut-off radius \n";
	std::cout << "			cationic index is the order number of that cation in POSCAR \n";
	std::cout << "			notepad will be used to create this parameter file\n";
	std::cout << "			save it as NPUpar.txt\n";
	std::cout << "			if you already have it, just close notepad, no save\n";


	bool setNPU = false;

	int totalNpus = 0;
	int *idx, NPUs;
	const int maxNPU = 24;
	double *val, *rang;
	double NNx[maxNPU], NNy[maxNPU], NNz[maxNPU];

	int totalAtm = first.getNum();
	std::cout << "total atoms: " << totalAtm << "\n";
	vect3D *pCoord = new vect3D[totalAtm];
	for (int i = 0; i < totalAtm; i++) {
		pCoord[i] = first.getCoord(i);
		pCoord[i].vect3DPrint();
	}

	int nx = 1, ny = 1, nz = 1;

	vect3D aa, bb, cc;
	aa = first.getAA();
	bb = first.getBB();
	cc = first.getCC();
	int expandCell = totalAtm * (2 * nx + 1)*(2 * ny + 1)*(2 * nz + 1);
	vect3D *expCoord = new vect3D[expandCell];
	std::cout << "expanding cells: " << expandCell << "\n";

	double xx, yy, zz;
	int iex = 0;
	for (int tot = 0; tot < totalAtm; tot++) {
		for (int ix = -nx; ix < nx + 1; ix++) {
			xx = pCoord[tot].getX() + double(ix);
			
			for (int iy = -ny; iy < ny + 1; iy++) {
				yy = pCoord[tot].getY() + double(iy);
				
				for (int iz = -nz; iz < nz + 1; iz++) {
					zz = pCoord[tot].getZ() + double(iz);
					
					vect3D tem(xx, yy, zz);
					expCoord[iex] = tem;
					iex++;
				}
			}
		}
	}
	std::cout << "expanding total atoms: " << iex << "\n";
	
	vect3D center, far, diff;
	double one = 1.0, minus = -1.0, dis;
	int iPass = 0;
	double mindis = 0.25;
	ifstream myInput("NPUpar.txt");

	if (!myInput.good())
	{
		std::cout << " cannot find input file: NPUpar.txt\n";
		std::cout << " please use notepad create such a NPU paramenter file\n";
		exit (-1);
	}

	myInput.close();
	do {
			ofstream myOutput("NPU.list");
			ifstream myInput("NPUpar.txt");
			myInput >> totalNpus;
			myOutput << totalNpus <<" "<< totalNpus <<" "<< 0 << "\n";

			idx = new int[totalNpus];
			val = new double[totalNpus];
			rang = new double[totalNpus];
			for (int i = 0; i < totalNpus; i++) {
				myInput >> idx[i] >> val[i] >> rang[i];
			}
			std::cout << " total NPUs= " << totalNpus << "\n";
			

			for (int i = 0; i < totalNpus; i++) {
				myOutput << idx[i]<<" ";
			}
			for (int i = 0; i < totalNpus; i++) {
				myOutput << val[i]<<" ";
			}
			myOutput << "\n";
			myInput.close();

			for (int i = 0; i < totalNpus; i++) {
				center = pCoord[idx[i]];
				NPUs = 0;
				std::cout << " calculate NN for " << idx[i] << "\n";
				center.vect3DPrint();
				for (int j = 0; j < iex; j++) {
					far = expCoord[j];
					diff = vect3DPlusScale(one, far, minus, center);
					dis = vect3DModule(aa, bb, cc, diff);
					if (dis < rang[i]&&dis>mindis) {
						NNx[NPUs] = expCoord[j].getX();
						NNy[NPUs] = expCoord[j].getY();
						NNz[NPUs] = expCoord[j].getZ();
						
						std::cout << fixed << showpoint << setprecision(4);
						std::cout << " NN# " << NPUs << " : "<<dis<<" , " << NNx[NPUs] << " , " << NNy[NPUs] << " , " << NNz[NPUs] << "\n";
						NPUs++;
					}
					if (NPUs > maxNPU) {
						std::cout << "WARNING: Too many NN for " << idx[i] << "\n";
					}
				}
				myOutput << NPUs << "\n";
				for (int j = 0; j < NPUs; j++) {
					myOutput << fixed << showpoint << setprecision(5);
					myOutput << NNx[j] <<" "<< NNy[j] <<" "<< NNz[j] << "\n";
				}
			}
			myOutput.close();
			
			//check the NN file
			std::cout << "check if the new NPU.list good or not\n";
	
		system("notepad NPU.list");
		std::cout << " if good, enter 1; need to modify NPUpar.txt, enter 0\n";
			std::cin >> iPass;
			if (iPass == 1) { setNPU = true; 
			std::cout<<" the NPU.list has been created, remember to go back <main menu> option 2 \n";
			std::cout << "	then to choose 1 to load this NPU list before calculation Madelung matrix\n";
			}
			else
			{
				setNPU = false;
				system("notepad NPUpar.txt");
			}
	} while (setNPU==false);
	system("cls");
}