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

        _quantity = rdm(0, _maxShippedPerFlavour);
        _prt.print(Printer::Kind::BottlingPlant, 'G', _quantity);
        
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
    for(unsigned int item = 0; item < 4; item++){
        cargo[item] = _quantity;   
    }

    _prt.print(Printer::Kind::BottlingPlant, 'P');
}
