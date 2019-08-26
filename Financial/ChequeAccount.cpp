#include "ChequeAccount.hpp"
//TODO Implement ChequeAccount class

ChequeAccount::ChequeAccount(const int customerID) : Account(customerID) {
	this->transactionFee = new Money(1, 0);
}

bool ChequeAccount::withdrawMoney(Money amount) {
	amount.add(*transactionFee);
	if (amount.asCents() > this->balance->asCents()) {
		return false;
	} else {
		this->balance->subtract(amount);
		this->transactionFee->addDollars(1);
		return true;
	}
	
	return false;
}

bool ChequeAccount::depositMoney(Money amount) {
	if (amount.asCents() < 0 || amount.asCents() > 3000*100) {
		return false;
	} else {
		this->balance->add(amount);
		return true;
	}

	return false;
}

Money* ChequeAccount::getTransactionFee() const {
	return transactionFee;
}

ChequeAccount::~ChequeAccount() {
	delete transactionFee;
}

