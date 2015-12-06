#ifndef _NAMESERVER_H_
#define _NAMESERVER_H_

#include <vector>
#include "vendingMachine.h"
#include "printer.h"
using namespace std;

_Task VendingMachine;

_Task NameServer {
    private:
        Printer& _prt;
        unsigned int _numVendingMachines;
        unsigned int _numStudents;
        vector<VendingMachine*> _machineList;
        vector<int> _studentLocList;
        void main();
    public:
        NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
        void VMregister( VendingMachine* vendingmachine );
        VendingMachine* getMachine( unsigned int id );
        VendingMachine** getMachineList();
};

#endif
