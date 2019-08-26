#include "Account.hpp"

#ifndef SAVINGSACCOUNT_HPP_
#define SAVINGSACCOUNT_HPP_

class SavingsAccount : public Account {
private:
	// private member variables
	int depositCount;
	Money bonusAmount;

	// private methods
	SavingsAccount& operator=(const SavingsAccount &other);
    SavingsAccount(const SavingsAccount &other);
public:
	// public methods

	// constructor
	SavingsAccount(const int customerID);
	// implement withdraw
	bool withdrawMoney(Money amount);
	// implement deposit
	bool depositMoney(Money amount);
	// return bonus savings value
	Money getBonusValue() const;
	// destructor
	virtual ~SavingsAccount();
};

#endif /* SAVINGSACCOUNT_HPP_ */
