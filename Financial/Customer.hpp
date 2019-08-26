#include <string>
#ifndef CUSTOMER_HPP_
#define CUSTOMER_HPP_

class Customer {
private:
	// private variables
	std::string name;
	static int ID;
	int customerID;
	
	// copy operators
	Customer& operator=(const Customer &other);
    Customer(const Customer &other);
	

public:
	// contructor
	Customer(const std::string &name);

	// public methods
	std::string getName() const;
	// return customer id
	int getID() const;
	// destructor
	virtual ~Customer();
};

#endif /* CUSTOMER_HPP_ */
