#include "truck.h"
#include "MPRNG.h"

extern MPRNG rdm;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : _printer(prt), _nameServer(nameServer),  _plant(plant), _numVendingMachines(numVendingMachines), _maxStockPerFlavour(maxStockPerFlavour) {
	_cargo = new unsigned int [4];
	clear();
}

Truck::~Truck() {
	delete [] _cargo;
}

void Truck::clear() {
	for (unsigned int i = 0; i < 4; i ++ ) {
		_cargo[i] = 0;
	}
}

unsigned Truck::total() {
	int sum = 0;
	for (unsigned int i = 0; i < 4; i ++ ) {
		sum += _cargo[i];
	}
	return sum;
}
	
	
void Truck::main() {
	_printer.print(Printer::Kind::Truck, 'S');
	VendingMachine** vmList = _nameServer.getMachineList();
	unsigned int curr = 0;
	for (;;) {
		try {
			yield(rdm(1,10));
			_plant.getShipment(_cargo);
			_printer.print(Printer::Kind::Truck, 'P', total());
		} catch (BottlingPlant::Shutdown) {
			clear();
			break;
		}	
		for (;;) {
			if (curr == _numVendingMachines) {
				curr = 0;
				break;
			} else if (total() == 0) {
				break;
			}
			_printer.print(Printer::Kind::Truck, vmList[curr]->getId(), 'd', total());
			unsigned int* inv = vmList[curr]->inventory();
			unsigned int total_not_replenished = 0;
			for (unsigned int i = 0; i < 4; i++) {
				unsigned int replenish = min((_maxStockPerFlavour - inv[i]), _cargo[i]);
				inv[i] += replenish;
				_cargo[i] -= replenish;
				total_not_replenished += _maxStockPerFlavour - inv[i];
			}
			if (total_not_replenished > 0) {
				_printer.print(Printer::Kind::Truck, vmList[curr]->getId(),'U',  total_not_replenished);
			}
			_printer.print(Printer::Kind::Truck, vmList[curr]->getId(), 'D', total());
			vmList[curr]->restocked();
			curr++;
		}
	}
	_printer.print(Printer::Kind::Truck, 'F');
}
