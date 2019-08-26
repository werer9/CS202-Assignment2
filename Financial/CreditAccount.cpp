#include "CreditAccount.hpp"
//TODO Implement CreditAccount class

CreditAccount::CreditAccount(const int customerID) : Account(customerID) {
	
}

bool CreditAccount::withdrawMoney(Money amount) {
	if (amount.asCents() < 0) {
		return false;
	} else {
		this->balance->subtract(amount);
		return true;
	}

	return false;
}

bool CreditAccount::depositMoney(Money amount) {
	if (amount.asCents() + this->balance->asCents() > 5000 * 100) {
		return false;
	} else {
		this->balance->add(amount);
		return true;
	}
	
	return false;
}

CreditAccount::~CreditAccount() {
	// TODO implement
}
