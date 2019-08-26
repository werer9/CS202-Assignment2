
#include "Money.hpp"

Money::Money() : totalCents(0) {
}

Money::Money(int dollars, int cents) {
	// convert dollars to cents and store in total cents
	this->totalCents = dollars*100 + cents;
}

int Money::getDollars() const {
	// convert all cents to dollars and truncate cents
	return totalCents/100;
}

int Money::getCents() const {
	// return cents that are worth less than a dollar
	return totalCents%100;
}

int Money::asCents() const {
	// return total amount in cents
	return totalCents;
}

void Money::addDollars(int dollars) {
	// check dollars is not negative before adding
	if (dollars > 0) {
		this->totalCents += dollars*100;
	}
}

void Money::addCents(int cents) {
	// check cents is not negative before adding
	if (cents > 0) {
		this->totalCents += cents;
	}
}

void Money::subtractDollars(int dollars) {
	// check dollars is not negative before subtracting
	if (dollars > 0) {
		this->totalCents -= dollars*100;
	}
}

void Money::subtractCents(int cents) {
	// check cents is not negative before substracting
	if (cents > 0) {
		this->totalCents -= cents;
	}
}

void Money::add(const Money &other) {
	// add amount from other money to this instance
	if (other.totalCents > 0) {
		this->totalCents += other.totalCents;
	}
}

void Money::subtract(const Money &other) {
	// remove amount in other money from this instance
	if (other.totalCents > 0) {
		this->totalCents -= other.totalCents;
	}
}

void Money::split(Money &other) {
	// get total of both instances then half
	int newTotal = (this->totalCents + other.totalCents)/2;
	// set new total to both instances
	this->totalCents = newTotal;
	other.totalCents = newTotal;
}

Money::~Money() {
}
