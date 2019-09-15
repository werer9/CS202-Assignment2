#ifndef FINANCIALSERVICESSYSTEM_HPP_
#define FINANCIALSERVICESSYSTEM_HPP_


#include "Customer.hpp"
#include "Account.hpp"
#include "Transaction.hpp"
#include "Money.hpp"
#include <vector>
#include <iostream>


class FinancialServicesSystem {

private:
	// private member variables
	std::vector<Account*> accounts;
	std::vector<Customer*> customers;
	std::vector<Transaction*> transactions;

	// private methods

	// find index of customer in customers vector 
	int getCustomerIndex(int ID) const;
	// find index of account in accounts vector
	int getAccountIndex(int ID) const;
	// find index tranaction in transactions vector
	int getTransactionIndex(int ID) const;
	// return accounts that belong to customer
	std::vector<Account*> getCustomerAccounts(int ID) const;
	// get transactions of specified statei
	std::vector<Transaction*> getTransactionByState(TransactionState state) const;

public:
	// public methods

	// constructor
	FinancialServicesSystem();
	// return my UPI
	static std::string author();
	
	// add customer to fss
	bool addCustomer(Customer* customer);
	// add account to fss if it belongs to customer
	bool addAccount(Account* account);
	// add transaction to fss if it belongs to account
	bool addTransaction(Transaction* transaction);

	// perform all transactions that are pending
	// return all transactions that were completed
	std::vector<Transaction*> performPendingTransactions();
	// return specified customer balance
	Money getCustomerBalance(int customerID) const;
	
	// check if customer is already in system
	bool verifyCustomer(int customerID) const;
	// check if account is already in system
	bool verifyAccount(int accountID) const;
	// check if transaction is already in system
	bool verifyTransaction(int transactionID) const;

	// return accounts stored in fss
	std::vector<Account*> getAccounts() const;
	// return customers stored in fss
	std::vector<Customer*> getCustomers() const;
	// return transactions stored in fss
	std::vector<Transaction*> getTransactions() const;
	// return transactions of specified state stored in fss
	std::vector<Transaction*> getTransactions(TransactionState state) const;

	// destructor
	virtual ~FinancialServicesSystem();
};

#endif /* FINANCIALSERVICESSYSTEM_HPP_ */
