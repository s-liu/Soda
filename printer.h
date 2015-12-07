#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

_Monitor Printer {
    private:
        unsigned int _numStudents;
        unsigned int _numVendingMachines;
        unsigned int _numCouriers;
    public:
        enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
        Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
        void print( Kind kind, char state );
        void print( Kind kind, char state, int value1 );
        void print( Kind kind, char state, int value1, int value2 );
        void print( Kind kind, unsigned int lid, char state );
        void print( Kind kind, unsigned int lid, char state, int value1 );
        void print( Kind kind, unsigned int lid, char state, int value1, int value2 );

    private:
        typedef struct {
            Kind kind;
            unsigned int lid;
            char state;
            int value1;
            int value2;
        } Info;
        vector<Info*> _infos;
        void printAll();
        unsigned int getIndex(Kind kind, unsigned int lid);
        void printFinished(unsigned int index);
};

#endif
