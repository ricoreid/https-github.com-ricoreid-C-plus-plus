// CommissionEmployee class definition represents a commissioned employee
#ifndef COMMISSION_H
#define COMMISSION_H

#include <string> // C++ standard string class
using namespace std;

class CommissionEmployee {
public:
	CommissionEmployee(const string &, const string &, const string &, double = 0.0, double = 0.0);

	void setFirstName(const string &); // set first name
	string getFirstName() const; // returns first name

	void setLastName(const string &); // set last name
	string getLastName() const; // returns last name

	void setSocialSecurity(const string &); // set social security
	string getSocialSecurity() const; // returns social security

	void setGrossSales(double); // set gross sales amount
	double getGrossSales() const; // return gross sales amount

	void setCommissionRate(double); // set commission rate (percentage)
	double getCommissionRate() const; // return commission rate

	double earnings() const; // calculate earnings
	void print() const; // print CommissionEmployee Object

private:
	string firstName;
	string lastName;
	string socialSecurityNumber;
	double grossSales; // gross weekly sales
	double commissionRate; // commission percentage
}; // ends commission class

#endif

