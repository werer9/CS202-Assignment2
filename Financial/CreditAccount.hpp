#include "Account.hpp"

#ifndef CREDITACCOUNT_HPP_
#define CREDITACCOUNT_HPP_

class CreditAccount : public Account {

private:
	// private methods
	CreditAccount& operator=(const CreditAccount &other);
    CreditAccount(const CreditAccount &other);
public:
	// public methods

	// constructor
	CreditAccount(const int customerID);
	// implement withdraw
	bool withdrawMoney(Money amount);
	// implement deposit
	bool depositMoney(Money amount);
	// destructor
	virtual ~CreditAccount();
};

#endif /* CREDITACCOUNT_HPP_ */
