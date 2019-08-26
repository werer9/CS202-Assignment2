#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount(const int customerID) : Account(customerID), depositCount(0), bonusAmount(10, 0) {
}

bool SavingsAccount::withdrawMoney(Money amount) {
	if (amount.asCents() > this->balance->asCents()) {
		return false;
	} else {
		this->balance->subtract(amount);
		if (this->bonusAmount.asCents() >= 200) {
			this->bonusAmount.subtractDollars(2);
		}
		return true;
	}
	return false;
}

bool SavingsAccount::depositMoney(Money amount) {
	if (amount.asCents() < 0) {
		return false;
	}
	++(this->depositCount);
	if (this->depositCount < 2) {	
		this->balance->add(amount);
		return true;
	} else if (this->depositCount == 2) {
		this->balance->add(amount);
		this->balance->add(this->bonusAmount);
		this->depositCount = 0;
		return true;
	} else {
		return false;
	}

	return false;
}

Money SavingsAccount::getBonusValue() const {
	return this->bonusAmount;
}

SavingsAccount::~SavingsAccount() {
	// TODO implement
}


