#ifndef  SERVICEPROVIDER_H
#define  SERVICEPROVIDER_H

#include <iostream>
#include <random>
#include <string>
#include <fstream>

using namespace std;

class ServiceProvider{

private:
	string companyId;
	string companyAddress;
	string clientAddress;
	static int totalNoCustomer;
	string trn;
	string lastName;
	string creditNumber;
	string password;
	string prefix;

protected:
	string customerNumber;
public:

	ServiceProvider(){
		companyId = "null";
		companyAddress = "null";
		clientAddress = "null";
		trn = "string";
		lastName = "null";
		creditNumber = "null";
		password = "null";
		prefix = "null";
		totalNoCustomer+=1;
	}

	ServiceProvider(string companyId,string companyAddress,string clientAddress, string trn,string lastName
							,string creditNumber,string password,string prefix,int totalNoCustomer){
		this->companyAddress = companyId;
		this->clientAddress = clientAddress;
		this->trn = trn;
		this->lastName = lastName;
		this->creditNumber = creditNumber;
		this->password = password;
		this->prefix = prefix;
		this->totalNoCustomer = totalNoCustomer;

	}

	void viewCompanyInfo(){ //This should be Overridden
		cout << "Company Information \n"<< endl;
	}
	
	void addCustomer(string trn,string lastName,string clientAddress){
		this->trn = trn;
		this->lastName = lastName;
		this->clientAddress = clientAddress;
	}

	void viewCustomerBase(){ //This should be Overridden
		ifstream readfileStream;
	}

	void createPhoneCard(){
		string buffer;
		int hold;
		random_device rand; //Getting a random number
		mt19937 generate(rand()); //Random number generator 
		uniform_int_distribution<> distribution(0,9); //random number range definition

		for(int i=0;i <=12;i++){
			hold = (distribution(generate)); //assigning random number to hold
			buffer += to_string(hold); //type casting hold to string and storing it in buffer
		}

		cout <<"\n\n" << endl;
		this->creditNumber = buffer;
			cout << "New Phone Card is: " << this->creditNumber << "\n\n" <<endl;
	}

	int viewTotalNumberOfCustomer(){//Could be overridden or maybe it should how all customers
		cout <<"Total Number of Customers: are\n\n"<< endl;
		return this->totalNoCustomer;
	}

	void viewAllPhoneCredit(){ //This should be Overridden // should be reading from file
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

	void setClientAddress(string clientAddress){
		this->clientAddress = clientAddress;
	}

	string getClientAddress(){
		return clientAddress;
	}

	void setTrn(string trn){
		this->trn = trn;
	}

	string getTrn(){
		return trn;
	}

	void setPrefix(string prefix){
		this->prefix = prefix;
	}

	string getPrefix(){
		return prefix;
	}
	~ServiceProvider();
};

int ServiceProvider::totalNoCustomer = 0;



#endif
