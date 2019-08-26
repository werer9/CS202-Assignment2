
#ifndef MONEY_H_
#define MONEY_H_

class Money {
private:
	int totalCents;
public:
	Money();
	Money(int dollars, int cents);

	// return amount of dollars
	int getDollars() const;
	// return amount of cents
	int getCents() const;
	// return total amount in cents
	int asCents() const;

	// add dollars to the amount
	void addDollars(int dollars);
	// add cents to the amount
	void addCents(int cents);
	// remove amount in dollars
	void subtractDollars(int dollars);
	// remove amount in cents
	void subtractCents(int cents);

	// add amount from another money object
	void add(const Money &other);
	// remove amount in nother money object
	void subtract(const Money &other);
	// evenly split total amount across two money objects
	void split(Money &other);

	// destructor
	virtual ~Money();
};

#endif /* MONEY_H_ */
