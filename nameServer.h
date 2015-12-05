#ifndef _NAMESERVER_H_
#define _NAMESERVER_H_

#include "vector"
using namespace std;

_Task NameServer {
    private:
        unsigned int _numVendingMachines;
        unsigned int _numStudents;
        Printer& _prt;
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
