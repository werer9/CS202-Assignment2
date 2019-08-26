#include "FinancialServicesSystem.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

FinancialServicesSystem::FinancialServicesSystem() {}

int FinancialServicesSystem::getCustomerIndex(int ID) const {
	
	for (unsigned int i = 0; i < this->customers.size(); i++) {
		if (this->customers[i]->getID() == ID) {
			return i;
		}
	}

	return -1;
}

int FinancialServicesSystem::getAccountIndex(int ID) const {
	for (unsigned int i = 0; i < this->accounts.size(); i++) {
		if (this->accounts[i]->getAccountID() == ID) {
			return i;
		}
	}

	return -1;
}
std::vector<Account*> FinancialServicesSystem::getCustomerAccounts(int ID) const {
	std::vector<Account*> customerAccounts;
	for (unsigned int i = 0; i < this->accounts.size(); i++) {
		if (this->accounts[i]->getCustomerID() == ID) {
			customerAccounts.push_back(this->accounts[i]);
		}
	}

	return customerAccounts;
}

int FinancialServicesSystem::getTransactionIndex(int ID) const {
	for (unsigned int i = 0; i < this->transactions.size(); i++) {
		if (this->transactions[i]->getID() == ID) {
			return i;
		}
	}

	return -1;
}

std::vector<Transaction*> FinancialServicesSystem::getTransactionByState(TransactionState state) const {
	std::vector<Transaction*> transactions;
	for (unsigned int i = 0; i < this->transactions.size(); i++) {
		if (this->transactions[i]->getState() == state) {
			transactions.push_back(this->transactions[i]);
		}
	}

	return transactions;
}

std::string FinancialServicesSystem::author(){
	// return my UPI: cmur196
	return "cmur196";
}

bool FinancialServicesSystem::addCustomer(Customer* customer) {
	if (!this->verifyCustomer(customer->getID())) {
		this->customers.push_back(customer);
		return true;
	} else {
		return false;
	}
}

bool FinancialServicesSystem::addAccount(Account* account) {
	if (!this->verifyAccount(account->getAccountID())) {
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
	if (!this->verifyTransaction(transaction->getID())) {
		if (this->verifyAccount(transaction->getFromAccount()->getAccountID())) {
			if (this->verifyAccount(transaction->getToAccount()->getAccountID())) {
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
	std::vector<Transaction*> transactionsInOrder;
	std::vector<Transaction*> transactionsCompleted;
	
	transactionsInOrder = this->transactions;

	std::sort(transactionsInOrder.begin(), transactionsInOrder.end());
	for (unsigned int i = 0; i < (unsigned int)transactionsInOrder.size(); i++) {
		if (transactionsInOrder[i]->getState() == TransactionState::PENDING) {
			if (transactionsInOrder[i]->performTransaction()) {
				if (transactionsInOrder[i]->getState() == TransactionState::COMPLETED) {
					transactionsCompleted.push_back(transactionsInOrder[i]);
				}
			} 
		}
	}

	return transactionsCompleted;
}

Money FinancialServicesSystem::getCustomerBalance(int customerID) const {
	Customer *customer = this->customers[getCustomerIndex(customerID)];
	std::vector<Account*> accounts = getCustomerAccounts(customer->getID());
	if (accounts.size() == 0) {
		return Money(0, 0);
	} else {
		Money amount(0, 0);
		for (unsigned int i = 0; i < accounts.size(); i++) {
			amount.add(accounts[i]->getBalance());
		}
		return amount;
	}
}

bool FinancialServicesSystem::verifyCustomer(int customerID) const {
	if (this->getCustomerIndex(customerID) != -1) {
		return true;
	} else {
		return false;
	}

}

bool FinancialServicesSystem::verifyAccount(int accountID) const {
	if (this->getAccountIndex(accountID) != -1) {
		return true;
	} else {
		return false;
	}
}

bool FinancialServicesSystem::verifyTransaction(int transactionID) const {
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

