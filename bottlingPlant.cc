#include "bottlingPlant.h"
#include "truck.h"

extern MPRNG rmd;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) : 
    _prt(prt),
    _nameServer(nameServer),
    _numVendingNamchines(numVendingMachines),
    _maxShipingPerFlavour(maxShippingPerFlavour),
    _maxStockPerFlavour(maxStockPerFlavour),
    _timeBetweenShipments(timeBetweenShipments) {}

void BottlingPlant::main(){
    for(;;){

        Truck* truck = new Truck(_prt, _nameServer, &this, _numVendingMachine, _maxStockPerFlavour);
        unsigned int quantity = rmd(0, _maxShippedPerFlavour);
        // simulate procution
        for(int num = 0; num < quantity; num++) {
            for(int flav = 0; flav < 4; flav++)
                _prod.push(flav);
        }
        
        // Yeild between production run
        yield(_timeBetweenShipments);
        // Wait for the truck to pickup the shipment
        _Accept(~BottlingPlant) {
            isDown = true;
            break;
        } or _Accept(getShipment);
    }
}

void BottlingPlant::getShipment(unsigned int cargo[]) {
    if(isDown) throw new Shutdown();

    // transfer item
    for(unsigned int item = 0; item < _prod.size(); item++){
        cargo[item] = _prod[item];    
    }
}
