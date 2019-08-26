#include "Account.hpp"

// set static ID variable to 0 initially
int Account::ID = 0;

// constructor, creat account with customer id
Account::Account(const int customerID) {
	// set account customer id to parameter
	this->customerID = customerID;
	// set next unique customer id
	this->accountID = ++ID;
	// set balance of account to $0.00
	this->balance = new Money(0, 0);
}

// return account id
int Account::getAccountID() const {
	return this->accountID;
}

// return accounts customer id
int Account::getCustomerID() const {
	return this->customerID;
}

// return account balance
Money Account::getBalance() const {
	return *(this->balance);
}

Account::~Account() {
	// TODO implement
}

