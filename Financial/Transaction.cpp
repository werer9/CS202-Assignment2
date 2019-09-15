#include "Transaction.hpp"
#include <string>

int Transaction::ID = 0;

Transaction::Transaction(Account* fromAccount, Account* toAccount, Money amount) {
	// set member to and from accounts
	this->fromAccount = fromAccount;
	this->toAccount = toAccount;

	// make sure amount isn't negative
	if (amount.asCents() < 0)
		// set amount to zero if amount is negative
		this->amount = Money(0, 0);
	else 
		// set member amount variable
		this->amount = amount;

	// create next transaction id
	this->transactionID = ++ID;
	// initiate instance as a pending transaction
	this->state = PENDING;
}

bool Transaction::compById(const Transaction *trans1, const Transaction *trans2) {
	return trans1->getID() < trans2->getID();
}

bool Transaction::performTransaction(){
	// make sure withdrawal from from account and deposit to to account is successful
	if (this->fromAccount->withdrawMoney(this->amount)) {
		if (this->toAccount->depositMoney(this->amount)) {
			// if successful mark state as completed and return true
			this->state = COMPLETED;
			return true;
		} else {
			// otherwise, make sure from account is same as before 
			this->fromAccount->returnMoney(this->amount);
			// state is failed and return false
			this->state = FAILED;
			return false;
		}
	} else {
		this->state = FAILED;
		return false;
	}
}

TransactionState Transaction::getState() const {
	return this->state;
}

Money Transaction::getAmount() const {
	return this->amount;
}

Account* Transaction::getToAccount() const {
	return this->toAccount;
}

Account* Transaction::getFromAccount() const {
	return this->fromAccount;
}

int Transaction::getID() const {
	return this->transactionID;
}

int Transaction::getHighestID()  {
	return Transaction::ID;
}

Transaction::~Transaction() {
	
}

