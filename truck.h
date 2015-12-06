#ifndef _TRUCK_H_
#define _TRUCK_H_

#include "nameServer.h"
#include "printer.h"
#include "bottlingPlant.h"

_Task BottlingPlant;

_Task Truck {
    void main();
	Printer &_printer;
	NameServer &_nameServer;
	BottlingPlant &_plant;
	unsigned int _numVendingMachines;
	unsigned int _maxStockPerFlavour;
	unsigned int* _cargo;
	void clear();
	unsigned int total();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};
#endif
