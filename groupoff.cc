#include "groupoff.h"
#include "MPRNG.h"

MPRNG rdm;

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : _printer(prt), _numStudents(numStudents), _sodaCost(sodaCost), _groupoffDelay(groupoffDelay) {}

void Groupoff::main() {
	int count = 0;
	for(;;) {
		if (count == _numStudents) break;
		_Accept(giftCard) {
			count++;
		}
	}
	for(;;) {
		_Accept(~Groupoff) {
			break;
		} _Else {
			if (_cards.empty()) break;
			yield(_groupoffDelay);
			WatCard* giftCard = new WATCard();
			giftCard->deposit(_sodaCost);
			unsigned randomIndex = rdm(_cards.size()-1);
			_cards[randomIndex].delivery(giftCard);		
			_cards.erase(_cards.begin+randomIndex);
		}
	}
}

WATCard::FWATCard Groupoff::giftCard() {
	WATCard::FWATCard card;
	_cards.push_back(card);
	return card;
}
