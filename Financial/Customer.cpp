#include "Customer.hpp"
#include <string>

// initialise non instance id to generate unique customer id
int Customer::ID = 0;

Customer::Customer(const std::string &name) {
	// assign name to member variable
	this->name = name;
	// set id to unique customer id
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

