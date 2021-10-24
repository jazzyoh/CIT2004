#ifndef  CUSTOMER_H
#define  CUSTOMER_H
#include <iostream>
#include <fstream>

using namespace std;

class Customer{
private:
	string trn;
	string lastName;
	string address;
	string phoneNumber;
	int creditBalance;
public:

	Customer(){
		trn = "null";
		lastName = "null";
		address = "null";
		phoneNumber = "null";
		creditBalance = 100;
	}

	Customer(string trn,string lastName,string address,
				string phoneNumber,int creditBalance ){
		this->trn = trn;
		this->lastName = lastName;
		this->address = address;
		this->phoneNumber = phoneNumber;
		this->creditBalance = creditBalance;
	}

	void addCredit(int credit){
		creditBalance += credit;
		cout << "\nCredit Added\n" << endl;
	}

	void checkBalance(){
		cout << lastName << "'s"<< " Credit Balance is: " << creditBalance << "\n"<< endl;
	}

	void setTrn(string trn){
		this->trn = trn; 
	}

	string getTrn(){
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
};


#endif

