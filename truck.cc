#include "truck.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : _printer(prt), _plant(plant), _numVendingMachines(numVendingMachines), _maxStockPerFlavour(maxStockPerFlavour) {
	unsigned int cargo [4];
	_cargo = cargo;
	clear();
}

void Truck::clear() {
	for (unsigned int i = 0; i < 4; i ++ ) {
		_cargo[i] = 0;
	}
}

bool Truck::empty() {
	int sum = 0;
	for (unsigned int i = 0; i < 4; i ++ ) {
		sum += _cargo[i];
	}
	return (sum == 0);
}
	
	
void Truck::main() {
	VendingMachine** vmList = _nameServer.getMachineList();
	for (;;) {
		try {
			yield(rdm(1,10));
			plant.getShipment(_cargo);
		} catch (BottlingPlant::Shutdown) {
			break;
		}	
		unsigned int curr = 0;
		for (;;) {
			if (curr == _numVendingMachines) {
				curr = 0;
				break;
			} else if (empty()) {
				break;
			}
			unsigned int* inv = vmList[curr]->inventory();
			for (unsigned int i = 0; i < 4; i++) {
				unsigned int replenish = min ((maxStockPerFlavour - inv[i]), _cargo[i]);
				inv[i] += replenish;
				_cargo[i] -= replenish;
			}
			curr++;
		}
	}
}
