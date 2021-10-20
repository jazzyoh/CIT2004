#ifndef  SERVICEPROVIDER_H
#define  SERVICEPROVIDER_H

#include <iostream>
#include <random>
#include <string>
#include "Customer.h"

using namespace std;

class ServiceProvider: public exception{

private:
	string companyId;
	string companyAddress;
	static int totalNoCustomer;
	string password;	
protected:
	Customer customer;
	string creditCard;
public:

	ServiceProvider(){
		companyId = "null";
		companyAddress = "null";
		password = "null";
		totalNoCustomer+=1;
	}

	ServiceProvider(string companyId,string companyAddress,string password, int totalNoCustomer, Customer *_customer){
		this->companyAddress = companyId;
		this->password = password;
		this->totalNoCustomer = totalNoCustomer;
	}

	virtual void viewCompanyInfo(){ //This should be Overridden
	}
	
	virtual void addCustomer(){//This should be Overridden
	}

	virtual void viewCustomerBase(){ //This should be Overridden
	}

	void createPhoneCard(){
		string buffer;
		int hold,choice;
		const string demoniation[]={"100","200","500","1000"};
		const string status[] = {"Used","Available"} ;
		
		try{
			cout << "Create Phone Card\n\n" <<
						"Select Denomination:\n" <<
						"1 for $100\n" <<
						"2 for $200\n" <<
						"3 for $500\n" <<
						"4 for $1000\n" << endl;
			cin >> choice;
			if(cin.fail())
				throw runtime_error("Value not Expected");
			else if(choice != 1 && choice != 2 &&  choice != 3 && choice != 4 )
				throw -1;

		}catch(runtime_error &err){
			cerr << err.what() << endl;
		}catch(int &err){
			cerr << "Enter one of the values displayed\n" << endl;
		}catch(...){
			cerr << "A fatal error has occurred "<< endl;
			return;
		}
		int sentenel;
		if(choice == 4)
			sentenel=8;	
		else
			sentenel = 9;
		
		random_device rand; //Getting a random number
		mt19937 generate(rand()); //Random number generator 
		uniform_int_distribution<> distribution(0,9); //random number range definition

		for(int i=0;i <=sentenel;i++){
			hold = (distribution(generate)); //assigning random number to hold
			buffer += to_string(hold); //type casting hold to string and storing it in buffer
		}

		buffer += demoniation[choice-1];
		buffer+= ("\t"+status[1]);// Appending Status to credit number 
		cout <<"\n\n" << endl;
		this->creditCard = buffer;
		cout << "New Phone Card is: " << this->creditCard<<"\n\n" <<endl;	
		saveCardTopUpDetails();
	}

	int viewTotalNumberOfCustomer(){//Could be overridden or maybe it should show all customers from each base 
		cout <<"Total Number of Customers: are\n\n"<< endl;
		return this->totalNoCustomer;
	}

	virtual void viewAllPhoneCredit(){ //This should be Overridden // should be reading from file
		cout << "Displaying all Created Phone Credits\n" << endl;

	}

	void setPassword(string password){
		this->password = password;
	}

	string getPassword(){
		return password;
	}

	void setCompanyId(string companyId){
		this->companyId = companyId;
	}

	string getCompanyId(){
		return companyId;
	}

	void setComapnyAddress(string companyAddress){
		this->companyAddress = companyAddress;
	}
	
	string getComapnyAddress(){
		return companyAddress;
	}

	void saveCustomerDetails(){

	}

	void saveCardTopUpDetails(){

	}

//	void setPrefix(string prefix){
//		this->prefix = prefix;
//	}

//	string getPrefix(){
//		return prefix;
//	}
	~ServiceProvider(){};
};

int ServiceProvider::totalNoCustomer = 0;

#endif
