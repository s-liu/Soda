#include "nameServer.h"

NameServer::NameServer( Printer& prt, unsigned int numVendingNamechines, unsigned int numStudents ) : 
       _prt(prt), 
       _numVendingMachines(numVendingMachines),
       _numStudents(numStudents){
       
           for(int i = 0; i < _numStudents; i++){
                _studentLocList.push(i % _numVendingMachines);     
           }
       }

void NameServer::VMregister( VendingMachine* vendingmachine ) {
    _machineList.push(vendingmachine);
}

VendingMachine* getMachine( unsigned int id ) {
    VendingMachine* machine = _machineList[_studentLocList[id]];
    _studentLocList[id] = ( studentLocList[id] + 1 ) % _numVendingMachines;
    return machine;
}

VendingMachine** getMachineList() {
    return &_machineList[0];
}
