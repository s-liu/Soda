#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : _printer(prt), _nameServer(nameServer), _id(id), _sodaCost(sodaCost), _maxStockPerFlavour(maxStockPerFlavour), _exception_flag(0) {
	_inventory = new unsigned int [4];
	for (unsigned int i = 0; i < 4; i++) {
		_inventory[i] = 0;
	}
}

VendingMachine::~VendingMachine() {
	delete [] _inventory;
}

void VendingMachine::buy( VendingMachine::Flavours flavour, WATCard &card ) {
	_currFlavour = flavour;
	_currCard = &card;
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

_Nomutex unsigned int VendingMachine::cost() {
	return _sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
	return _id;
}

void VendingMachine::main() {
	_nameServer.VMregister(this);
	_printer.print(Printer::Kind::Vending, _id, 'S', _sodaCost);
    for (;;) {
        _Accept(~VendingMachine) {
			break;
		} or _Accept(inventory) {
			_printer.print(Printer::Kind::Vending, _id, 'r');
			_Accept(restocked) {
				_printer.print(Printer::Kind::Vending, _id, 'R');
			}
		} or _Accept(buy) {
			if (_inventory[_currFlavour] == 0) {
                _exception_flag = 1;
			} else if (_currCard->getBalance() < _sodaCost) {
                _exception_flag = 2;
			} else {
                _currCard->withdraw(_sodaCost);
                _inventory[_currFlavour] --;
                _printer.print(Printer::Kind::Vending, _id, 'B', _currFlavour, _inventory[_currFlavour]);
			}
			
            _lock.signalBlock();
		}
	}
	_printer.print(Printer::Kind::Vending, _id, 'F');
}

