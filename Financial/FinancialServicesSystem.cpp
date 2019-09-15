#include "FinancialServicesSystem.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

FinancialServicesSystem::FinancialServicesSystem() {}

// find index of customer in customers vector 
int FinancialServicesSystem::getCustomerIndex(int ID) const {
	// iterate over customer vector 
	for (unsigned int i = 0; i < this->customers.size(); i++) {
		if (this->customers[i]->getID() == ID) {
			// return index if customer found
			return i;
		}
	}

	// return -1 if customer not found
	return -1;
}

// find index of account in accounts vector
int FinancialServicesSystem::getAccountIndex(int ID) const {
	// iterate over account vector
	for (unsigned int i = 0; i < this->accounts.size(); i++) {
		if (this->accounts[i]->getAccountID() == ID) {
			// return index if account found
			return i;
		}
	}

	// return -1 if account not found
	return -1;
}

// get accounts that belong to customer
std::vector<Account*> FinancialServicesSystem::getCustomerAccounts(int ID) const {
	// vector to be returned
	std::vector<Account*> customerAccounts;
	// iterate over accounts
	for (unsigned int i = 0; i < this->accounts.size(); i++) {
		if (this->accounts[i]->getCustomerID() == ID) {
			// add acount to vector if it belongs to customer
			customerAccounts.push_back(this->accounts[i]);
		}
	}

	return customerAccounts;
}

// get index of transaction 
int FinancialServicesSystem::getTransactionIndex(int ID) const {
	// iterate over transactions vector
	for (unsigned int i = 0; i < this->transactions.size(); i++) {
		if (this->transactions[i]->getID() == ID) {
			// return index if found
			return i;
		}
	}

	// return -1 if not found
	return -1;
}

// return transactions of specified state
std::vector<Transaction*> FinancialServicesSystem::getTransactionByState(TransactionState state) const {
	// vector to be returned
	std::vector<Transaction*> transactions;

	// iterate over transactions
	for (unsigned int i = 0; i < this->transactions.size(); i++) {
		if (this->transactions[i]->getState() == state) {
			// add transation to return vector if it has correct state
			transactions.push_back(this->transactions[i]);
		}
	}

	return transactions;
}

std::string FinancialServicesSystem::author(){
	// return my UPI: cmur196
	return "cmur196";
}

// add customer to fss if they aren't already added
bool FinancialServicesSystem::addCustomer(Customer* customer) {
	// make sure customer isn't already added
	if (!this->verifyCustomer(customer->getID())) {
		// add customer, return true
		this->customers.push_back(customer);
		return true;
	} else {
		// do nothing, return false
		return false;
	}
}

// add account if it hasn't been added
bool FinancialServicesSystem::addAccount(Account* account) {
	// make sure account isn't already added
	if (!this->verifyAccount(account->getAccountID())) {
		// add acount if customer is added, return true
		if (verifyCustomer(account->getCustomerID())) {
			this->accounts.push_back(account);
			return true;
		}
	} else {
		return false;
	}

	return false;
}

bool FinancialServicesSystem::addTransaction(Transaction* transaction) {
	// check transaction hasn't been added already
	if (!this->verifyTransaction(transaction->getID())) {
		// check that to account is added
		if (this->verifyAccount(transaction->getFromAccount()->getAccountID())) {
			// check that from account is added
			if (this->verifyAccount(transaction->getToAccount()->getAccountID())) {
				// add transaction to transactions & return true
				this->transactions.push_back(transaction);
				return true;
			}
		}
	} else {
		return false;
	}

	return false;
}

std::vector<Transaction*> FinancialServicesSystem::performPendingTransactions() {
	// return vector
	std::vector<Transaction*> transactionsCompleted;

	// use stdlib sort algorithm
	std::sort(this->transactions.begin(), this->transactions.end(), Transaction::compById);
	// iterate over ordered transactions
	for (unsigned int i = 0; i < (unsigned int)this->transactions.size(); i++) {
		// check transaction is pending
		if (this->transactions[i]->getState() == TransactionState::PENDING) {
			// perform transaction
			if (this->transactions[i]->performTransaction()) {
				// check if transaction successful
				if (this->transactions[i]->getState() == TransactionState::COMPLETED) {
					// added completed transaction to return vector
					transactionsCompleted.push_back(this->transactions[i]);
				}
			} 
		}
	}

	return transactionsCompleted;
}

Money FinancialServicesSystem::getCustomerBalance(int customerID) const {
	// retrieve customer
	Customer *customer = this->customers[getCustomerIndex(customerID)];
	// retireve customer accounts
	std::vector<Account*> accounts = getCustomerAccounts(customer->getID());
	// if customer has no accounts return 0 balance
	if (accounts.size() == 0) {
		return Money(0, 0);
	} else {
		// added total amount from all acounts to return
		Money amount(0, 0);
		for (unsigned int i = 0; i < accounts.size(); i++) {
			if (accounts[i]->getBalance().asCents() >= 0) 
				amount.add(accounts[i]->getBalance());
			else 
				amount.subtractCents(accounts[i]->getBalance().asCents()*-1);
		}
		return amount;
	}
}

bool FinancialServicesSystem::verifyCustomer(int customerID) const {
	// check customer can be found in customers vector
	if (this->getCustomerIndex(customerID) != -1) {
		return true;
	} else {
		return false;
	}

}

bool FinancialServicesSystem::verifyAccount(int accountID) const {
	// check account can be found in accounts vector
	if (this->getAccountIndex(accountID) != -1) {
		return true;
	} else {
		return false;
	}
}

bool FinancialServicesSystem::verifyTransaction(int transactionID) const {
	// check transaction can be found in transactions vector
	if (this->getTransactionIndex(transactionID) != -1) {
		return true;
	} else {
		return false;
	}
}

std::vector<Account*> FinancialServicesSystem::getAccounts() const {
	return accounts;
}

std::vector<Customer*> FinancialServicesSystem::getCustomers() const {
	return customers;
}

std::vector<Transaction*> FinancialServicesSystem::getTransactions() const {
	return transactions;
}

std::vector<Transaction*> FinancialServicesSystem::getTransactions(TransactionState state) const {
	return getTransactionByState(state);
}

FinancialServicesSystem::~FinancialServicesSystem() {
	
}

