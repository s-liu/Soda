#include "student.h"
#include "MPRNG.h"

extern MPRNG rdm;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff, unsigned int id, unsigned int maxPurchases ) : _printer(prt), _nameServer(nameServer), _cardOffice(cardOffice), _groupoff(groupoff), _id(id), _maxPurchases(maxPurchases) {}

void Student::main() {
	// selecting random number of bottles to purchase
	unsigned int purchase = rdm(1,_maxPurchases);
	unsigned int flavour = rdm(3);
	unsigned int currPurchase = 0;
	_printer.print(Printer::Kind::Student, _id, 'S', flavour, purchase);
	// create watCard with $5 balance and a gift card
	WATCard *watCard = NULL;
	WATCard *giftCard = NULL;
    WATCard::FWATCard fWatCard = _cardOffice.create(_id, 5);
    WATCard::FWATCard fGiftCard = _groupoff.giftCard();
	bool giftCardUsed = false;
	VendingMachine* vMachine = _nameServer.getMachine(_id);
	_printer.print(Printer::Kind::Student, _id, 'V', vMachine->getId());

	for (;;) {
		if (currPurchase == purchase) {
			break;
		}
		try {
			_Select(fWatCard) {
				watCard = fWatCard();
				// yield
				yield(rdm(1,10));
				vMachine->buy(static_cast<VendingMachine::Flavours>(flavour), *watCard);
				_printer.print(Printer::Kind::Student, _id, 'B', watCard->getBalance());
			} or _Select(fGiftCard) {
				giftCard = fGiftCard();
				// yield
				yield(rdm(1,10));
				vMachine->buy(static_cast<VendingMachine::Flavours>(flavour), *giftCard); 
				_printer.print(Printer::Kind::Student, _id, 'G', giftCard->getBalance());
				giftCardUsed = true;
				fGiftCard.reset();
				delete giftCard;
			}
			currPurchase++;
		} catch (WATCardOffice::Lost &e) {
			_printer.print(Printer::Kind::Student, _id, 'L');
			fWatCard.reset();
			fWatCard = _cardOffice.create(_id, 5);
		} catch (VendingMachine::Funds &e) {
			fWatCard = _cardOffice.transfer(_id, 5 + vMachine->cost(), watCard);
		} catch (VendingMachine::Stock &e) {
			vMachine = _nameServer.getMachine(_id);
			_printer.print(Printer::Kind::Student, _id, 'V', vMachine->getId());
		}
	}
	_printer.print(Printer::Kind::Student, _id, 'F');

	if (!giftCardUsed) {
		delete fGiftCard();
	}
	try{
       delete fWatCard();
    } catch (WATCardOffice::Lost &e){
		//dont need to do anything if lost
    }
}
