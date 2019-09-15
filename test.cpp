#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>

// flags to enable tests for the later parts of the assignment
#define ENABLE_T2_TESTS
#define ENABLE_T3_TESTS
#define ENABLE_T4_TESTS

// include headers for classes being tested
#include "Financial/Money.hpp"
#include "Financial/Account.hpp"
#include "Financial/SavingsAccount.hpp"
#include "Financial/ChequeAccount.hpp"
#include "Financial/CreditAccount.hpp"
#include "Financial/Transaction.hpp"
#include "Financial/Customer.hpp"
#include "Financial/FinancialServicesSystem.hpp"

#ifdef ENABLE_T2_TESTS

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS

#endif /*ENABLE_T3_TESTS*/

using namespace std;

enum TestResult { TR_PASS, TR_FAIL };

#define ASSERT(condition)                                                         \
		if ((condition) == false) {                                                   \
			cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
			<< "\tExpression '" << #condition << "' evaluated to false" << endl; \
			return TR_FAIL;                                                           \
		}

/*
 * 0. This checks that you are returning your UoA username (formally known as UPI)
 */
TestResult testUPI() {
	string upi = FinancialServicesSystem::author();

	// UPIs should be at least 4 characters long
	ASSERT(upi.size() >= 4);
	// First character should be alphabetic
	ASSERT(isalpha(upi[0]));
	// Last 3 characters should be numeric
	ASSERT(isdigit(upi[upi.size() - 1]));
	ASSERT(isdigit(upi[upi.size() - 2]));
	ASSERT(isdigit(upi[upi.size() - 3]));

	// If nothing went wrong, the test passed
	return TR_PASS;
}

/*
 * 1. Test creating an instance of Money with a negative balance
 */

TestResult testMoney() {
	Money money(-2, 0);
	ASSERT(money.asCents() == -200);
	ASSERT(money.getDollars() == -2);
	ASSERT(money.getCents() == 0);

	Money money2(0, -2);
	ASSERT(money2.asCents() == -2);
	ASSERT(money2.getDollars() == 0);
	ASSERT(money2.getCents() == -2);

	Money money3(-2, -2);
	ASSERT(money3.asCents() == -202);
	ASSERT(money3.getDollars() == -2);
	ASSERT(money3.getCents() == -2);

	Money money4(-2,300);
	ASSERT(money4.asCents() == 100);
	ASSERT(money4.getDollars() == 1);
	ASSERT(money4.getCents() == 0);

	// If overall postive money still add money
	money.add(money4);
	ASSERT(money.asCents() == -100);
	ASSERT(money.getDollars() == -1);
	ASSERT(money.getCents() == 0);

	return TR_PASS;
}

/*
 * 2. Test adding positive and negative amounts to Money
 */

TestResult testAddDollarsCents() {
	Money money(10, 10);
	money.addCents(50);
	money.addDollars(5);
	ASSERT(money.asCents() == 1560);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 60);

	money.addDollars(0);
	money.addCents(0);
	ASSERT(money.asCents() == 1560);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 60);

	money.addDollars(-1);
	money.addCents(-1);
	ASSERT(money.asCents() == 1560);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 60);

	return TR_PASS;
}

/*
 * 3. Test subtracting positive and negative amounts from Money
 */

TestResult testSubtractDollarsCents() {
	Money money(10, 10);
	money.subtractCents(50);
	money.subtractDollars(11);
	ASSERT(money.asCents() == -140);
	ASSERT(money.getDollars() == -1);
	ASSERT(money.getCents() == -40);

	money.subtractDollars(0);
	money.subtractCents(0);
	ASSERT(money.asCents() == -140);
	ASSERT(money.getDollars() == -1);
	ASSERT(money.getCents() == -40);

	money.subtractDollars(-1);
	money.subtractCents(-1);
	ASSERT(money.asCents() == -140);
	ASSERT(money.getDollars() == -1);
	ASSERT(money.getCents() == -40);

	return TR_PASS;
}

/*
 * 4. Test add() positive and negative Money objects to Money
 */
TestResult testAddMoneyObject() {
	Money money(10, 10);
	money.add(Money(5,5));
	ASSERT(money.asCents() == 1515);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 15);

	money.add(Money(0,0));
	ASSERT(money.asCents() == 1515);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 15);

	money.add(Money(-1,-1));
	ASSERT(money.asCents() == 1515);
	ASSERT(money.getDollars() == 15);
	ASSERT(money.getCents() == 15);

	return TR_PASS;
}

/*
 * 5. Test subtract() positive and negative Money objects from Money
 */

TestResult testSubtractMoneyObject() {
	Money money(10, 10);
	money.subtract(Money(5,50));
	ASSERT(money.asCents() == 460);
	ASSERT(money.getDollars() == 4);
	ASSERT(money.getCents() == 60);

	money.subtract(Money(0,0));
	ASSERT(money.asCents() == 460);
	ASSERT(money.getDollars() == 4);
	ASSERT(money.getCents() == 60);

	money.subtract(Money(-1,-1));
	ASSERT(money.asCents() == 460);
	ASSERT(money.getDollars() == 4);
	ASSERT(money.getCents() == 60);

	return TR_PASS;
}

/*
 * test all money features
 */
TestResult testMoneyObjectAll() {
	Money t1 = Money(-1,-1);
	Money t2 = Money(1,120);

	// Test subtract money object features
	t1.subtract(t2);
	ASSERT(t1.asCents() == -321);
	ASSERT(t1.getDollars() == -3);
	ASSERT(t1.getCents() == -21);

	t2.subtract(t1);
	ASSERT(t2.asCents() == 220);
	ASSERT(t2.getDollars() == 2);
	ASSERT(t2.getCents() == 20);

	// Test add money object features
	t2.add(t1);
	ASSERT(t2.asCents() == 220);
	ASSERT(t2.getDollars() == 2);
	ASSERT(t2.getCents() == 20);

	t1.add(t2);
	ASSERT(t1.asCents() == -101);
	ASSERT(t1.getDollars() == -1);
	ASSERT(t1.getCents() == -1);

	// Test add dollars/cents.
	t1.addDollars(-1);
	t1.addCents(-1);

	ASSERT(t1.asCents() == -101);
	ASSERT(t1.getDollars() == -1);
	ASSERT(t1.getCents() == -1);

	t1.addDollars(1);
	t1.addCents(1);

	ASSERT(t1.asCents() == 0);
	ASSERT(t1.getDollars() == 0);
	ASSERT(t1.getCents() == 0);

	// Test the subtract dollars/cents features
	t1.subtractDollars(-1);
	t1.subtractCents(-1);

	ASSERT(t1.asCents() == 0);
	ASSERT(t1.getDollars() == 0);
	ASSERT(t1.getCents() == 0);

	t1.subtractDollars(1);
	t1.subtractCents(1);

	ASSERT(t1.asCents() == -101);
	ASSERT(t1.getDollars() == -1);
	ASSERT(t1.getCents() == -1);

	return TR_PASS;
}

/*
 * 6. Test construction of Customer instance with correct getters
 */

TestResult testCustomer() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	delete sarah;
	delete james;

	return TR_PASS;
}

/*
 * 7. Test unique ID is created for each Customer created
 */

TestResult testCustomerUniqueID() {
	std::map<int, int> ID_map;

	for(unsigned int i = 0; i<1000; i++){
		Customer customer("test "+i);
		ASSERT((ID_map.count(customer.getID()) > 0) == false && "Non-Unique ID found.");
		ID_map[customer.getID()] = 1;
	}

	return TR_PASS;
}

#ifdef ENABLE_T2_TESTS

/*
 * 8. Test construction of SavingsAccount instance with correct getters
 */

TestResult testSavingsAccount() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);
	ASSERT(sarahSavings->getCustomerID() == sarah->getID());
	ASSERT(sarahSavings->getBonusValue().asCents() == 1000);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 9. Test successful deposit
 */
TestResult testSuccessfulSavingsAccountDeposit() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	sarahSavings->depositMoney(Money(500,0));

	ASSERT(sarahSavings->getBalance().asCents()==50000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 10. Test successful deposit with bonus
 */

TestResult testSuccessfulSavingsAccountMultipleDeposit() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	sarahSavings->depositMoney(Money(500,0));

	ASSERT(sarahSavings->getBalance().asCents()==50000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	sarahSavings->depositMoney(Money(100,0));
	ASSERT(sarahSavings->getBalance().asCents()==61000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 11. Test failed deposit
 */
TestResult testFailedSavingsAccountDeposit() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	ASSERT(sarahSavings->depositMoney(Money(500,0)) == true);

	ASSERT(sarahSavings->getBalance().asCents()==50000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	//Cannot deposit negative amount. Bonus should also not be added as deposit fails.
	ASSERT(sarahSavings->depositMoney(Money(-100,0)) == false);
	ASSERT(sarahSavings->getBalance().asCents()==50000);
	ASSERT(sarahSavings->getBonusValue().asCents()==1000);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 12. Test successful withdraw and adjustment of bonus
 */

TestResult testSuccessfulSavingsAccountWithdraw() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	sarahSavings->depositMoney(Money(500,0));

	ASSERT(sarahSavings->withdrawMoney(Money(60,0)) == true);
	ASSERT(sarahSavings->getBalance().asCents()==44000);
	ASSERT(sarahSavings->getBonusValue().asCents()==800);

	ASSERT(sarahSavings->withdrawMoney(Money(100,0)) == true);
	ASSERT(sarahSavings->getBalance().asCents()==34000);
	ASSERT(sarahSavings->getBonusValue().asCents()==600);

	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 13. Test failed withdraw and no adjustment of bonus
 */

TestResult testFailedSavingsAccountWithdraw() {
	Customer* sarah = new Customer("Sarah");
	ASSERT(sarah->getName() == "Sarah");

	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	ASSERT(sarahSavings->getBalance().asCents()==0);

	sarahSavings->depositMoney(Money(500,0));

	ASSERT(sarahSavings->withdrawMoney(Money(60,0)) == true);
	ASSERT(sarahSavings->getBalance().asCents()==44000);
	ASSERT(sarahSavings->getBonusValue().asCents()==800);

	//Cannot go into negative balance. Bonus not affected as withdraw fails.
	ASSERT(sarahSavings->withdrawMoney(Money(500,0)) == false);
	ASSERT(sarahSavings->getBalance().asCents()==44000);
	ASSERT(sarahSavings->getBonusValue().asCents()==800);

	delete sarah;
	delete sarahSavings;


	return TR_PASS;
}
/*
 * Check that you cannot withdraw or deposit invalid money
 */
TestResult testSavingsAccountOne() {
	Customer* bob = new Customer("bob");
	ASSERT(bob->getName() == "bob");

	SavingsAccount* bobSavings = new SavingsAccount(bob->getID());
	ASSERT(bobSavings->getBalance().asCents()==0);

	ASSERT(bobSavings->depositMoney(Money(5,0)) == true);

	ASSERT(bobSavings->getBalance().asCents()==500);
	ASSERT(bobSavings->getBonusValue().asCents()==1000);

	// Check cant withdraw/deposit Invalid money
	ASSERT(bobSavings->depositMoney(Money(-3,0)) == false);
	ASSERT(bobSavings->getBalance().asCents()==500);
	ASSERT(bobSavings->getBonusValue().asCents()==1000);
	ASSERT(bobSavings->withdrawMoney(Money(-3,0)) == false);
	ASSERT(bobSavings->getBalance().asCents()==500);
	ASSERT(bobSavings->getBonusValue().asCents()==1000);

	delete bob;
	delete bobSavings;

	return TR_PASS;
}
/*
 * Test that the bonus value is working correctly
 */
TestResult testSavingsAccountTwo(){
	Customer* bob = new Customer("bob");
	ASSERT(bob->getName() == "bob");

	SavingsAccount* bobSavings = new SavingsAccount(bob->getID());
	ASSERT(bobSavings->getBalance().asCents()==0);

	ASSERT(bobSavings->depositMoney(Money(3,200)) == true);

	ASSERT(bobSavings->getBalance().asCents()==500);
	ASSERT(bobSavings->getBonusValue().asCents()==1000);


	ASSERT(bobSavings->depositMoney(Money(0,20)) == true);
	ASSERT(bobSavings->getBalance().asCents()==1520);
	ASSERT(bobSavings->getBonusValue().asCents()==1000);

	ASSERT(bobSavings->depositMoney(Money(2,20)) == true);
	ASSERT(bobSavings->getBalance().asCents()==1740);
	ASSERT(bobSavings->getBonusValue().asCents()==1000);

	ASSERT(bobSavings->withdrawMoney(Money(0,0)) == true);
	ASSERT(bobSavings->getBalance().asCents()==1740);
	ASSERT(bobSavings->getBonusValue().asCents()==800);

	ASSERT(bobSavings->depositMoney(Money(0,20)) == true);
	ASSERT(bobSavings->getBalance().asCents()==2560);
	ASSERT(bobSavings->getBonusValue().asCents()==800);

	ASSERT(bobSavings->depositMoney(Money(2,20)) == true);
	ASSERT(bobSavings->getBalance().asCents()==2780);
	ASSERT(bobSavings->getBonusValue().asCents()==800);

	delete bob;
	delete bobSavings;

	return TR_PASS;
}
/*
 * test that the bonus value never goes negative
 */
TestResult testSavingsAccountThree(){
	Customer* bob = new Customer("bob");
	ASSERT(bob->getName() == "bob");
	SavingsAccount* bobSavings = new SavingsAccount(bob->getID());

	int expectedValue = 800; // the starting bonus value in this case.

	for(int i = 0; i < 7; i++){
		ASSERT(bobSavings->withdrawMoney(Money(0,0)) == true);
		ASSERT(bobSavings->getBonusValue().asCents() == expectedValue);
		if(expectedValue - 200 >= 0){
			expectedValue -= 200;
		}
	}

	delete bob;
	delete bobSavings;

	return TR_PASS;
}

TestResult testSavingsAccountFour(){
	Customer* bob = new Customer("bob");
	ASSERT(bob->getName() == "bob");
	SavingsAccount* bobSavings = new SavingsAccount(bob->getID());

	ASSERT(bobSavings->withdrawMoney(Money(0,0)) == true);
	ASSERT(bobSavings->depositMoney(Money(0,0)) == true);

	delete bob;
	delete bobSavings;

	return TR_PASS;
}

TestResult testSavingsAccountFive(){
	Customer* bob = new Customer("bob");
	ASSERT(bob->getName() == "bob");
	SavingsAccount* bobSavings = new SavingsAccount(bob->getID());

	bobSavings->depositMoney(Money(2,320));
	ASSERT(bobSavings->getBalance().asCents() == 520);

	bobSavings->withdrawMoney(Money(2,400));
	ASSERT(bobSavings->getBalance().asCents() == 520);

	delete bob;
	delete bobSavings;

	return TR_PASS;
}
/*
 * test that the bonus remains constant when
 * a transaction is failed (multiple iterations).
 */
TestResult testSavingsAccountSix(){
	Customer* bob = new Customer("bob");
	ASSERT(bob->getName() == "bob");
	SavingsAccount* bobSavings = new SavingsAccount(bob->getID());

	int expectedValue = 1000; // the starting bonus value
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 7; j++){
			ASSERT(bobSavings->withdrawMoney(Money(1,0)) == false);
			ASSERT(bobSavings->getBonusValue().asCents() == expectedValue);
		}
		expectedValue -= 200;
		bobSavings->withdrawMoney(Money(0,0));
	}

	delete bob;
	delete bobSavings;

	return TR_PASS;
}
/*
 * 14. Test construction of ChequeAccount and getters
 */

TestResult testChequeAccount() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);
	ASSERT(jamesCheque->getCustomerID() == james->getID());
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 15. Test successful deposit
 */

TestResult testSuccessfulChequeAccountDeposit() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(100,0)) == true);
	ASSERT(jamesCheque->getBalance().asCents()==10000);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 16. Test failed deposit
 */

TestResult testFailedChequeAccountDeposit() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(5000,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()==0);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;


	return TR_PASS;
}


/*
 * 17. Test successful withdraw and adjustment of transaction fee
 */

TestResult testSuccessfulChequeAccountWithdraw() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(2000,0)) == true);

	//Withdraw including transaction fee and check increased fee after
	ASSERT(jamesCheque->withdrawMoney(Money(500,0)) == true);
	ASSERT(jamesCheque->getBalance().asCents()==149900);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 200);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}




/*
 * 18. Test failed withdraw, no adjustment of transaction fee
 */

TestResult testFailedChequeAccountWithdraw() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(500,0)) == true);

	ASSERT(jamesCheque->withdrawMoney(Money(5000,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()==50000);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 19. Test failed withdraw because transaction fee went over limit
 */

TestResult testFailedChequeAccountWithdrawEdge() {
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents()==0);

	ASSERT(jamesCheque->depositMoney(Money(500,0)) == true);

	ASSERT(jamesCheque->withdrawMoney(Money(500,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()==50000);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}
/*
 * Test that 3001 withdrawal will go through but
 * a 3000 wont
 */
TestResult testChequeAccountOne(){
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents() == 0);

	ASSERT(jamesCheque->depositMoney(Money(3000,0)) == true);

	ASSERT(jamesCheque->withdrawMoney(Money(2999,0)) == true);
	ASSERT(jamesCheque->getBalance().asCents()== 0);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 200);

	ASSERT(jamesCheque->depositMoney(Money(3000,0)) == true);

	ASSERT(jamesCheque->withdrawMoney(Money(3000,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()== 300000);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 200);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}
/*
 * Test for invalid input
 */
TestResult testChequeAccountTwo(){
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents() == 0);

	ASSERT(jamesCheque->depositMoney(Money(-3000,0)) == false);

	ASSERT(jamesCheque->withdrawMoney(Money(2999,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()== 0);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	ASSERT(jamesCheque->depositMoney(Money(3000,0)) == true);

	ASSERT(jamesCheque->withdrawMoney(Money(-500,0)) == false);
	ASSERT(jamesCheque->getBalance().asCents()== 300000);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}
/*
 * Check that transaction fee continues to increment correctly
 */
TestResult testChequeAccountThree(){
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents() == 0);

	int expectedValue = 200;
	jamesCheque->depositMoney(Money(3000,0));

	for(int i = 0; i < 10; i++){
		jamesCheque->withdrawMoney(Money(0,0));
		ASSERT(jamesCheque->getTransactionFee() != 0);
		ASSERT(jamesCheque->getTransactionFee()->asCents() == expectedValue);
		expectedValue += 100;
	}

	delete james;
	delete jamesCheque;

	return TR_PASS;
}
/*
 * test that a balance of greater than 3000
 * is possible.
 */
TestResult testChequeAccountFour(){
	Customer* james = new Customer("James");
	ASSERT(james->getName() == "James");

	ChequeAccount* jamesCheque = new ChequeAccount(james->getID());
	ASSERT(jamesCheque->getBalance().asCents() == 0);

	ASSERT(jamesCheque->depositMoney(Money(3000,0)) == true);
	ASSERT(jamesCheque->depositMoney(Money(123,0)) == true);
	ASSERT(jamesCheque->getBalance().asCents()== 312300);
	ASSERT(jamesCheque->getTransactionFee() != 0);
	ASSERT(jamesCheque->getTransactionFee()->asCents() == 100);

	delete james;
	delete jamesCheque;

	return TR_PASS;
}


/*
 * 20. Test construction of CreditAccount and getters
 */

TestResult testCreditAccount() {
	Customer* billie = new Customer("Billie");
	ASSERT(billie->getName() == "Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);
	ASSERT(billieCredit->getCustomerID() == billie->getID());

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 21. Test successful deposit with positive balance
 */

TestResult testSuccessfulCreditAccountDeposit() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 22. Test successful deposit with positive balance
 */

TestResult testFailedCreditAccountDeposit() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	ASSERT(billieCredit->depositMoney(Money(4600,0)) == false);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 23. Test successful withdraw with positive balance
 */

TestResult testSuccessfulCreditAccountWithdraw() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	ASSERT(billieCredit->withdrawMoney(Money(200,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == 30000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 24. Test successful withdraw into negative balance
 */

TestResult testSuccessfulCreditAccountWithdrawDebt() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	ASSERT(billieCredit->withdrawMoney(Money(800,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == -30000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * test when account balance is negative can still add money
 */

TestResult testCreditAccountOne() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);

	ASSERT(billieCredit->withdrawMoney(Money(800,77)) == true);
	ASSERT(billieCredit->getBalance().asCents() == -30077);

	ASSERT(billieCredit->depositMoney(Money(500,20)) == true);
	ASSERT(billieCredit->getBalance().asCents()== 19943);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * test invalid inputs
 */

TestResult testCreditAccountTwo() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	//invalid deposit
	ASSERT(billieCredit->depositMoney(Money(-500,0)) == false);
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->depositMoney(Money(500,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==50000);


	ASSERT(billieCredit->withdrawMoney(Money(-800,0)) == false);
	ASSERT(billieCredit->getBalance().asCents() == 50000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}
/*
 * check extreme cases of deposit (5k)
 * also check if withdraw, and depositing $0 results in successful deposit
 */
TestResult testCreditAccountThree() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	//invalid deposit
	ASSERT(billieCredit->depositMoney(Money(5000,0)) == true);
	ASSERT(billieCredit->getBalance().asCents()==500000);

	ASSERT(billieCredit->depositMoney(Money(1,0)) == false);
	ASSERT(billieCredit->getBalance().asCents()==500000);


	ASSERT(billieCredit->withdrawMoney(Money(5000,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == 0);

	ASSERT(billieCredit->depositMoney(Money(0,0)) == true);
	ASSERT(billieCredit->withdrawMoney(Money(0,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == 0);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}
/*
 * test that when withdrawing from a negative
 * credit still goes through.
 */
TestResult testCreditAccountFour() {
	Customer* billie = new Customer("Billie");

	CreditAccount* billieCredit= new CreditAccount(billie->getID());
	ASSERT(billieCredit->getBalance().asCents()==0);

	ASSERT(billieCredit->withdrawMoney(Money(100,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == -10000);

	ASSERT(billieCredit->withdrawMoney(Money(100,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == -20000);

	ASSERT(billieCredit->depositMoney(Money(100,0)) == true);
	ASSERT(billieCredit->getBalance().asCents() == -10000);

	delete billie;
	delete billieCredit;

	return TR_PASS;
}
TestResult testAccount(){
	Customer* bob = new Customer("Bob");
	ASSERT(bob->getName() == "Bob");

	SavingsAccount* bobSavings = new SavingsAccount(bob->getID());
	ASSERT(bobSavings->getBalance().asCents() == 0);
	ASSERT(bobSavings->getCustomerID() == bob->getID());
	ASSERT(bobSavings->getBonusValue().asCents() == 1000);

	bobSavings->depositMoney(Money(1,20));
	ASSERT(bobSavings->getBalance().asCents() == 120);
	ASSERT(bobSavings->getBonusValue().asCents() == 1000);

	bobSavings->depositMoney(Money(1,20));
	ASSERT(bobSavings->getBalance().asCents() == 1240);
	ASSERT(bobSavings->getBonusValue().asCents() == 1000);
	//Check that the savings cannot be altered outside of the class stack frame
	bobSavings->getBalance().addDollars(2);
	bobSavings->getBalance().addCents(1253);
	ASSERT(bobSavings->getBalance().asCents() == 1240);
	ASSERT(bobSavings->getBonusValue().asCents() == 1000);

	Customer* finn = new Customer("Finn");
	ASSERT(finn->getName() == "Finn");

	SavingsAccount* finnSavings = new SavingsAccount(finn->getID());
	ASSERT(finnSavings->getBalance().asCents() == 0);
	ASSERT(finnSavings->getCustomerID() == finn->getID());
	ASSERT(finnSavings->getCustomerID() != bob->getID()); // Check different id's
	ASSERT(finnSavings->getBonusValue().asCents() == 1000);

	finnSavings->withdrawMoney(Money(10,523));
	ASSERT(finnSavings->getBalance().asCents() == 0);
	ASSERT(finnSavings->getBonusValue().asCents() == 1000);

	finnSavings->depositMoney(Money(10,53));
	ASSERT(finnSavings->getBalance().asCents() == 1053);
	ASSERT(finnSavings->getBonusValue().asCents() == 1000);

	finnSavings->withdrawMoney(Money(8,0));
	ASSERT(finnSavings->getBalance().asCents() == 253);
	ASSERT(finnSavings->getBonusValue().asCents() == 800);

	delete bob;
	delete finn;
	delete bobSavings;
	delete finnSavings;

	return TR_PASS;
}

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS
/*
 * 25. Test construction of Transaction and getters
 */

TestResult testTransaction() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(400,0));

	ASSERT(transaction->getFromAccount() != 0);
	ASSERT(transaction->getToAccount() != 0);

	ASSERT(transaction->getFromAccount()->getAccountID() == billieCredit->getAccountID());
	ASSERT(transaction->getToAccount()->getAccountID() == jamesCheque->getAccountID());
	ASSERT(transaction->getAmount().asCents() == 40000);
	ASSERT(transaction->getState() == PENDING);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;


	return TR_PASS;
}

/*
 * 26. Test construction of Transaction with negative amount
 */

TestResult testTransactionNegativeAmount() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(-400,0));

	ASSERT(transaction->getFromAccount() != 0);
	ASSERT(transaction->getToAccount()->getAccountID() == jamesCheque->getAccountID());

	ASSERT(transaction->getFromAccount()->getAccountID() == billieCredit->getAccountID());
	ASSERT(transaction->getToAccount()->getAccountID() == jamesCheque->getAccountID());
	ASSERT(transaction->getAmount().asCents() == 0);
	ASSERT(transaction->getState() == PENDING);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 27. Test unique ID of transactions are created in ascending order beginning at 1
 */

TestResult testCorrectTransactionID() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(200,0));
	Transaction* transaction3 = new Transaction(jamesCheque, billieCredit, Money(100,0));

	ASSERT(transaction->getID() < transaction2->getID());
	ASSERT(transaction2->getID() < transaction3->getID());

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 28. Test successful transaction from credit to cheque
 */

TestResult testSuccessfulTransactionOne() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(transaction->performTransaction() == true);

	ASSERT(billieCredit->getBalance().asCents() == 40000);
	ASSERT(jamesCheque->getBalance().asCents() == 40000);

	ASSERT(transaction->getState() == COMPLETED);


	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 29. Test successful transaction from cheque to savings
 */

TestResult testSuccessfulTransactionTwo() {

	Customer* james = new Customer("James");
	Customer* sarah = new Customer("Sarah");

	Account* jamesCheque = new ChequeAccount(james->getID());
	Account* sarahSavings= new SavingsAccount(sarah->getID());

	jamesCheque->depositMoney(Money(1000,0));
	sarahSavings->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(jamesCheque, sarahSavings, Money(100,0));

	ASSERT(transaction->performTransaction() == true);

	//Including cheque transaction fee and savings deposit bonus (2nd deposit)
	ASSERT(jamesCheque->getBalance().asCents() == 89900);
	ASSERT(sarahSavings->getBalance().asCents() == 41000);

	ASSERT(transaction->getState() == COMPLETED);

	delete james;
	delete jamesCheque;
	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}


/*
 * 30. Test failed transaction from savings to savings
 */

TestResult testFailedTransactionOne() {

	Customer* james = new Customer("James");
	Customer* sarah = new Customer("Sarah");

	Account* jamesCheque = new ChequeAccount(james->getID());
	Account* sarahSavings= new SavingsAccount(sarah->getID());

	jamesCheque->depositMoney(Money(1000,0));
	sarahSavings->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(jamesCheque, sarahSavings, Money(1500,0));

	ASSERT(transaction->performTransaction() == false);

	//Including cheque transaction fee and savings deposit bonus (2nd deposit)
	ASSERT(jamesCheque->getBalance().asCents() == 100000);
	ASSERT(sarahSavings->getBalance().asCents() == 30000);

	ASSERT(transaction->getState() == FAILED);

	delete james;
	delete jamesCheque;
	delete sarah;
	delete sarahSavings;

	return TR_PASS;
}

/*
 * 31. Test failed transaction from savings to cheque
 */

TestResult testFailedTransactionTwo() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(3500,0));

	ASSERT(transaction->performTransaction() == false);

	ASSERT(billieCredit->getBalance().asCents() == 50000);
	ASSERT(jamesCheque->getBalance().asCents() == 30000);

	ASSERT(transaction->getState() == FAILED);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * check that the first transaction ID is 1 and
 * id increments correctly.
 */
TestResult testTransactionOne() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(100,0));
	Transaction* transaction3 = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(transaction->getID() == 1);
	ASSERT(transaction->getID() == 2);
	ASSERT(transaction->getID() == 3);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;
	delete transaction;
	delete transaction2;
	delete transaction3;

	return TR_PASS;
}


/*
 * Test that when cheque account fee introduced failed transaction
 */
TestResult testTransactionTwo() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(500,0)); // total amount needed to withdraw is 501

	Transaction* transaction = new Transaction(jamesCheque, billieCredit, Money(500,0));

	ASSERT(transaction->performTransaction() == false);
	ASSERT(transaction->getState() == FAILED);


	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}
/*
 * Test that when introducing a cheque account, only up
 * to $3000 can be deposited. Also tests the features of the
 * Savings account.
 */
TestResult testTransactionThree() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieSavings= new SavingsAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieSavings->depositMoney(Money(5000,0));
	jamesCheque->depositMoney(Money(500,0));

	Transaction* transaction = new Transaction(billieSavings, jamesCheque, Money(3000,0));

	ASSERT(transaction->performTransaction() == true);
	ASSERT(transaction->getState() == COMPLETED);
	ASSERT(billieSavings->getBalance().asCents() == 200000);
	ASSERT(jamesCheque->getBalance().asCents() == 350000);

	billieSavings->depositMoney(Money(2000,0)); // Don't forget bonus value

	Transaction* transaction2 = new Transaction(billieSavings, jamesCheque, Money(3001,0));
	ASSERT(transaction2->performTransaction() == false);
	ASSERT(transaction2->getState() == FAILED);
	ASSERT(billieSavings->getBalance().asCents() == 400800);
	ASSERT(jamesCheque->getBalance().asCents() == 350000);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieSavings;

	return TR_PASS;
}
/*
 * test that multiple withdrawals result in an increased
 * transaction fee within the cheque account
 */
TestResult testTransactionFour() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(500,0));

	Transaction* transaction = new Transaction(jamesCheque, billieCredit, Money(100,0));

	ASSERT(transaction->performTransaction() == true);
	ASSERT(transaction->getState() == COMPLETED);
	ASSERT(jamesCheque->getBalance().asCents() == 39900);
	ASSERT(billieCredit->getBalance().asCents() == 60000);

	Transaction* transaction2 = new Transaction(jamesCheque, billieCredit, Money(100,0));

	ASSERT(transaction2->performTransaction() == true);
	ASSERT(transaction2->getState() == COMPLETED);
	ASSERT(jamesCheque->getBalance().asCents() == 29700);
	ASSERT(billieCredit->getBalance().asCents() == 70000);

	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}
/*
 * Test that the features of the credit account
 * work with transfers.
 */
TestResult testTransactionFive() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesSavings = new SavingsAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesSavings->depositMoney(Money(10000,0));

	Transaction* transaction = new Transaction(jamesSavings, billieCredit, Money(4500,0));


	ASSERT(transaction->performTransaction() == true);
	ASSERT(transaction->getState() == COMPLETED);
	ASSERT(jamesSavings->getBalance().asCents() == 550000);
	ASSERT(billieCredit->getBalance().asCents() == 500000);

	Transaction* transaction2 = new Transaction(jamesSavings, billieCredit, Money(1,0));
	ASSERT(transaction2->performTransaction() == false);
	ASSERT(transaction2->getState() == FAILED);
	ASSERT(jamesSavings->getBalance().asCents() == 550000);
	ASSERT(billieCredit->getBalance().asCents() == 500000);

	Transaction* transaction3 = new Transaction(billieCredit, jamesSavings, Money(10000,0));
	ASSERT(transaction3->performTransaction() == true);
	ASSERT(transaction3->getState() == COMPLETED);
	ASSERT(jamesSavings->getBalance().asCents() == 1550800);
	ASSERT(billieCredit->getBalance().asCents() == -500000);

	delete james;
	delete jamesSavings;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}
/*
 * Test that extreme inputs result in correct outcomes
 * for example an input of negative money or a transfer of 0 dollars
 */
TestResult testTransactionSix() {

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Customer* pepeHands = new Customer("pepeHands");

	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());
	Account* pepeHandsSavings = new SavingsAccount(pepeHands->getID());

	//All Account are made with $0.00


	// This block tests that an input of 0 should return a successful transaction
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(0,0));
	ASSERT(transaction->performTransaction() == true);
	ASSERT(transaction->getState() == COMPLETED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	// Remember the Cheque account has a withdraw fee
	Transaction* transaction2 = new Transaction(jamesCheque, billieCredit, Money(0,0));
	ASSERT(transaction2->performTransaction() == false);
	ASSERT(transaction2->getState() == FAILED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	// test that 0 works with savings->credit
	Transaction* transaction3 = new Transaction(pepeHandsSavings, billieCredit, Money(0,0));
	ASSERT(transaction3->performTransaction() == true);
	ASSERT(transaction3->getState() == COMPLETED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	// Opposite of above should be true
	Transaction* transaction4 = new Transaction(billieCredit, pepeHandsSavings, Money(0,0));
	ASSERT(transaction4->performTransaction() == true);
	ASSERT(transaction4->getState() == COMPLETED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	// Test savings->cheque works
	Transaction* transaction5 = new Transaction(pepeHandsSavings, jamesCheque, Money(0,0));
	ASSERT(transaction5->performTransaction() == true);
	ASSERT(transaction5->getState() == COMPLETED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	// Test cheque -> savings doesn't work (withdraw fee)
	Transaction* transaction6 = new Transaction(jamesCheque, pepeHandsSavings, Money(0,0));
	ASSERT(transaction6->performTransaction() == false);
	ASSERT(transaction6->getState() == FAILED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	// Test that when a negative is inputed sets money to 0.
	// Which can result in both a successful, and not successful result
	// as tested below.
	Transaction* transaction7 = new Transaction(pepeHandsSavings, billieCredit, Money(-1,-1));
	ASSERT(transaction7->performTransaction() == true);
	ASSERT(transaction7->getState() == COMPLETED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	Transaction* transaction8 = new Transaction(pepeHandsSavings, billieCredit, Money(0,-1));
	ASSERT(transaction8->performTransaction() == true);
	ASSERT(transaction8->getState() == COMPLETED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	Transaction* transaction9 = new Transaction(pepeHandsSavings, billieCredit, Money(-1,0));
	ASSERT(transaction9->performTransaction() == true);
	ASSERT(transaction9->getState() == COMPLETED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	Transaction* transaction10 = new Transaction(jamesCheque, billieCredit, Money(-1,0));
	ASSERT(transaction10->performTransaction() == false);
	ASSERT(transaction10->getState() == FAILED);
	ASSERT(billieCredit->getBalance().asCents() == 0);
	ASSERT(jamesCheque->getBalance().asCents() == 0);
	ASSERT(pepeHandsSavings->getBalance().asCents() == 0);

	delete pepeHands;
	delete pepeHandsSavings;
	delete james;
	delete jamesCheque;
	delete billie;
	delete billieCredit;
	delete transaction;
	delete transaction2;
	delete transaction3;
	delete transaction4;
	delete transaction5;
	delete transaction6;
	delete transaction7;
	delete transaction8;
	delete transaction9;
	delete transaction10;

	return TR_PASS;
}


#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS
/*
 * 32. Test successful add customer to financial services system
 */

TestResult testSuccessfulAddCustomerFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");

	ASSERT(fss->addCustomer(billie) == true);

	std::vector<Customer*> customers = fss->getCustomers();

	ASSERT(customers.size() == 1);
	ASSERT(customers[0]->getID() == billie->getID());

	delete fss;
	delete billie;

	return TR_PASS;
}

/*
 * 33. Test failed (duplicate) add customer to financial services system
 */

TestResult testFailedAddCustomerFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");

	ASSERT(fss->addCustomer(billie) == true);

	std::vector<Customer*> customers = fss->getCustomers();

	ASSERT(customers.size() == 1);
	ASSERT(customers[0]->getID() == billie->getID());

	ASSERT(fss->addCustomer(billie) == false);
	customers = fss->getCustomers();
	ASSERT(customers.size() == 1);


	delete fss;
	delete billie;

	return TR_PASS;
}

/*
 * 34. Test successful add account to financial services system
 */

TestResult testSuccessfulAddAccountFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");
	Account* billieCredit= new CreditAccount(billie->getID());

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);

	std::vector<Account*> accounts = fss->getAccounts();

	ASSERT(accounts.size() == 1);
	ASSERT(accounts[0]->getAccountID() == billieCredit->getAccountID());

	delete fss;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 35. Test failed add account (customer doesn't exist) to financial services system
 */

TestResult testFailedAddAccountNoCustomerFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");
	Account* billieCredit= new CreditAccount(billie->getID());

	ASSERT(fss->addAccount(billieCredit) == false);

	std::vector<Account*> accounts = fss->getAccounts();

	ASSERT(accounts.size() == 0);

	delete fss;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 36. Test failed add account (duplicate) to financial services system
 */

TestResult testFailedAddAccountDuplicateFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* billie = new Customer("Billie");
	Account* billieCredit= new CreditAccount(billie->getID());

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);

	std::vector<Account*> accounts = fss->getAccounts();

	ASSERT(accounts.size() == 1);
	ASSERT(accounts[0]->getAccountID() == billieCredit->getAccountID());

	ASSERT(fss->addAccount(billieCredit) == false);
	accounts = fss->getAccounts();
	ASSERT(accounts.size() == 1);

	delete fss;
	delete billie;
	delete billieCredit;

	return TR_PASS;
}

/*
 * 37. Test successful add transaction to financial services system
 */

TestResult testSuccessfulAddTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction) == true);

	std::vector<Transaction*> transactions = fss->getTransactions();
	ASSERT(transactions.size() == 1);
	ASSERT(transactions[0]->getID() == transaction->getID());

	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 38. Test failed add transaction (to account or from account doesn't exist in system)
 */

TestResult testFailedAddTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	//Missing add jamesCheque to FSS! Should cause transaction add to fail.

	ASSERT(fss->addTransaction(transaction) == false);

	std::vector<Transaction*> transactions = fss->getTransactions();
	ASSERT(transactions.size() == 0);

	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}
/*
 * 39. Test failed add transaction (transaction already exists)
 */

TestResult testFailedAddDuplicateTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction) == true);

	std::vector<Transaction*> transactions = fss->getTransactions();
	ASSERT(transactions.size() == 1);
	ASSERT(transactions[0]->getID() == transaction->getID());

	ASSERT(fss->addTransaction(transaction) == false);

	transactions = fss->getTransactions();
	ASSERT(transactions.size() == 1);

	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 40. Test successful perform pending transaction
 */

TestResult testSuccessfulPerformTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(100,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction) == true);

	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 1);
	ASSERT(billieCredit->getBalance().asCents() == 40000);
	ASSERT(jamesCheque->getBalance().asCents() == 40000);

	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 41. Test failed perform pending transaction (valid withdraw / invalid deposit)
 */

TestResult testFailedPerformTransactionFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction = new Transaction(billieCredit, jamesCheque, Money(3500,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction) == true);

	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 0);
	ASSERT(billieCredit->getBalance().asCents() == 50000);
	ASSERT(jamesCheque->getBalance().asCents() == 30000);



	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}


/*
 * 42. Test successful pending transactions when ordered correctly
 */

TestResult testSuccessfulOrderedTransactionsFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction1 = new Transaction(billieCredit, jamesCheque, Money(400,0));
	Transaction* transaction2 = new Transaction(jamesCheque, billieCredit, Money(600,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	//Transactions added in reverse order to required execution
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction1) == true);

	//transaction1 should be performed first for both to succeed.
	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 2);
	ASSERT(billieCredit->getBalance().asCents() == 70000);
	ASSERT(jamesCheque->getBalance().asCents() == 9900);

	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 43. Test failed pending transaction when ordered correctly
 */

TestResult testFailedOrderedTransactionsFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction1 = new Transaction(jamesCheque, billieCredit, Money(600,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(400,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	//Transactions added in reverse order to required execution
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction1) == true);

	//transaction1 should be performed first and will fail, then transaction2 success
	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 1);
	ASSERT(billieCredit->getBalance().asCents() == 10000);
	ASSERT(jamesCheque->getBalance().asCents() == 70000);

	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 44. Test returned successful transactions are only those completed during this invocation
 */

TestResult testSuccesfulReturnedTransactionsFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction1 = new Transaction(jamesCheque, billieCredit, Money(100,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(200,0));
	Transaction* transaction3 = new Transaction(billieCredit, jamesCheque, Money(150,0));


	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);

	//Transaction 1 and 2 should complete and return
	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();
	ASSERT(transactionsCompleted.size() == 2);

	ASSERT(fss->addTransaction(transaction3) == true);
	//Transaction 3 should complete and return
	transactionsCompleted = fss->performPendingTransactions();
	ASSERT(transactionsCompleted.size() == 1);

	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 45. Test getTransactions and getTransactions overriden with state
 */

TestResult testGetTransactionsFSS() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));
	Transaction* transaction1 = new Transaction(jamesCheque, billieCredit, Money(100,0));
	Transaction* transaction2 = new Transaction(billieCredit, jamesCheque, Money(200,0));
	Transaction* transaction3 = new Transaction(jamesCheque, billieCredit, Money(1000,0));

	ASSERT(fss->addCustomer(billie) == true);
	ASSERT(fss->addAccount(billieCredit) == true);
	ASSERT(fss->addCustomer(james) == true);
	ASSERT(fss->addAccount(jamesCheque) == true);

	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);

	std::vector<Transaction*> transactionsCompleted = fss->getTransactions(PENDING);
	ASSERT(transactionsCompleted.size() == 2);

	fss->performPendingTransactions();

	transactionsCompleted = fss->getTransactions(PENDING);
	ASSERT(transactionsCompleted.size() == 0);
	transactionsCompleted = fss->getTransactions(COMPLETED);
	ASSERT(transactionsCompleted.size() == 2);

	ASSERT(fss->addTransaction(transaction3) == true);

	transactionsCompleted = fss->getTransactions();
	ASSERT(transactionsCompleted.size() == 3);

	fss->performPendingTransactions();

	transactionsCompleted = fss->getTransactions(FAILED);
	ASSERT(transactionsCompleted.size() == 1);


	delete fss;
	delete billie;
	delete billieCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}

/*
 * 46. Test successful getCombined balance with one positive account
 */

TestResult testGetTotalCustomerBalance() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* sarah = new Customer("Sarah");
	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	fss->addCustomer(sarah);
	fss->addCustomer(billie);
	fss->addCustomer(james);
	fss->addAccount(sarahSavings);
	fss->addAccount(jamesCheque);
	fss->addAccount(billieCredit);

	sarahSavings->depositMoney(Money(1,25));
	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Money total = fss->getCustomerBalance(sarah->getID());

	ASSERT(total.asCents() == 125);

	delete sarah;
	return TR_PASS;
}

/*
 * 47. Test successful getCombined balance with multiple accounts positive total
 */

TestResult testGetTotalCustomerBalanceMultiple() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* sarah = new Customer("Sarah");
	Customer* billie = new Customer("Billie");
	Customer* james = new Customer("James");
	CreditAccount* sarahCredit = new CreditAccount(sarah->getID());
	ChequeAccount* sarahCheque = new ChequeAccount(sarah->getID());
	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());
	Account* billieCredit= new CreditAccount(billie->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	fss->addCustomer(sarah);
	fss->addCustomer(billie);
	fss->addCustomer(james);
	fss->addAccount(sarahCredit);
	fss->addAccount(sarahCheque);
	fss->addAccount(sarahSavings);
	fss->addAccount(jamesCheque);
	fss->addAccount(billieCredit);


	sarahCredit->depositMoney(Money(1,50));
	sarahCheque->depositMoney(Money(2,0));
	sarahSavings->depositMoney(Money(1,25));
	billieCredit->depositMoney(Money(500,0));
	jamesCheque->depositMoney(Money(300,0));

	Money total = fss->getCustomerBalance(sarah->getID());

	ASSERT(total.asCents() == 475);

	delete sarah;
	return TR_PASS;
}
/*
 * test when 0 transactions are input that performPendingTransactions
 * doesn't cause any issues, i.e segmentation fault.
 */
TestResult testFSSOne() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* jimbo  = new Customer("Jimbo");
	Customer* james = new Customer("James");
	Account* jimboCredit = new CreditAccount(jimbo->getID());
	Account* jamesCheque = new ChequeAccount(james->getID());

	ASSERT (fss->addCustomer(jimbo) == true);
	ASSERT (fss->addCustomer(james) == true);
	ASSERT (fss->addAccount(jimboCredit) == true);
	ASSERT (fss->addAccount(jamesCheque) == true);

	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();
	ASSERT(transactionsCompleted.size() == 0);

	delete fss;
	delete jimbo;
	delete jimboCredit;
	delete james;
	delete jamesCheque;

	return TR_PASS;
}
/*
 * Test order longer (5 transactions)
 */
TestResult testFSSTwo() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* foo = new Customer("Foo");
	Customer* bar = new Customer("bar");
	Account* fooCheque = new ChequeAccount(foo->getID());
	Account* barCheque = new ChequeAccount(bar->getID());

	fooCheque->depositMoney(Money(700,0));
	barCheque->depositMoney(Money(100,0));
	Transaction* transaction1 = new Transaction(fooCheque, barCheque, Money(600,0));
	Transaction* transaction2 = new Transaction(barCheque, fooCheque, Money(400,0));
	Transaction* transaction3 = new Transaction(fooCheque, barCheque, Money(200,0));
	Transaction* transaction4 = new Transaction(barCheque, fooCheque, Money(400,0));
	Transaction* transaction5 = new Transaction(fooCheque, barCheque, Money(694,0));


	ASSERT(fss->addCustomer(foo) == true);
	ASSERT(fss->addAccount(fooCheque) == true);
	ASSERT(fss->addCustomer(bar) == true);
	ASSERT(fss->addAccount(barCheque) == true);

	//Transactions added in random order.
	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction3) == true);
	ASSERT(fss->addTransaction(transaction4) == true);
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction5) == true);

	//transactions should be done in the following order 1,2,3,4,5
	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 5);
	ASSERT(fooCheque->getBalance().asCents() == 0);
	ASSERT(barCheque->getBalance().asCents() == 79100);

	delete fss;
	delete foo;
	delete fooCheque;
	delete bar;
	delete barCheque;
	delete transaction1;
	delete transaction2;
	delete transaction3;
	delete transaction4;
	delete transaction5;

	return TR_PASS;
}
/*
 * Test 1 for this particular case (multiple are needed)
 * Test the cheque, credit, and savings account limitations
 * are accounted for when calling perform pending transactions.
 */
TestResult testFSSThree() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* foo = new Customer("Foo");
	Customer* bar = new Customer("bar");
	Customer* gar = new Customer("gar");

	Account* fooSavings = new SavingsAccount(foo->getID());
	Account* barCredit = new CreditAccount(bar->getID());
	Account* garCheque = new ChequeAccount(gar->getID());

	fooSavings->depositMoney(Money(10000,0));
	barCredit->depositMoney(Money(77,77));
	garCheque->depositMoney(Money(100,120));

	// Following should fail
	Transaction* transaction1 = new Transaction(fooSavings, barCredit, Money(4923,23));
	Transaction* transaction2 = new Transaction(fooSavings, garCheque, Money(3001,0));

	// Should lower the bonus value -2
	Transaction* transaction3 = new Transaction(fooSavings, barCredit, Money(5,682));

	// Should add bonus value to savings and deduct withdrawal fee
	Transaction* transaction4 = new Transaction(garCheque, fooSavings, Money(0,0));

	// Should fail due to withdrawal fee (can't go negative)
	Transaction* transaction5 = new Transaction(garCheque, fooSavings, Money(100,2));


	ASSERT(fss->addCustomer(foo) == true);
	ASSERT(fss->addAccount(fooSavings) == true);
	ASSERT(fss->addCustomer(bar) == true);
	ASSERT(fss->addAccount(barCredit) == true);
	ASSERT(fss->addCustomer(gar) == true);
	ASSERT(fss->addAccount(garCheque) == true);


	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction3) == true);
	ASSERT(fss->addTransaction(transaction4) == true);
	ASSERT(fss->addTransaction(transaction5) == true);

	std::vector<Transaction*> transactionsPending = fss->getTransactions(PENDING);
	ASSERT(transactionsPending.size() == 5);


	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();
	std::vector<Transaction*> transactionsFailed = fss->getTransactions(FAILED);
	transactionsPending = fss->getTransactions(PENDING);

	ASSERT(transactionsCompleted.size() == 2);
	ASSERT(transactionsFailed.size() == 3);
	ASSERT(transactionsPending.size() == 0);
	ASSERT(fooSavings->getBalance().asCents() == 999618);
	ASSERT(barCredit->getBalance().asCents() == 8959);
	ASSERT(garCheque->getBalance().asCents() == 10020);

	delete fss;
	delete foo;
	delete fooSavings;
	delete bar;
	delete barCredit;
	delete transaction1;
	delete transaction2;
	delete transaction3;
	delete transaction4;
	delete transaction5;


	return TR_PASS;
}
/*
 * Test all account types are added correctly
 * to the system as well as customers.
 */
TestResult testFSSFour() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* foo = new Customer("Foo");
	Customer* bar = new Customer("bar");
	Customer* gar = new Customer("gar");

	Account* fooSavings = new SavingsAccount(foo->getID());
	Account* barCredit = new CreditAccount(bar->getID());
	Account* garCheque = new ChequeAccount(gar->getID());

	// Nothing should be in the system yet
	ASSERT(fss->verifyCustomer(foo->getID()) == false);
	ASSERT(fss->verifyCustomer(bar->getID()) == false);
	ASSERT(fss->verifyCustomer(gar->getID()) == false);
	ASSERT(fss->verifyAccount(fooSavings->getAccountID()) == false);
	ASSERT(fss->verifyAccount(barCredit->getAccountID()) == false);
	ASSERT(fss->verifyAccount(garCheque->getAccountID()) == false);

	// Accounts cannot be added until customer exists in system
	ASSERT(fss->addAccount(fooSavings) == false);
	ASSERT(fss->addAccount(barCredit) == false);
	ASSERT(fss->addAccount(garCheque) == false);

	// Add everything to the system
	ASSERT(fss->addCustomer(foo) == true);
	ASSERT(fss->addAccount(fooSavings) == true);
	ASSERT(fss->addCustomer(bar) == true);
	ASSERT(fss->addAccount(barCredit) == true);
	ASSERT(fss->addCustomer(gar) == true);
	ASSERT(fss->addAccount(garCheque) == true);

	// Check it was all added
	ASSERT(fss->verifyCustomer(foo->getID()) == true);
	ASSERT(fss->verifyCustomer(bar->getID()) == true);
	ASSERT(fss->verifyCustomer(gar->getID()) == true);
	ASSERT(fss->verifyAccount(fooSavings->getAccountID()) == true);
	ASSERT(fss->verifyAccount(barCredit->getAccountID()) == true);
	ASSERT(fss->verifyAccount(garCheque->getAccountID()) == true);

	// Can't add duplicates
	ASSERT(fss->addCustomer(foo) == false);
	ASSERT(fss->addAccount(fooSavings) == false);
	ASSERT(fss->addCustomer(bar) == false);
	ASSERT(fss->addAccount(barCredit) == false);
	ASSERT(fss->addCustomer(gar) == false);
	ASSERT(fss->addAccount(garCheque) == false);

	delete fss;
	delete foo;
	delete fooSavings;
	delete bar;
	delete barCredit;

	return TR_PASS;
}
/*
 * Test transactions are added correctly
 */
TestResult testFSSFive() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* foo = new Customer("Foo");
	Customer* bar = new Customer("bar");
	Customer* gar = new Customer("gar");

	Account* fooSavings = new SavingsAccount(foo->getID());
	Account* barCredit = new CreditAccount(bar->getID());
	Account* garCheque = new ChequeAccount(gar->getID());

	fooSavings->depositMoney(Money(10000,0));
	barCredit->depositMoney(Money(77,77));
	garCheque->depositMoney(Money(100,120));

	// Following should fail
	Transaction* transaction1 = new Transaction(fooSavings, barCredit, Money(4923,23));
	Transaction* transaction2 = new Transaction(fooSavings, garCheque, Money(3001,0));

	// Should lower the bonus value -2
	Transaction* transaction3 = new Transaction(fooSavings, barCredit, Money(5,682));

	// Should add bonus value to savings and deduct withdrawal fee
	Transaction* transaction4 = new Transaction(garCheque, fooSavings, Money(0,0));

	// Should fail due to withdrawal fee (can't go negative)
	Transaction* transaction5 = new Transaction(garCheque, fooSavings, Money(100,2));


	ASSERT(fss->addCustomer(foo) == true);
	ASSERT(fss->addAccount(fooSavings) == true);
	ASSERT(fss->addCustomer(bar) == true);
	ASSERT(fss->addAccount(barCredit) == true);
	ASSERT(fss->addCustomer(gar) == true);
	ASSERT(fss->addAccount(garCheque) == true);


	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction3) == true);
	ASSERT(fss->addTransaction(transaction4) == true);
	ASSERT(fss->addTransaction(transaction5) == true);

	std::vector<Transaction*> transactionsPending = fss->getTransactions(PENDING);
	ASSERT(transactionsPending.size() == 5);


	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();
	std::vector<Transaction*> transactionsFailed = fss->getTransactions(FAILED);
	transactionsPending = fss->getTransactions(PENDING);

	ASSERT(transactionsCompleted.size() == 2);
	ASSERT(transactionsFailed.size() == 3);
	ASSERT(transactionsPending.size() == 0);
	ASSERT(fooSavings->getBalance().asCents() == 999618);
	ASSERT(barCredit->getBalance().asCents() == 8959);
	ASSERT(garCheque->getBalance().asCents() == 10020);

	delete fss;
	delete foo;
	delete fooSavings;
	delete bar;
	delete barCredit;
	delete transaction1;
	delete transaction2;
	delete transaction3;
	delete transaction4;
	delete transaction5;


	return TR_PASS;
}

TestResult testFSSSix() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* foo = new Customer("Foo");
	Customer* bar = new Customer("bar");
	Customer* gar = new Customer("gar");

	Account* fooSavings = new SavingsAccount(foo->getID());
	Account* barCredit = new CreditAccount(bar->getID());
	Account* garCheque = new ChequeAccount(gar->getID());

	fooSavings->depositMoney(Money(100,0));
	barCredit->depositMoney(Money(0,0));
	garCheque->depositMoney(Money(100,0));


	Transaction* transaction1 = new Transaction(fooSavings, barCredit, Money(0,0));
	Transaction* transaction2 = new Transaction(fooSavings, garCheque, Money(0,0));
	Transaction* transaction3 = new Transaction(fooSavings, barCredit, Money(0,0));
	Transaction* transaction4 = new Transaction(garCheque, fooSavings, Money(0,0));
	Transaction* transaction5 = new Transaction(garCheque, fooSavings, Money(0,0));

	// Attempt to just add customers.
	ASSERT(fss->addCustomer(foo) == true);
	ASSERT(fss->addCustomer(bar) == true);
	ASSERT(fss->addCustomer(gar) == true);

	// Check that when only the Credit account is added but no others fails
	ASSERT(fss->addAccount(barCredit) == true);
	ASSERT(fss->addTransaction(transaction1) == false);
	ASSERT(fss->addTransaction(transaction2) == false);
	ASSERT(fss->addTransaction(transaction3) == false);
	ASSERT(fss->addTransaction(transaction4) == false);
	ASSERT(fss->addTransaction(transaction5) == false);


	ASSERT(fss->addAccount(fooSavings) == true);
	ASSERT(fss->addAccount(garCheque) == true);

	// Everything added should work now
	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction3) == true);
	ASSERT(fss->addTransaction(transaction4) ==	true);
	ASSERT(fss->addTransaction(transaction5) == true);

	delete fss;
	delete foo;
	delete fooSavings;
	delete bar;
	delete barCredit;
	delete transaction1;
	delete transaction2;
	delete transaction3;
	delete transaction4;
	delete transaction5;


	return TR_PASS;
}

TestResult testFSSSeven() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* foo = new Customer("Foo");
	Customer* bar = new Customer("bar");
	Customer* gar = new Customer("gar");

	Account* fooSavings = new SavingsAccount(foo->getID());
	Account* barCredit = new CreditAccount(bar->getID());
	Account* garCheque = new ChequeAccount(gar->getID());

	fooSavings->depositMoney(Money(100,0));
	barCredit->depositMoney(Money(0,0));
	garCheque->depositMoney(Money(100,0));


	Transaction* transaction1 = new Transaction(fooSavings, barCredit, Money(0,0));
	Transaction* transaction2 = new Transaction(fooSavings, garCheque, Money(0,0));
	Transaction* transaction3 = new Transaction(fooSavings, barCredit, Money(0,0));
	Transaction* transaction4 = new Transaction(garCheque, fooSavings, Money(0,0));
	Transaction* transaction5 = new Transaction(garCheque, fooSavings, Money(0,0));

	// Attempt to just add customers.
	ASSERT(fss->addCustomer(foo) == true);
	ASSERT(fss->addCustomer(bar) == true);
	ASSERT(fss->addCustomer(gar) == true);

	// Check that when only the Cheque account is added but no others fails
	ASSERT(fss->addAccount(garCheque) == true);
	ASSERT(fss->addTransaction(transaction1) == false);
	ASSERT(fss->addTransaction(transaction2) == false);
	ASSERT(fss->addTransaction(transaction3) == false);
	ASSERT(fss->addTransaction(transaction4) == false);
	ASSERT(fss->addTransaction(transaction5) == false);


	ASSERT(fss->addAccount(fooSavings) == true);
	ASSERT(fss->addAccount(barCredit) == true);

	// Everything added should work now
	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction3) == true);
	ASSERT(fss->addTransaction(transaction4) ==	true);
	ASSERT(fss->addTransaction(transaction5) == true);

	delete fss;
	delete foo;
	delete fooSavings;
	delete bar;
	delete barCredit;
	delete transaction1;
	delete transaction2;
	delete transaction3;
	delete transaction4;
	delete transaction5;


	return TR_PASS;
}
/*
 * Test that when 0 dollar transactions
 * are made, they can pass through either
 * successfuly or not.
 */
TestResult testFSSEight() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();

	Customer* foo = new Customer("Foo");
	Customer* bar = new Customer("bar");
	Customer* gar = new Customer("gar");

	Account* fooSavings = new SavingsAccount(foo->getID());
	Account* barCredit = new CreditAccount(bar->getID());
	Account* garCheque = new ChequeAccount(gar->getID());

	fooSavings->depositMoney(Money(100,0));
	barCredit->depositMoney(Money(0,0));
	garCheque->depositMoney(Money(100,0));


	Transaction* transaction1 = new Transaction(fooSavings, barCredit, Money(0,0));
	Transaction* transaction2 = new Transaction(fooSavings, garCheque, Money(0,0));
	Transaction* transaction3 = new Transaction(fooSavings, barCredit, Money(0,0));
	Transaction* transaction4 = new Transaction(garCheque, fooSavings, Money(0,0));
	Transaction* transaction5 = new Transaction(garCheque, fooSavings, Money(0,0));
	Transaction* transaction6 = new Transaction(barCredit, garCheque, Money(0,0));


	ASSERT(fss->addCustomer(foo) == true);
	ASSERT(fss->addCustomer(bar) == true);
	ASSERT(fss->addCustomer(gar) == true);
	ASSERT(fss->addAccount(garCheque) == true);
	ASSERT(fss->addAccount(fooSavings) == true);
	ASSERT(fss->addAccount(barCredit) == true);


	ASSERT(fss->addTransaction(transaction1) == true);
	ASSERT(fss->addTransaction(transaction2) == true);
	ASSERT(fss->addTransaction(transaction3) == true);
	ASSERT(fss->addTransaction(transaction4) ==	true);
	ASSERT(fss->addTransaction(transaction5) == true);
	ASSERT(fss->addTransaction(transaction6) == true);

	std::vector<Transaction*> transactionsCompleted = fss->performPendingTransactions();

	ASSERT(transactionsCompleted.size() == 6);
	ASSERT(fooSavings->getBalance().asCents() == 10400);
	ASSERT(barCredit->getBalance().asCents() == 0);
	ASSERT(garCheque->getBalance().asCents() == 9700);

	delete fss;
	delete foo;
	delete fooSavings;
	delete bar;
	delete barCredit;
	delete transaction1;
	delete transaction2;
	delete transaction3;
	delete transaction4;
	delete transaction5;


	return TR_PASS;
}
/*
 * Test that a overall balance of less than 0 can be returned
 */
TestResult testFSSNine() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* sarah = new Customer("Sarah");
	CreditAccount* sarahCredit = new CreditAccount(sarah->getID());
	ChequeAccount* sarahCheque = new ChequeAccount(sarah->getID());
	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());

	fss->addCustomer(sarah);
	fss->addAccount(sarahCredit);
	fss->addAccount(sarahCheque);
	fss->addAccount(sarahSavings);

	sarahCredit->withdrawMoney(Money(1000,0));
	sarahCheque->depositMoney(Money(200,22));
	sarahSavings->depositMoney(Money(689,25));

	Money total = fss->getCustomerBalance(sarah->getID());

	ASSERT(total.asCents() == -11053);

	delete sarah;
	return TR_PASS;
}
/*
 * Test that the customer account balance can be 0 dollars total.
 */
TestResult testFSSTen() {

	FinancialServicesSystem* fss = new FinancialServicesSystem();
	Customer* sarah = new Customer("Sarah");
	CreditAccount* sarahCredit = new CreditAccount(sarah->getID());
	ChequeAccount* sarahCheque = new ChequeAccount(sarah->getID());
	SavingsAccount* sarahSavings = new SavingsAccount(sarah->getID());

	fss->addCustomer(sarah);
	fss->addAccount(sarahCredit);
	fss->addAccount(sarahCheque);
	fss->addAccount(sarahSavings);

	sarahCredit->withdrawMoney(Money(1000,0));
	sarahCheque->depositMoney(Money(200,0));
	sarahSavings->depositMoney(Money(800,0));

	Money total = fss->getCustomerBalance(sarah->getID());

	ASSERT(total.asCents() == 0);

	delete fss;
	delete sarah;
	return TR_PASS;
}

#endif /*ENABLE_T4_TESTS*/

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
 */

vector<TestResult (*)()> generateTests() {
	vector<TestResult (*)()> tests;

	tests.push_back(&testUPI);
	tests.push_back(&testMoney);
	tests.push_back(&testAddDollarsCents);
	tests.push_back(&testSubtractDollarsCents);
	tests.push_back(&testAddMoneyObject);
	tests.push_back(&testSubtractMoneyObject);
	tests.push_back(&testCustomer);
	tests.push_back(&testCustomerUniqueID);
	tests.push_back(&testMoneyObjectAll);

#ifdef ENABLE_T2_TESTS

	tests.push_back(&testSavingsAccount);
	tests.push_back(&testSuccessfulSavingsAccountDeposit);
	tests.push_back(&testSuccessfulSavingsAccountMultipleDeposit);
	tests.push_back(&testFailedSavingsAccountDeposit);
	tests.push_back(&testSuccessfulSavingsAccountWithdraw);
	tests.push_back(&testFailedSavingsAccountWithdraw);
	tests.push_back(&testChequeAccount);
	tests.push_back(&testSuccessfulChequeAccountDeposit);
	tests.push_back(&testFailedChequeAccountDeposit);
	tests.push_back(&testSuccessfulChequeAccountWithdraw);
	tests.push_back(&testFailedChequeAccountWithdraw);
	tests.push_back(&testFailedChequeAccountWithdrawEdge);
	tests.push_back(&testCreditAccount);
	tests.push_back(&testSuccessfulCreditAccountDeposit);
	tests.push_back(&testFailedCreditAccountDeposit);
	tests.push_back(&testSuccessfulCreditAccountWithdraw);
	tests.push_back(&testSuccessfulCreditAccountWithdrawDebt);
	tests.push_back(&testSavingsAccountOne);
	tests.push_back(&testSavingsAccountTwo);
	tests.push_back(&testSavingsAccountThree);
	tests.push_back(&testSavingsAccountFour);
	tests.push_back(&testSavingsAccountFive);
	tests.push_back(&testSavingsAccountSix);
	tests.push_back(&testChequeAccountOne);
	tests.push_back(&testChequeAccountTwo);
	tests.push_back(&testChequeAccountThree);
	tests.push_back(&testChequeAccountFour);
	tests.push_back(&testCreditAccountOne);
	tests.push_back(&testCreditAccountTwo);
	tests.push_back(&testCreditAccountThree);
	tests.push_back(&testCreditAccountFour);
	tests.push_back(&testAccount);

#endif /*ENABLE_T2_TESTS*/

#ifdef ENABLE_T3_TESTS

	//tests.push_back(&testTransactionOne);
	tests.push_back(&testTransaction);
	tests.push_back(&testTransactionNegativeAmount);
	tests.push_back(&testCorrectTransactionID);
	tests.push_back(&testSuccessfulTransactionOne);
	tests.push_back(&testSuccessfulTransactionTwo);
	tests.push_back(&testFailedTransactionOne);
	tests.push_back(&testFailedTransactionTwo);
	tests.push_back(&testTransactionTwo);
	tests.push_back(&testTransactionThree);
	tests.push_back(&testTransactionFour);
	tests.push_back(&testTransactionFive);
	tests.push_back(&testTransactionSix);

#endif /*ENABLE_T3_TESTS*/

#ifdef ENABLE_T4_TESTS

	tests.push_back(&testSuccessfulAddCustomerFSS);
	tests.push_back(&testFailedAddCustomerFSS);
	tests.push_back(&testSuccessfulAddAccountFSS);
	tests.push_back(&testFailedAddAccountNoCustomerFSS);
	tests.push_back(&testFailedAddAccountDuplicateFSS);
	tests.push_back(&testSuccessfulAddTransactionFSS);
	tests.push_back(&testFailedAddTransactionFSS);
	tests.push_back(&testFailedAddDuplicateTransactionFSS);
	tests.push_back(&testSuccessfulPerformTransactionFSS);
	tests.push_back(&testFailedPerformTransactionFSS);
	tests.push_back(&testSuccessfulOrderedTransactionsFSS);
	tests.push_back(&testFailedOrderedTransactionsFSS);
	tests.push_back(&testSuccesfulReturnedTransactionsFSS);
	tests.push_back(&testGetTransactionsFSS);
	tests.push_back(&testGetTotalCustomerBalance);
	tests.push_back(&testGetTotalCustomerBalanceMultiple);
	tests.push_back(&testFSSOne);
	tests.push_back(&testFSSTwo);
	tests.push_back(&testFSSThree);
	tests.push_back(&testFSSFour);
	tests.push_back(&testFSSFive);
	tests.push_back(&testFSSSix);
	tests.push_back(&testFSSSeven);
	tests.push_back(&testFSSEight);
	tests.push_back(&testFSSNine);
	tests.push_back(&testFSSTen);

#endif /*ENABLE_T4_TESTS*/

return tests;
}

int main(int argc, char const* argv[]) {

	// If one or more test numbers are passed as command-line parameters, execute them
	vector<TestResult (*)()> tests_to_run = generateTests();
	unsigned int pass_count = 0;
	unsigned int fail_count = 0;
	unsigned int run_count = 0;
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			unsigned int test_num = atoi(argv[i]);
			if (test_num > tests_to_run.size()) {
				cout << "ERROR: unknown test case " << test_num << endl;
				continue;
			}
			// run the test
			++run_count;
			TestResult result = tests_to_run[test_num]();
			if (result == TR_FAIL) {
				cout << "FAIL: Test " << test_num << " failed." << endl;
				++fail_count;
			} else {
				cout << "PASS: Test " << test_num << " passed." << endl;
				++pass_count;
			}
		}
	} else {
		// otherwise, run all tests
		// Make sure to update this section as you add more tests
		// Add the tests for the first task
		for (unsigned int t = 0; t < tests_to_run.size(); ++t) {
			++run_count;
			TestResult result = tests_to_run[t]();
			if (result == TR_FAIL) {
				cout << "FAIL: Test " << t << " failed." << endl;
				++fail_count;
			} else {
				cout << "PASS: Test " << t << " passed." << endl;
				++pass_count;
			}
		}
	}
	cout << "\n-------------------------------------------------\n"
			<< "Total Run: " << run_count << "\n"
			<< "Total PASSED: " << pass_count << "\n"
			<< "Total FAILED: " << fail_count << "\n"
			<< "-------------------------------------------------\n" << endl;

	// Return 0 if everything was ok
	if(fail_count > 0) {
		return 1;
	} else {
		return 0;
	}

}
