#ifndef _BOTTLINGPLANT_H_
#define _BOTTLINGPLANT_H_

#include "vector"
#include "nameServer.h"

_Task BottlingPlant {
    private:
        void main();
        Printer& _prt;
        NameServer& _nameServer;
        unsigned int _numVendingMachines;
        unsigned int _maxShippedPerFlavour;
        unsigned int _maxStockPerFlavour;
        unsigned int _timeBetweenShipments;
        vector<unsigned int> _prod;
        bool isDown = false;
    public:
        _Event Shutdown {}; // shutdown plant
        BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
            unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
            unsigned int timeBetweenShipments );
        void getShipment( unsigned int cargo[] );
};

#endif
