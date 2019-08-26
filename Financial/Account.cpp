#include "Account.hpp"

int Account::ID = 0;

Account::Account(const int customerID) {
	this->customerID = customerID;
	this->accountID = ++ID;
	this->balance = new Money(0, 0);
}

int Account::getAccountID() const {
	return this->accountID;
}

int Account::getCustomerID() const {
	return this->customerID;
}

Money Account::getBalance() const {
	return *(this->balance);
}

Account::~Account() {
	// TODO implement
}

