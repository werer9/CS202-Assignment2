#ifndef ACCOUNT_HPP_
#define ACCOUNT_HPP_
#include "Money.hpp"
class Account{
protected:
	// protected member variables
	int customerID;
	int accountID;
	static int ID;
	Money *balance;

private:
	// private methods
	Account& operator=(const Account &other);
	Account(const Account &other);
public:
	// public methods

	// constructor, creat account with customer id
	Account(const int customerID);
	// take balance from account, abstract method
	virtual bool withdrawMoney(Money amount) = 0;
	// insert balance into account, abstract method
	virtual bool depositMoney(Money amount) = 0;
	// return accounts customer id
	int getCustomerID() const;
	// return account id
	int getAccountID() const;
	// get account balance
	Money getBalance() const;

	virtual bool returnMoney(Money amount);
	// destructor
	virtual ~Account();
};

#endif /* ACCOUNT_HPP_ */
