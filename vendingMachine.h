#ifndef _VENDING_MACHINE_H_
#define _VENDING_MACHINE_H_
#include "watCard.h"
#include "nameServer.h"
#include "printer.h"

_Task NameServer;

_Task VendingMachine {
    void main();
	Printer &_printer;
	NameServer &_nameServer;
	unsigned int _id;
	unsigned int _sodaCost;
	unsigned int _maxStockPerFlavour;
	unsigned int* _inventory;
	uCondition _lock;
	unsigned int _currFlavour;
	WATCard *_currCard;
	unsigned int _exception_flag;
  public:
    enum Flavours { CLASSIC = 0, LIME = 1, ROOT_BEER = 2, CREAM_SODA = 3 };                 // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};
#endif
