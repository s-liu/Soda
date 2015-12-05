#include "bank.h"

Bank::Bank( unsigned int numStudents ){
    _accounts = vector<unsigned int>(numStudents);
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    _accounts[id] += amount;

    // If there are accounts waiting for deposit, then unblock all 
    // and let them check again
    while( !_acclk.empty() ) _acclk.signal();
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    
    // if the account does not have emough funding, then wait
    while( _accounts[id] < amount ) {
        _acclk.wait();
    }

    _accounts[id] -= amount;
}
