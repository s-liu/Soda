#include "vendingMachine.h"
#include "watCard.cc"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : _printer(prt), _id(id), _sodaCost(sodaCost), _maxStockPerFlavour(maxStockPerFlavour), _exception_flag(0) {
	int inv [4];
	_inventory = inv;
	for (unsigned int i = 0; i < 4; i++) {
		_inventory[i] = 0;
	}
}

void VendingMachine::buy( VendingMachine::Flavours flavour, WATCard &card ) {
	/*if (_inventory[flavour] == 0) {
		_Throw Stock();
	}
	if (card.getBalance() < _sodaCost) {
		_Throw Funds();
	}
	card.withdraw(sodaCost );
	_inventory[flavour] --;*/
	_currFlavour = flavour;
	_currCard = card;
	_lock.wait();
	if (_exception_flag == 1) {
		_exception_flag = 0;
		_Throw Stock();
	} else if (_exception_flag == 2) {
		_exception_flag = 0;
		_Throw Funds();
	}

}

unsigned int* VendingMachine::inventory() {
	return _inventory;
}

void VendingMachine::restocked() {
}

_Nomutex unsigned int cost() {
	return _sodaCost;
}

_Nomutex unsigned int getId() {
	return _id;
}

void VendingMachine::main() {
	nameServer.VMregister(&this);
	for (;;) {
		_Accept(~VendingMachine) {
			break;
		} or _Accept(inventory) {
			_Accept(restocked);
		} or _Accept(buy) {
			if (_inventory[_currFlavour] == 0) {
				_exception_flag = 1;
			} else if (_currCard.getBalance() < _sodaCost) {
				_exception_flag = 2;
			} else {
				_currCard.withdraw(_sodaCost);
				_inventory[_currFlavour] --;
			}
			_lock.signalBlock();
		}
	}
}
