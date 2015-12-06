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

            // Printer??
            _bank.deposit(studentID, money);
        }
    }   
}


