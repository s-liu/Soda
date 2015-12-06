#include "bottlingPlant.h"
#include "MPRNG.h"

extern MPRNG rdm;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : 
    _prt(prt),
    _nameServer(nameServer),
    _numVendingMachines(numVendingMachines),
    _maxShippedPerFlavour(maxShippedPerFlavour),
    _maxStockPerFlavour(maxStockPerFlavour),
    _timeBetweenShipments(timeBetweenShipments) {}

void BottlingPlant::main(){

    // Start
    _prt.print(Printer::Kind::BottlingPlant, 'S');
    new Truck(_prt, _nameServer, *this, _numVendingMachines, _maxStockPerFlavour);
    for(;;){

        unsigned int quantity = rdm(0, _maxShippedPerFlavour);
        // simulate procution
        for (unsigned int num = 0; num < quantity; num++) {
            for (unsigned int flav = 0; flav < 4; flav++) {
                _prod.push_back(flav);
			}
        }
        _prt.print(Printer::Kind::BottlingPlant, 'G', quantity);
        
        // Yeild between production run
        yield(_timeBetweenShipments);
        // Wait for the truck to pickup the shipment
        _Accept(~BottlingPlant) {
            isDown = true;
            break;
        } or _Accept(getShipment);
    }

    // End
    _prt.print(Printer::Kind::BottlingPlant, 'F');
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
    if(isDown) _Throw Shutdown();

    // transfer item
    for(unsigned int item = 0; item < _prod.size(); item++){
        cargo[item] = _prod[item];    
    }

    _prt.print(Printer::Kind::BottlingPlant, 'P');
}
