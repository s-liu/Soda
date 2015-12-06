#include "printer.h"

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) : 
    _numStudents(numStudents),
    _numVendingMachines(numVendingMachines),
    _numCouriers(numCouriers) {
        _infos = vector<Info*>( 6 + numStudents + numVendingMachines + numCouriers );

        cout << "Parent\tGropoff\tWATOff\tNames\tTruck\tPlant\t";
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

unsigned int Printer::getIndex(Kind kind) {
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
    return 404; // Should not reach here
}

void Printer::printAll() {
    for(unsigned int index = 0; index < _infos.size(); index++){
        Info* info = _infos[index];
        if(info == NULL) {
            cout << "\t";
            continue;
        }
        if(info -> kind == Kind::Parent) {
            if(info -> state == 'S' || info -> state == 'F') {
                cout << info -> state;
            } else if (info -> state == 'D') {
                cout << info -> state << info -> lid << info -> value1;
            }
        } else if(info -> kind == Kind::Groupoff) {
            if(info -> state == 'S' || info -> state == 'F') {
                cout << info -> state;
            } else if (info -> state == 'D') {
                cout << info -> state << info -> value1;
            }
        } else if(info -> kind == Kind::WATCardOffice) {
            if(info -> state == 'S' || info -> state == 'W' || info -> state == 'F') {
                cout << info -> state;
            } else if (info -> state == 'C' || info -> state == 'T') {
                cout << info -> state << info -> lid << info -> value1;
            }
        } else if(info -> kind == Kind::NameServer) {
            if(info -> state == 'S' || info -> state == 'F') {
                cout << info -> state;
            } else if (info -> state == 'N') {
                cout << info -> state << info -> lid << info -> value1;
            } else if (info -> state == 'R') {
                cout << info -> state << info -> lid;
            }
        } else if(info -> kind == Kind::Truck) {
            if(info -> state == 'S' || info -> state == 'F') {
                 cout << info -> state;
            } else if (info -> state == 'd' || info -> state == 'U' || info -> state == 'D') {
                cout << info -> state << info -> lid << info -> value1;
            } else if (info -> state == 'P') {
                cout << info -> state << info -> value1;
            }
        } else if(info -> kind == Kind::BottlingPlant) {
            if(info -> state == 'S' || info -> state == 'F' || info -> state == 'P') {
                cout << info -> state;
            } else if (info -> state == 'G') {
                cout << info -> state << info -> value1;
            }
        } else if(info -> kind == Kind::Student) {
            if(info -> state == 'L' || info -> state == 'F') {
                cout << info -> state;
            } else if (info -> state == 'V') {
                cout << info -> state << info -> lid;
            } else if (info -> state == 'S') {
                cout << info -> state << info -> value1 << info -> value2 ;
            } 
        } else if(info -> kind == Kind::Vending) {
            if(info -> state == 'r' || info -> state == 'F' || info -> state == 'R') {
                cout << info -> state;
            } else if (info -> state == 'B') {
                cout << info -> state << info -> value1 << info -> value2;
            } else if (info -> state == 'S') {
                cout << info -> state << info -> value1;
            }
        } else if(info -> kind == Kind::Courier) {
            if(info -> state == 'S' || info -> state == 'F') {
                cout << info -> state;
            } else if (info -> state == 't' || info -> state == 'T') {
                cout << info -> state << info -> lid << info -> value1;
            }
        }

        cout << "\t";
        // Delete the info object
        // And set the index to null
        delete info;
        _infos[index] = NULL;
    }
}

void Printer::printFinished(unsigned int index) {
    printAll();
    for(unsigned int i = 0; i < _infos.size(); i++) {
        if(i == index) {
            cout << 'F';
        } else {
            cout << "...";
        }
        cout << "\t";
    }
    cout << endl;
}

void Printer::print( Kind kind, char state ){
    unsigned int index = getIndex(kind);
    if(state == 'F') {
        printFinished(index);
        return;
    }

    if(_infos[index] != NULL) {
        printAll();
    }

    Info* info = new Info();
    info -> kind = kind;
    info -> state = state;
    _infos[index] = info;
}

void Printer::print( Kind kind, char state, int value1 ){
    unsigned int index = getIndex(kind);
    if(state == 'F') {
        printFinished(index);
        return;
    }

    if(_infos[index] != NULL) {
        printAll();
    }

    Info* info = new Info();
    info -> kind = kind;
    info -> state = state;
    info -> value1 = value1;
    _infos[index] = info;
}

void Printer::print( Kind kind, char state, int value1, int value2 ){
    unsigned int index = getIndex(kind);
    if(state == 'F') {
        printFinished(index);
        return;
    }

    if(_infos[index] != NULL) {
        printAll();
    }

    Info* info = new Info();
    info -> kind = kind;
    info -> state = state;
    info -> value1 = value1;
    info -> value2 = value2;
    _infos[index] = info;
}

void Printer::print( Kind kind, unsigned int lid, char state ){
    unsigned int index = getIndex(kind) + lid;
    if(state == 'F') {
        printFinished(index);
        return;
    }

    if(_infos[index] != NULL) {
        printAll();
    }

    Info* info = new Info();
    info -> kind = kind;
    info -> state = state;
    _infos[index] = info;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ){
    unsigned int index = getIndex(kind) + lid;
    if(state == 'F') {
        printFinished(index);
        return;
    }

    if(_infos[index] != NULL) {
        printAll();
    }

    Info* info = new Info();
    info -> kind = kind;
    info -> state = state;
    info -> value1 = value1;
    _infos[index] = info;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ){
    unsigned int index = getIndex(kind) + lid;
    if(state == 'F') {
        printFinished(index);
        return;
    }

    if(_infos[index] != NULL) {
        printAll();
    }

    Info* info = new Info();
    info -> kind = kind;
    info -> state = state;
    info -> value1 = value1;
    info -> value2 = value2;
    _infos[index] = info;
}
