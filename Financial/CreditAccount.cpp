#include "CreditAccount.hpp"

// assign account's customer id
CreditAccount::CreditAccount(const int customerID) : Account(customerID) {
	
}

bool CreditAccount::withdrawMoney(Money amount) {
	// check amount is not negative
	if (amount.asCents() < 0) {
		// fail withdraw if negative amount
		return false;
	} else {
		// otherwise complete withdrawl and subtract amount
		// from balance
		this->balance->subtract(amount);
		return true;
	}

	return false;
}

bool CreditAccount::depositMoney(Money amount) {
	// make sure deposit will not cause account to exceed balance of $5000
	if (amount.asCents() + this->balance->asCents() > 5000 * 100) {
		// fail deposit if it exceeds account limit
		return false;
	} else {
		// otherwise add new amount to account and return true
		this->balance->add(amount);
		return true;
	}
	
	return false;
}

CreditAccount::~CreditAccount() {
	
}
