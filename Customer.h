#ifndef  CUSTOMER_H
#define  CUSTOMER_H
#include <iostream>

using namespace std;

class Customer{
private:
	int trn;
	string lastName;
	string address;
	string phoneNumber;
	int creditBalance;
	static int totalNoCustomer;
public:

	Customer(){
		trn = 0;
		lastName = "null";
		address = "null";
		phoneNumber = "null";
		creditBalance = 100;
		totalNoCustomer+=1;
	}

	Customer(int trn,string lastName,string address,
				string phoneNumber,int creditBalance,int totalNoCustomer ){
		this->trn = trn;
		this->lastName = lastName;
		this->address = address;
		this->phoneNumber = phoneNumber;
		this->creditBalance = creditBalance;
	}
	
	void incrementCustomer(){
		totalNoCustomer ++;
	}
	void addCredit(int credit){
		creditBalance += credit;
		cout << "\nCredit Added\n" << endl;
	}

	void checkBalance(){
		cout << lastName << "'s"<< " Credit Balance is: " << creditBalance << "\n"<< endl;
	}

	void setTrn(int trn){
		this->trn = trn; 
	}

	int getTrn(){
		return trn;
	}

	void setLastName(string lastName){
		this->lastName= lastName; 
	}

	string getLastName(){
		return lastName;
	}

	void setAddress(string address){
		this->address = address;
	}
	string getAddress(){
		return address;
	}
	void setPhoneNumber(string phoneNumber){
		this->phoneNumber = phoneNumber;
	}
	string getPhoneNumber(){
		return phoneNumber;
	}
	void setCreditBalance(int creditBalance){
		this->creditBalance = creditBalance;
	}

	int getCreditBalance(){
		return creditBalance;
	}
	void setTotalNoCustomer(int totalNoCustomer){
		this->totalNoCustomer= totalNoCustomer; 
	}
	int getTotalNoCustomer(){
		return totalNoCustomer;
	}

};
int Customer::totalNoCustomer = 0;

#endif

