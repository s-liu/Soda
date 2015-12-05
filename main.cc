#include "main.h"
#include <string>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

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
	} else if ((verifyInput & ((1<<10)-1)) != ((1<<10)-1)) {
		cerr << "Error: file \"" << configFile << "\" is corrupt." << endl;
	}

}

void uMain::main() {
	char filename[] = "soda.config";
	ConfigParms c;
	processConfigFile( filename, c );
}
