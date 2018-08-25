#include "Title.h"

void displaymenu() {
	std::cout << " =========================================================   " << "\n";
	std::cout << "                 Madelung calculation                       " << "\n";
	std::cout << " =========================================================   " << "\n";
	std::cout << "     1.Read in a VASP POSCAR: need input file name          " << "\n";
	std::cout << "     2.Set polyhedral groups: by a file or algorithm        " << "\n";
	std::cout << "     3.Calculate Madelung matrix: need the set of Polyhedra " << "\n";
	std::cout << "     4.Calculate Madelung energy: need charge vector        " << "\n";
	std::cout << "     5.Exit			                                      " << "\n";
}

void License()  //display the information of the HTPD
{
	std::string idum;
	std::cout << "--------------------------------------------------------------\n";
	std::cout << "																\n";
	std::cout << "  Welcome to Madelung lattice energy calculation of Materials \n";
	std::cout << "																\n";
	std::cout << "          ----Authors: Zhenlian Chen and Jun Li----	        \n";
	std::cout << "             Ningbo Institute of Materials, CAS               \n";
	std::cout << "																\n";
	std::cout << "            This software was registered with NCAC            \n";
	std::cout << "           The National Copyright Administration of	        \n";
	std::cout << "               the People's Republic of China                 \n";
	std::cout << "             Registration number (2015SR153209)               \n";
	std::cout << "																\n";
	std::cout << "      ** How to cite this article, if useful to your RD **	\n";
	std::cout << "       Z.Chen, J.Li, J. Comput. Chem. 2016, 37, 1476-1483.	\n";
	std::cout << "                 DOI : 10.1002 / jcc.24360					\n";
	std::cout << "																\n";
	std::cout << "------------------Enter to continue...------------------------\n";

	std::cin.get();

	system("CLS");
}
void Disclaimer()
{
	int idum;
	std::cout << "--------------------------------------------------------------\n";
	std::cout << "																\n";
	std::cout << "                       DISCLAIMER                             \n";
	std::cout << "     The software is provided \"AS IS\" for illustrative      \n";
	std::cout << "    purposes only which provides users with programming       \n";
	std::cout << "    information regarding the method, implementation, and     \n";
	std::cout << "   application in academic research, without any warranties   \n";
	std::cout << "    and support. The authors assume no responsibility or      \n";
	std::cout << "            liability for the use of the software,            \n";
	std::cout << "   conveys no license or title under any patent, copyright,   \n";
	std::cout << "              or mask work right to the product.              \n";
	std::cout << "      The authors reserve the right to make changes in        \n";
	std::cout << "    the software without notification. The authors also       \n";
	std::cout << "   make no representation or warranty that such application   \n";
	std::cout << "    will be suitable for the specified use without further    \n";
	std::cout << "                   testing or modification.                   \n";
	std::cout << "																\n";
	std::cout << "------------------Enter to continue...------------------------\n";

	std::cin.get();
	system("CLS");
}