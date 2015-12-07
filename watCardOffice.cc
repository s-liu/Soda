#include "watCardOffice.h"
#include "MPRNG.h"

extern MPRNG rdm;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : _printer(prt), _bank(bank), _numCouriers(numCouriers), _courier_arr(NULL) {
	_courier_arr = new Courier* [numCouriers];
	for (unsigned int i = 0; i < _numCouriers; i++) {
		_courier_arr[i] = new Courier(this, &_bank, i);
	}
}

WATCardOffice::~WATCardOffice() {
	for (unsigned int i = 0; i < _numCouriers; i++) {
		delete _courier_arr[i];
	}
	delete [] _courier_arr;
}
	
		
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	Args a (sid, amount, new WATCard());
	Job* job  = new Job(a);
	_job_list.push(job);
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
	Args a (sid, amount, card);
	Job* job  = new Job(a);
	_job_list.push(job);
	return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	if (_job_list.empty()) return NULL;
	Job* job = _job_list.front();
    _job_list.pop();
    return job;
}

void WATCardOffice::main() {
	_printer.print(Printer::Kind::WATCardOffice, 'S');
	for (;;) {
		_Accept( ~WATCardOffice ) {
			for (unsigned int i = 0; i < _numCouriers; i++ ) {
				_Accept(requestWork);
			}
			break;
		} or _When(!_job_list.empty()) _Accept(requestWork) {
			_printer.print(Printer::Kind::WATCardOffice, 'W');
		} or _Accept( create ) {
			_printer.print(Printer::Kind::WATCardOffice, _job_list.back()->args.sid, 'C', _job_list.back()->args.amount);
		} or _Accept( transfer ) {
			_printer.print(Printer::Kind::WATCardOffice, _job_list.back()->args.sid, 'T', _job_list.back()->args.amount);
		}
	}
	_printer.print(Printer::Kind::WATCardOffice, 'F');
}

void WATCardOffice::Courier::main() {
	_office->_printer.print(Printer::Kind::Courier, _id, 'S');
	for (;;) {
		_Accept( ~Courier ) {
			break;
		} _Else {
			Job* job = _office->requestWork();
			if (job == NULL) break;
			Args a = job->args;
			_office->_printer.print(Printer::Kind::Courier, _id, 't', a.sid, a.amount);
			_bank->withdraw(a.sid, a.amount);
			a.card->deposit(a.amount);
			_office->_printer.print(Printer::Kind::Courier, _id, 'T', a.sid, a.amount);
			if (rdm(1,6)==1) {
				delete a.card;
				job->result.exception(new Lost());
			} else {
				job->result.delivery(a.card);
			}
			delete job;
		}
	}
	_office->_printer.print(Printer::Kind::Courier, _id, 'F');
}
