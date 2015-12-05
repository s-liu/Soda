#include "parent.h"
#include "MPRNG.h"

// Random Num Gen
extern MPRG rmd;

Parent::Parent( Printer &prt, bank &bank, unsigned int numStudents, unsigned int parentalDelay ) : 
    _numStudents(numStudents), 
    _parentalDelay(parentalDelay),
    _bank(bank),
    _prtprt() {}

void Parent:main() {
    for(;;){
        // If destructor is called
        // then break from loop
        _Accept(~Parent) {
            break;
        } _Else {
            // Assigning the values
            unsigned int money = rmd(1, 3);
            unsigned int studentID = rmd(0, numStudents-1);
            yeild(_parentalDelay);

            // Printer??
            _bank.deposit(studentID, money);
        }
    }   
}


