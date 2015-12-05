#include "watCardOffice.h"
#include "MPRNG.h"

MPRNG rdm;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : _printer(prt), _bank(bank), _numCouriers(numCouriers), _courier_arr(NULL) {
	Courier* arr [numCouriers];
	_courier_arr = arr;
	for (unsigned int i = 0; i < numCouriers; i++) {
		_courier_arr[i] = new Courier();
	}
}

WATCardOffice::~WATCardOffice() {
	for (unsigned int i = 0; i < numCouriers; i++) {
		delete _courier_arr[i];
	}
	delete [] _courier_arr;
}
	
		
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	Args a (sid, amount, new WATCard());
	Job job (a);
	_job_list.push(a);
	return job.result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
	Args a (sid, amount, card);
	Job job (a);
	_job_list.push(a);
	return job.result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
	return &_job_list.pop();
}

WATCardOffice::main() {
	for (;;) {
		_Accept( ~WATCardOffice ) {
			break;
		} or _When(!_job_list.empty()) _Accept(requestWork) {
		} or _Accept( create, transfer ) {
		}
	}
}

Courier::main() {
	for (;;) {
		Job* job = requestWork();
		if (rdm(1,6)==1) job->result.exception(new Lost());
		Args a = job->args;
		bank.withdraw(a.sid, a.amount);
		a.card->deposit(a.amount);
		job->result.delivery(a.card);
	}
}
