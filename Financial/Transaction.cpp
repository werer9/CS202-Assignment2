#include "Transaction.hpp"
#include <string>

int Transaction::ID = 0;

Transaction::Transaction(Account* fromAccount, Account* toAccount, Money amount) {
	
	this->fromAccount = fromAccount;
	this->toAccount = toAccount;

	if (amount.asCents() < 0)
		this->amount = Money(0, 0);
	else 
		this->amount = amount;

	this->transactionID = ++ID;
	this->state = PENDING;
}

bool Transaction::performTransaction(){
	if (this->fromAccount->withdrawMoney(this->amount)) {
		if (this->toAccount->depositMoney(this->amount)) {
			this->state = COMPLETED;
			return true;
		} else {
			this->fromAccount->depositMoney(this->amount);
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

bool Transaction::operator<(const Transaction &other) const {
	return this->getID() < other.getID();
}

Transaction::~Transaction() {
	delete toAccount;
	delete fromAccount;
}

