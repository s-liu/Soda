#include "main.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watCardOffice.h"
#include "groupoff.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "bottlingPlant.h"
#include "student.h"
#include "MPRNG.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>

using namespace std;

MPRNG rdm;

void processConfigFile( const char *configFile, ConfigParms &cparms ) {
	ifstream ifs;
	ifs.open( configFile, ifstream::in );
	unsigned int verifyInput = 0x0;
	string input;
	
	while ( !ifs.fail() ) {
		ifs >> input;
		if (input[0] == '#') {
			ifs.ignore(numeric_limits<streamsize>::max(), '\n');
		} else {
			if (input == "SodaCost") {
				ifs >> cparms.sodaCost;
				verifyInput |= 1<<0;
			} else if (input == "NumStudents") {
				ifs >> cparms.numStudents;
				verifyInput |= 1<<1;
			} else if (input == "MaxPurchases") {
				ifs >> cparms.maxPurchases;
				verifyInput |= 1<<2;
			} else if (input == "NumVendingMachines") {
				ifs >> cparms.numVendingMachines;
				verifyInput |= 1<<3;
			} else if (input == "MaxStockPerFlavour") {
				ifs >> cparms.maxStockPerFlavour;
				verifyInput |= 1<<4;
			} else if (input == "MaxShippedPerFlavour") {
				ifs >> cparms.maxShippedPerFlavour;
				verifyInput |= 1<<5;
			} else if (input == "TimeBetweenShipments") {
				ifs >> cparms.timeBetweenShipments;
				verifyInput |= 1<<6;
			} else if (input == "GroupoffDelay") {
				ifs >> cparms.groupoffDelay;
				verifyInput |= 1<<7;
			} else if (input == "ParentalDelay") {
				ifs >> cparms.parentalDelay;
				verifyInput |= 1<<8;
			} else if (input == "NumCouriers") {
				ifs >> cparms.numCouriers;
				verifyInput |= 1<<9;
			} else {
				verifyInput |= 1<<10;
			}
		}
	}
	
	if ((verifyInput & 1<<10) == (1<<10)) {
		cerr << "Error: file \"" << configFile << "\" has extraneous data." << endl;
        exit(EXIT_FAILURE);
	} else if ((verifyInput & ((1<<10)-1)) != ((1<<10)-1)) {
		cerr << "Error: file \"" << configFile << "\" is corrupt." << endl;
        exit(EXIT_FAILURE);
	}

}

void uMain::main() {
	char filename[] = "soda.config";
	ConfigParms c;

	unsigned int seed = getpid();

    try {
		//parse input arguments
        if (argc > 2) {
            stringstream arg;
            arg.str(argv[2]);
            arg >> seed;
            if (arg.fail()) {
                throw -1;
            }
        }
        if (argc > 1) {
            stringstream arg;
            arg.str(argv[1]);
            arg >> filename;
            if (arg.fail()) {
                throw -1;
            }
        }
    } catch (...) {
		// catch error reading inputs
        cerr << "Usage: " << argv[0] << " [ config-files [ random-seed (> 0) ] ]" << endl;
        exit(EXIT_FAILURE);
    }

    // invalid inputs
    if (argc > 3) {
        cerr << "Usage: " << argv[0] << " [ config-files [ random-seed (> 0) ] ]" << endl;
        exit(EXIT_FAILURE);
    }
	processConfigFile( filename, c );

    // initialize seed
    rdm.seed(seed);

	// initialize printer and TallyVotes
	Printer printer(c.numStudents, c.numVendingMachines, c.numCouriers);
	Bank bank(c.numStudents);
	Parent parent(printer, bank, c.numStudents, c.parentalDelay);
	WATCardOffice cardOffice(printer, bank, c.numCouriers);
	Groupoff groupoff(printer, c.numStudents, c.sodaCost, c.groupoffDelay);
	NameServer nameServer(printer, c.numVendingMachines, c.numStudents);
	VendingMachine* vMachine_arr[c.numVendingMachines];
	for (unsigned int i = 0; i < c.numVendingMachines; i++) {
		vMachine_arr[i] = new VendingMachine(printer, nameServer, i, c.sodaCost, c.maxStockPerFlavour);
	}
	BottlingPlant* bottlingPlant = new BottlingPlant(printer, nameServer, c.numVendingMachines, c.maxShippedPerFlavour, c.maxStockPerFlavour, c.timeBetweenShipments);
	//BottlingPlant bottlingPlant (printer, nameServer, c.numVendingMachines, c.maxShippedPerFlavour, c.maxStockPerFlavour, c.timeBetweenShipments);
	Student* student_arr[c.numStudents];
	for (unsigned int i = 0; i < c.numStudents; i++) {
		student_arr[i] = new Student(printer, nameServer, cardOffice, groupoff, i, c.maxPurchases);
	}
		
	
	for (unsigned int i = 0; i < c.numStudents; i++) {
		delete student_arr[i];
	}
	delete bottlingPlant;

	for (unsigned int i = 0; i < c.numStudents; i++) {
		delete vMachine_arr[i];
	}
}
