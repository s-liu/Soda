#include "parent.h"
#include "MPRNG.h"

// Random Num Gen
extern MPRNG rdm;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) : 
    _numStudents(numStudents), 
    _parentalDelay(parentalDelay),
    _prt(prt),
    _bank(bank) {}

void Parent::main() {
    // Parent Start
    _prt.print(Printer::Kind::Parent, 'S');
    
    for(;;){
        // If destructor is called
        // then break from loop
        _Accept(~Parent) {
            break;
        } _Else {
            // Assigning the values
            unsigned int money = rdm(1, 3);
            unsigned int studentID = rdm(0, _numStudents-1);
            yield(_parentalDelay);

            // Give student studentID, money amount
            _prt.print(Printer::Kind::Parent, studentID, 'D', (int)money);
            _bank.deposit(studentID, money);
        }
    }  

    // Parent Finish
    _prt.print(Printer::Kind::Parent, 'F');
}


