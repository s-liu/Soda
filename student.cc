#include "student.h"
#include "MPRNG.h"

MPRNG rdm;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff, unsigned int id, unsigned int maxPurchases ) : _printer(prt), _nameServer(nameServer), _cardOffice(cardOffice), _groupoff(groupoff), _id(id), _maxPurchases(maxPurchases) {}

void Student::main() {
	// selecting random number of bottles to purchase
	unsigned int purchase = rdm(1,_maxPurchases);
	unsigned int flavour = rdm(3);
	unsigned int currPurchase = 0;
	// create watCard with $5 balance and a gift card
	WATCard *watCard = NULL;
	WATCard *giftCard = NULL;
	FWATCard fWatCard = _cardOffice.create(_id, 5);
	FWATCard fGiftCard = _groupoff.giftCard();
	VendingMachine* vMachine = _nameServer.getMachine(_id);


	for (;;) {
		if (currPurchase == purchase) break;
		try {
			_Select(fWatCard) {
				watCard = fWatCard();
				// yield
				yield(rdm(1,10));
				vMachine.buy(flavour, watCard);
			} or _Select(fGiftCard) {
				giftCard = fGiftCard();
				// yield
				yield(rdm(1,10));
				vMachine.buy(flavour, giftCard); 
				fGiftCard.reset();
			}
			currPurchase++;
		} catch (WATCardOffice::Lost &e) {
			fWatCard.reset();
			fWatCard = _cardOffice.create(_id, 5);
		} catch (VendingMachine::Funds &e) {
			_cardOffice.transfer(_id, 5 + vMachine->cost(), watCard);
		} catch (VendingMachine::Stock &e) {
			vMachine = _nameServer.getMachine(_id);
		}
	}
}
