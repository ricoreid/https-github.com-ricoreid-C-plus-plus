#include <iostream>
#include <iomanip>
#include "CommissionEmployee.h"
#include "BasePlusCommissionEmployee.h"

using namespace std;

int main() {
	// instantiate a CommissionEmployee object
	BasePlusCommissionEmployee employee("Sue", "Jones", "222-22-2222", 1000, 0.6, 2000);

	// set floating point output formatting
	cout << fixed << setprecision(2);

	// get commission employee data
	cout << "Employee information obtained by get functions: \n"
		<< "\nFirst name is " << employee.getFirstName()
		<< "\nLast name is " << employee.getLastName()
		<< "\nSocial security number is " << employee.getSocialSecurity()
		<< "\nGross sales is " << employee.getGrossSales()
		<< "\nCommission rate is " << employee.getCommissionRate() 
		<< "\nBase Salary: " << employee.getBaseSalary() << endl;

	employee.setGrossSales(8000); // sets gross sales
	employee.setCommissionRate(0.6); // set commission rate

	cout << "\nUpdated employee information output printed by function: \n" << endl;
	employee.print(); // displays the new employee information

	// displays the employee's earnings
	cout << "\n\nEmployee's Earnings: $" << employee.earnings() << endl;

	system("PAUSE");
} // end main