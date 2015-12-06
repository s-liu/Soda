#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) : _printer(prt), _nameServer(nameServer), _id(id), _sodaCost(sodaCost), _maxStockPerFlavour(maxStockPerFlavour), _exception_flag(0) {
	unsigned int inv [4];
	_inventory = inv;
	for (unsigned int i = 0; i < 4; i++) {
		_inventory[i] = 0;
	}
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
	_printer.print(Printer::Kind::Vending, _id, 'S', _sodaCost);
	_nameServer.VMregister(this);
	for (;;) {
		cout << "vm1" << endl;
        _Accept(~VendingMachine) {
		    cout << "vm2" << endl;
			_printer.print(Printer::Kind::Vending, _id, 'F');
			break;
		} or _Accept(inventory) {
		    cout << "vm3" << endl;
			_printer.print(Printer::Kind::Vending, _id, 'r');
			_Accept(restocked) {
				_printer.print(Printer::Kind::Vending, _id, 'R');
			}
		} or _Accept(buy) {
		    cout << "vm4" << endl;
			if (_inventory[_currFlavour] == 0) {
				
		cout << "vm1" << endl;
                _exception_flag = 1;
			} else if (_currCard->getBalance() < _sodaCost) {
			
		cout << "vm1" << endl;
                _exception_flag = 2;
			} else {
				
		cout << "vm1" << endl;
                _currCard->withdraw(_sodaCost);
		
		cout << "vm1" << endl;
                _inventory[_currFlavour] --;
				
		cout << "vm1" << endl;
                _printer.print(Printer::Kind::Vending, _id, 'B', _currFlavour, _inventory[_currFlavour]);
			}
			
		cout << "vm1" << endl;
            _lock.signalBlock();
		}
	}
}

