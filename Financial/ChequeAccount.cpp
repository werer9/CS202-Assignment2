#include "ChequeAccount.hpp"

// assign account to customer and initialise transaction fee at $1
ChequeAccount::ChequeAccount(const int customerID) : Account(customerID) {
	this->transactionFee = new Money(1, 0);
}

bool ChequeAccount::withdrawMoney(Money amount) {
	// increase withdrawl by transaction fee as penalty
	amount.add(*transactionFee);
	if (amount.asCents() > this->balance->asCents()) {
		// fail withdrawl if withdrawl will cause balance to become negative
		return false;
	} else {
		// otherwise subtract amount from balance and increease 
		// transaction fee by $1
		this->balance->subtract(amount);
		this->transactionFee->addDollars(1);
		return true;
	}
	
	return false;
}

bool ChequeAccount::depositMoney(Money amount) {
	// check that deposit not larger than $3000
	if (amount.asCents() < 0 || amount.asCents() > 3000*100) {
		// fail deposit if amount exceeds $3000
		return false;
	} else {
		// otherwise add amount to balance and complete deposit
		this->balance->add(amount);
		return true;
	}

	return false;
}

Money* ChequeAccount::getTransactionFee() const {
	return transactionFee;
}

ChequeAccount::~ChequeAccount() {
	// delete objects on heap
	delete transactionFee;
}

