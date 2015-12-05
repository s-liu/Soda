#ifndef _GROUPOFF_H_
#define _GROUPOFF_H_

#include "watCard.h"
#include <vector>

_Task Groupoff {
    void main();
	Printer& _printer;
	unsigned int _numStudents;
	unsigned int _sodaCost;
	unsigned int _groupoffDelay;
	std::vector<WATCard::FWATCard> _cards;
	
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};
#endif
