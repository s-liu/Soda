#ifndef _WATCARD_OFFICE_H_
#define _WATCARD_OFFICE_H_

#include <uFuture.h>
#include "watCard.h"
#include "bank.h"
#include <queue>

_Task WATCardOffice {
	struct Args {
		unsigned int sid;
		unsigned int amount;
		WATCard* card;
		Args( unsigned int sid, unsigned amount, WATCard* card ) : sid( sid ), amount( amount ), card( card ) {}
	}; 

    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;          // return future
        Job( Args args ) : args( args ) {}
    };

    _Task Courier { 
		void main();
	};                 // communicates with bank

    void main();
	Printer &_printer;
	Bank &_bank;
	unsigned int _numCouriers;
	Courier** _courier_arr;
	queue<Job> _job_list;
	
  public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};
#endif
