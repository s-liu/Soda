#include "printer.h"

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) : 
    _numStudents(numStudents),
    _numVendingMachines(numVendingMachines),
    _numCouriers(numCouriers) {
        _infos = vector<Info*>( 6 + numStudents + numVendingMachines + numCouriers );

        cout << "Parent\tGroupoff\tWATOff\tNames\tTruck\tPlant\t";
        for(unsigned int i = 0; i < numStudents; i++)
            cout << "Stud" << i << "\t";
        for(unsigned int i = 0; i < numVendingMachines; i++)
            cout << "Mach" << i << "\t";
        for(unsigned int i = 0; i < numCouriers; i++)
            cout << "Cour" << i << "\t";
        cout << endl;

        for(unsigned int i = 0; i < 6 + numStudents + numVendingMachines + numCouriers; i++)
            cout << "*******\t";
        cout << endl;
    }

int Printer::getIndex(Kind kind) {
    switch(kind){
        case Kind::Parent: return 0;
        case Kind::Groupoff: return 1;
        case Kind::WATCardOffice: return 2;
        case Kind::NameServer: return 3;
        case Kind::Truck: return 4;
        case Kind::BottlingPlant: return 5;
        case Kind::Student: return 6;
        case Kind::Vending: return 6 + _numStudents;
        case Kind::Courier: return 6 + _numStudents + _numVendingMachines;
    }
    return -1;
}

void Printer::printAll() {
    for(unsigned int index = 0; index < _infos.size(); index++){
        Info* info = _infos[index];
        if(info == NULL) {
            cout << "\t";
            continue;
        }

        if(info -> kind == Kind::Parent) {
            if(info -> state == 'S') {
                cout << 'S';
            } else if (info -> state == 'D') {
                cout << 'D' << info -> lid << info -> value1;
            } else if (info -> state == 'F') {
                cout << 'F';
            }
        } else if(info -> kind == Kind::Groupoff) {
            
            
        } else if(info -> kind == Kind::WATCardOffice) {
        
        } else if(info -> kind == Kind::NameServer) {
        
        } else if(info -> kind == Kind::Truck) {
        
        }

        cout << "\t";

        // Delete the info object
        // And set the index to null
        delete info;
        _infos[index] = NULL;
    }
}

void Printer::print( Kind kind, char state ){

}

void Printer::print( Kind kind, char state, int value1 ){

}

void Printer::print( Kind kind, char state, int value1, int value2 ){

}

void Printer::print( Kind kind, unsigned int lid, char state ){

}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){

}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){

}
