#include "Account.hpp"

#ifndef CHEQUEACCOUNT_HPP_
#define CHEQUEACCOUNT_HPP_

class ChequeAccount : public Account {

private:
	// private member variables
	Money *transactionFee;

	// private methods
	ChequeAccount& operator=(const ChequeAccount &other);
    ChequeAccount(const ChequeAccount &other);
public:
	// public methods

	// constructor
	ChequeAccount(const int customerID);
	// implement withdraw
	bool withdrawMoney(Money amount);
	// implement deposit
	bool depositMoney(Money amount);
	// return tranesaction fee for account
	Money* getTransactionFee() const;
	// destructor
	virtual ~ChequeAccount();
};

#endif /* CHEQUEACCOUNT_HPP_ */
