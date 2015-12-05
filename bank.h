#ifndef _BANK_H_
#define _BANK_H_
#include "vector"

using namespace std;

_Monitor Bank {
    private:
        int balance = 0;
        vector<unsigned int> _accounts;
        uCondition _acclk;
    public:
        Bank( unsigned int numStudents );
        void deposit( unsigned int id, unsigned int amount);
        void withdraw( unsigned int id, unsigned int amount );
};
#endif
