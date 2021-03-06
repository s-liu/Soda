#include "groupoff.h"
#include "watCard.h"
#include "MPRNG.h"

extern MPRNG rdm;

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) : _printer(prt), _numStudents(numStudents), _sodaCost(sodaCost), _groupoffDelay(groupoffDelay) {}

void Groupoff::main() {
    // Start
    _printer.print(Printer::Kind::Groupoff, 'S');

	unsigned int count = 0;
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
			WATCard* giftCard = new WATCard();
			giftCard->deposit(_sodaCost);

            // Deposit to gift card
            _printer.print(Printer::Kind::Groupoff, 'D', (int)_sodaCost);
			unsigned randomIndex = rdm(_cards.size()-1);
			_cards[randomIndex].delivery(giftCard);		
			_cards.erase(_cards.begin()+randomIndex);
		}
	}

    // End
    _printer.print(Printer::Kind::Groupoff, 'F');
}

WATCard::FWATCard Groupoff::giftCard() {
	WATCard::FWATCard card;
	_cards.push_back(card);
	return card;
}
