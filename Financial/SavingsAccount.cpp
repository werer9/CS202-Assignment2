#include "SavingsAccount.hpp"

SavingsAccount::SavingsAccount(const int customerID) : Account(customerID), depositCount(0), bonusAmount(10, 0) {
}

bool SavingsAccount::withdrawMoney(Money amount) {
	// check withdraw amount is greater than 0
	if (amount.asCents() < 0)
		return false;
	
	// get amount in cents is not more than balance
	if (amount.asCents() > this->balance->asCents()) {
		return false;
	} else {
		// subtract amount from balance
		this->balance->subtract(amount);
		// subtract bonus amount by 2 if it isn't zero
		if (this->bonusAmount.asCents() >= 200) {
			this->bonusAmount.subtractDollars(2);
		}
		return true;
	}
	return false;
}



bool SavingsAccount::depositMoney(Money amount) {
	// check deposit amount is greater than 0
	if (amount.asCents() < 0)
		return false;

	// // make sure amount isn't zero
	// if (amount.asCents() < 0) {
	// 	return false;
	// }
	// increase the number of deposits
	++(this->depositCount);
	// if less thant two deposits just add amount to balance
	if (this->depositCount < 2) {	
		this->balance->add(amount);
		return true;
	} else if (this->depositCount == 2) {
		// otherwise add bonus amount two and reset deposit count to zero
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

bool SavingsAccount::returnMoney(Money amount) {
	Account::returnMoney(amount);
	this->bonusAmount.addDollars(2);
	return true;
}

SavingsAccount::~SavingsAccount() {
	// TODO implement
}


