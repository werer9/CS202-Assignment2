#ifndef TRANSACTION_HPP_
#define TRANSACTION_HPP_

#include <string>
#include "Account.hpp"
#include "Money.hpp"

// transaction states enumeration
enum TransactionState {
	COMPLETED,
	PENDING,
	FAILED
};

class Transaction {
	
private:
	// private member variables
	Account *fromAccount;
	Account *toAccount;

	Money amount;

	TransactionState state;

	int transactionID;
	static int ID;
	
	// private methods
	Transaction& operator=(const Transaction &other);
    Transaction(const Transaction &other);

public:
	// public methods

	// constructor
	Transaction(Account* fromAccount, Account* toAccount, Money amount);
	// perform transaction if pending, return true if successful
	bool performTransaction();
	// return transaction state
	TransactionState getState() const;
	// return transaction amount
	Money getAmount() const;
	// return from account
	Account* getFromAccount() const;
	// return to account
	Account* getToAccount() const;
	// return transaciton id
	int getID() const;
	// return highest id created so far
	// static method/non-instance method
	static int getHighestID();
	// implement < operator for std::sort
	// compares two transaction ids
	bool operator<(const Transaction &other) const;
	// destructor
	virtual ~Transaction();
};

#endif /* TRANSACTION_HPP_ */
