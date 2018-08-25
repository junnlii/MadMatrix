#pragma once
#include "DataStructure.h"


class Xtal: public Lattice, public pCell {
	
	string title;
	int totalNPU, nocc, nvac;


	int PrintOption = 0;	//0: no print out; 1: print out POSCAR

public:
	//Lattice abc;
	//pCell center;
	NPU *occNPU;
	NPU *vacNPU;
	
	Xtal() {}
	~Xtal() {}
	void LoadingXtal();		//input crystall structure from VASP POSCAR
	void PrintXtal();		//print out setup of the lattice and cell
	void LoadNPUList();		//Load the GPU information
	int getNocc() { return nocc; }
	

};
