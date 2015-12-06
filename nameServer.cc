#include "nameServer.h"

NameServer::NameServer( Printer& prt, unsigned int numVendingMachines, unsigned int numStudents ) : 
       _prt(prt), 
       _numVendingMachines(numVendingMachines),
       _numStudents(numStudents){
       
           for(unsigned int i = 0; i < _numStudents; i++){
                _studentLocList.push_back(i % _numVendingMachines);     
           }
       }

void NameServer::VMregister( VendingMachine* vendingmachine ) {
    _machineList.push_back(vendingmachine);
}

VendingMachine* NameServer::getMachine( unsigned int id ) {
    VendingMachine* machine = _machineList[_studentLocList[id]];
    _studentLocList[id] = ( _studentLocList[id] + 1 ) % _numVendingMachines;
    return machine;
}

VendingMachine** NameServer::getMachineList() {
    return &_machineList[0];
}

void NameServer::main(){
    for(unsigned int currentVM = 0; currentVM < _numVendingMachines; currentVM ++){
        _Accept(VMregister);
    }

    // Wait for task to call getMachine or get MachineList
    for(;;){
        _Accept(~NameServer){
            break;
        } or _Accept(getMachine, getMachineList);
    }
}
