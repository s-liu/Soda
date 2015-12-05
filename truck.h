#ifndef _TRUCK_H_
#define _TRUCK_H_

#include "nameServer.h"

_Task Truck {
    void main();
	Printer &_printer;
	NameServer &_nameServer;
	BottlingPlant &_plant;
	unsigned int _numVendingMachines;
	unsigned int _maxStockPerFlavour;
	unsigned int* _cargo;
	void clear();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};
