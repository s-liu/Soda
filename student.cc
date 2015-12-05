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
	FWATCard fWatCard = _cardOffice.create(_id, 5);
	FWATCard fGiftCard = _groupoff.giftCard();
	VendingMachine* vMachine = _nameServer.getMachine(_id);

	// yield
	yield(rdm(1,10));

	for (;;) {
		if (currPurchase == purchase) break;
		try {
			_Select(fWatCard) {
				watCard = fWatCard();
				vMachine.buy(flavour, watCard);
			} or _Select(fGiftCard) {
				vMachine.buy(flavour, *fGiftCard());
				fGiftCard.reset();
			}
			currPurchase++;
		} catch (WATCardOffice::Lost) {
			fWatCard = _cardOffice.create(_id, 5);
		} catch (VendingMachine::Funds) {
			_cardOffice.transfer(_id, 5 + vMachine->cost(), watCard);
		} catch (VendingMachine::Stock) {
			vMachine = _nameServer.getMachine(_id);
		}
	}
}
