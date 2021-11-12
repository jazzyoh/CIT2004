#ifndef  SERVICEPROVIDER_H
#define  SERVICEPROVIDER_H

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "Customer.h"

using namespace std;

class ServiceProvider : public exception {

private:
	string companyId;
	string companyAddress;
	static int totalNoCustomer;
	string password;
protected:
	Customer customer;
	string creditCard;
public:
	ServiceProvider() {
		companyId = "null";
		companyAddress = "null";
		password = "null";
		creditCard = '0';
	}

	ServiceProvider(string companyId, string companyAddress, string password, string creditCard, int totalNoCustomer, Customer* customer) {
		this->companyAddress = companyId;
		this->password = password;
		this->totalNoCustomer = totalNoCustomer;
		this->creditCard = '0';
		this->customer.setTrn(customer->getTrn());
		this->customer.setLastName(customer->getLastName());
		this->customer.setAddress(customer->getAddress());
		this->customer.setPhoneNumber(customer->getPhoneNumber());
		this->customer.setTotalNoCustomer(customer->getTotalNoCustomer());
	}

	//virtual void viewCompanyInfo();
	virtual void viewAllPhoneCredit() = 0;
	virtual bool findCustomer(string) = 0;
	virtual void addCustomer() = 0;
	virtual bool login(string) = 0;
	virtual void viewCustomerBase() = 0;
	virtual void saveCustomerDetails() = 0;
	virtual void saveCardTopUpDetails() = 0;
	virtual void addCredit() = 0;
	virtual bool findCard(string) = 0;
	virtual void checkPhoneNumber(string) = 0;
	//virtual void updateCustomer(Customer)=0;
	//virtual void updateCardInfo(string){};
	//virtual Customer getCustomer(){ return customer; };


	void createPhoneCard() {
		string buffer;
		int hold, choice;
		const string demoniation[] = { "100","200","500","1000" };
		const string status[] = { "Used","Available" };

		try {
			cout << "Create Phone Card\n\n" <<
				"Select Denomination:\n" <<
				"1 for $100\n" <<
				"2 for $200\n" <<
				"3 for $500\n" <<
				"4 for $1000\n" << endl;
			cin >> choice;
			if (cin.fail())
				throw runtime_error("Value not Expected");
			else if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
				throw - 1;

			else {
				int sentinel;
				if (choice == 4)
					sentinel = 8;
				else
					sentinel = 9;

				random_device rand; //Getting a random number
				mt19937 generate(rand()); //Random number generator 
				uniform_int_distribution<> distribution(0, 9); //random number range definition

				for (int i = 0;i <= sentinel;i++) {
					hold = (distribution(generate)); //assigning random number to hold
					buffer += to_string(hold); //type casting hold to string and storing it in buffer
				}
				buffer += demoniation[choice - 1];
				buffer += ("\t" + status[1]);// Appending Status to credit number 
				cout << "\n\n" << endl;
				this->creditCard = buffer;
				cout << "New Phone Card is: " << this->creditCard << "\n\n" << endl;
				saveCardTopUpDetails();
			}
		}
		catch (runtime_error& err) {
			cerr << err.what() << endl;
		}
		catch (int& err) {
			cerr << "Enter one of the values displayed\n" << endl;
		}
		catch (...) {
			cerr << "A fatal error has occurred " << endl;
			return;
		}
	}

	int viewTotalNumberOfCustomer() {//Could be overridden or maybe it should show all customers from each base 
		cout << "Total Number of Customers: are\n\n" << endl;
		return this->totalNoCustomer;
	}


	void setPassword(string password) {
		this->password = password;
	}

	string getPassword() {
		return password;
	}

	void setCompanyId(string companyId) {
		this->companyId = companyId;
	}

	string getCompanyId() {
		return companyId;
	}

	void setComapnyAddress(string companyAddress) {
		this->companyAddress = companyAddress;
	}

	string getComapnyAddress() {
		return companyAddress;
	}
	string getCustomerName() {
		return customer.getLastName();
	}
	int getCustomerTrn() {
		return customer.getTrn();
	}
	string getCustomerPhone() {
		return customer.getAddress();
	}
	int getCustomerBalance() {
		return customer.getCreditBalance();
	}
	Customer getCustomer() {
		return customer;
	}

	void updateCustomerInfromation() {
		//Notice we should use a binary file to write and read customer and caard infromation 
		//we need to indec the number of customers  and use that as a primary key eck tool
		//to identfy the customer  this woull makke it easier checking the files  because
		//if u look at the question sheet we need to display the total number of customer from bother service providers
		//we arnt allowed to save the number of customers in the file directly so this would be a good workaround
		//and also we coulse associate the same number of the cutomer to the respective card info.
	}

	virtual ~ServiceProvider() {};
};



#endif
