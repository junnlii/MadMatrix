#include <iostream>
#include <string>
#include "Title.h"
#include "Xtal.h"


void createNPUs(Xtal);
void MadEng(Xtal, double);		//Module: Regular Madelung Energy Calculation 

double convergence = 0.0001;

int main() {
	License();
	Disclaimer();
	Xtal FirstModel;
	int funcOptions;
	
	char confirm='N';
	std::string aString = "Welcome to Madelung lattice energy calculation";
	
	do
	{
		displaymenu();
		std::cout << "Enter your choice(1-5):";
		std::cin >> funcOptions;
		
		switch (funcOptions) {
		case 1:
			std::cout << "Read in a VASP POSCAR\n";
			FirstModel.LoadingXtal();
			FirstModel.PrintXtal();
			
			break;
		case 2:
			system("CLS");
			std::cout << "Set polyhedral groups\n";
			std::cout << " determine the polyhedral unit from nearest neightbors\n";
			std::cout << " if NPU.list ready, enter 1 now						\n";
			std::cout << "    not yet,        enter 0 to create and load in		\n";
			
			int myOpt;
			std::cin >> myOpt;
			if (myOpt == 0) {
				std::cout << " create a NPU list\n";
				createNPUs(FirstModel);
			}
			FirstModel.LoadNPUList();
			break;
		case 3:
			std::cout << "Calculate Madelung matrix\n";
			MadEng(FirstModel, convergence);
			break;
		case 4:
			std::cout << "Calculate Madelung energy\n";
			std::cout << "you need to provide a file for charge vectors\n";
			//ModES();
			break;
		case 5:
			std::cout << "Exit" << "\n";
			break;
		default:
			std::cout << "invalid functions, check menu please";
		}

		std::cout << "\nPress y or Y to continue:";
		std::cin >> confirm;
		system("CLS");
	} while (confirm == 'y' || confirm == 'Y');


	system("pause");
	return 0;
}