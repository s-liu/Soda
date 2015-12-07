#include "bottlingPlant.h"
#include "MPRNG.h"

extern MPRNG rdm;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : 
    _prt(prt),
    _nameServer(nameServer),
    _numVendingMachines(numVendingMachines),
    _maxShippedPerFlavour(maxShippedPerFlavour),
    _maxStockPerFlavour(maxStockPerFlavour),
    _timeBetweenShipments(timeBetweenShipments) {
        _quantity = new unsigned int[4];
    }

void BottlingPlant::main(){

    // Start
    _prt.print(Printer::Kind::BottlingPlant, 'S');
    Truck t (_prt, _nameServer, *this, _numVendingMachines, _maxStockPerFlavour);
    for(;;){
        unsigned int totalGen = 0;
        for(int i = 0; i < 4; i++) {
            unsigned int num = rdm(0, _maxShippedPerFlavour);
            totalGen += num;
            _quantity[i] = num;
        }
        _prt.print(Printer::Kind::BottlingPlant, 'G', totalGen);
        
        // Yeild between production run
        yield(_timeBetweenShipments);
        // Wait for the truck to pickup the shipment
		try {
			_Accept(~BottlingPlant) {
				isDown = true;
				_Accept(getShipment) {
					break;
				}
			} or _Accept(getShipment){
                _prt.print(Printer::Kind::BottlingPlant, 'P');
            }
		} catch (uMutexFailure::RendezvousFailure) {
			break;
		}
    }

    // End
    _prt.print(Printer::Kind::BottlingPlant, 'F');
    delete[] _quantity;
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
    if(isDown) _Throw Shutdown();

    // transfer item
    for(unsigned int item = 0; item < 4; item++){
        cargo[item] = _quantity[item];   
    }
}
