#include "Customer.hpp"
#include <string>

int Customer::ID = 0;

Customer::Customer(const std::string &name) {
	this->name = name;
	this->customerID = ++ID;
}

std::string Customer::getName() const {
	return this->name;
}

int Customer::getID() const {
	return this->customerID;
}

Customer::~Customer() {
	// No implementation needed so far
}

