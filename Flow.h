#ifndef  FLOW_H
#define  FLOW_H

#include <iostream>
#include <fstream>
#include "ServiceProvider.h"

using namespace std;

class Flow :public ServiceProvider{
private:
	 string parentCompany;
public:
	Flow(){
		this->parentCompany = "null";
	}

	Flow(string parentCompany){
		this->parentCompany =  parentCompany;
	}

	void setParentCompany(string parentCompany){
		this->parentCompany = parentCompany;
	}

	string getParentCompany(){
		return parentCompany;
	}

	void addCustomer(){// Save to a file
		string detailBuffer;
		string addressBuffer ;
		string phoneBuffer;
		try{
				cout << "\nEnter Customer Infromation:\n "<< endl;
				cout << "\nEnter Trn: " ;
				cin >>detailBuffer;
				if(cin.fail()){
					throw runtime_error("There was an input error");
				}

				customer.setTrn(detailBuffer);
				cout << "\nEnter Last Name: ";
				cin >> detailBuffer;
				if(cin.fail()){
					throw runtime_error("There was an input error");
				}
				customer.setLastName(detailBuffer);

				cout << "\nEnter Customer Address: ";
				getline(cin,addressBuffer); //doesnt work otherwise 
				getline(cin,addressBuffer);
				customer.setAddress(addressBuffer);
				if(cin.fail()){
					throw runtime_error("There was an input error");
				}

				cout << "\nEnter Customer Number \nImportant Details\n"<<
								"Area Code (876)\nPrefix (601,602,603,604): " ;
				getline(cin,phoneBuffer);
				
					checkPhoneNumber(phoneBuffer);

		}catch(runtime_error &err){
				cerr << err.what() << endl;
				throw;
		}catch(...){
				cerr << "A fatal error has occurred" << endl;
				throw;
		}
	customer.setPhoneNumber(phoneBuffer);
	customer.setCreditBalance(100);
	saveCustomerDetails();
	cout << "Customer Account was created and $100 was added" << endl;
	
}

	void setCustomer(Customer customer){
		this->customer = customer;
	}

	void saveCustomerDetails(){
		ofstream writeFileStream;
		writeFileStream.open("Flow_Customers",ios::app);

		writeFileStream << customer.getTrn() << "\t" <<customer.getLastName()
							<< "\t" << customer.getAddress() << "\t" << customer.getPhoneNumber() << "\t" 
							<< customer.getCreditBalance() << endl;;
		writeFileStream.close();
		cout << "\n\nCustomer Infromation Saved\n" << endl;
	}
	void createPhoneCard(){
		ServiceProvider::createPhoneCard();
		saveCardTopUpDetails();
	}

	void saveCardTopUpDetails(){
		ofstream writeFileStream;
		writeFileStream.open("Flow_CardInformation",ios::app);

		writeFileStream << creditCard << endl;
		cout << "\n\nCard Infromation Saved\n"<<endl; 
	}
	
	bool findCustomer(string search){
		ifstream readFileStream;
		string nameBuffer;
		string trnBuffer;
		string addressBuffer;
		string phoneBuffer;
		int creditBuffer;
		readFileStream.open("Flow_Customers",ios::in);
		
		while(!readFileStream.eof()){

			readFileStream >> trnBuffer;
			customer.setTrn(trnBuffer);
			readFileStream >> nameBuffer;
			customer.setLastName(nameBuffer);
			readFileStream >> addressBuffer;
			customer.setAddress(addressBuffer);
			readFileStream >> phoneBuffer;
			customer.setPhoneNumber(phoneBuffer);
			readFileStream >> creditBuffer; 
			customer.setCreditBalance(creditBuffer);
			if(phoneBuffer == search){
				cout  << "\nCustomer Found\n" << endl;
				return true;
			}
		}
		customer.setAddress("null");
		customer.setCreditBalance(0);
		customer.setLastName("null");
		customer.setPhoneNumber("null");
		customer.setTrn("null");
		return  false;
	}

	void addCredit(){
		const string sign="*121*";
		string number;
		string delimiter = "*";

		cout << "\n\nEnter Credit Number\n" <<
				"Important Details\n" <<
				"*121*[card number]*[phone number]#: ";
		getline(cin,number);
		
		for(int i = 0; true ; i++){
			number.substr(i,number.find(delimiter));

		}
		

	}

	void checkPhoneNumber(string phoneBuffer){
		const string prefix[4] = {"601","602","603","604"};
	
		try{
			if(phoneBuffer.length()!= 10 ){ //First checking the length,then the areacode then the prefix
				throw runtime_error("Not a valid phone number");
			}else if(phoneBuffer.substr(0,3) != "876"){
				throw runtime_error("Areacode not registered") ;
				}else if(phoneBuffer.substr(3,3)!=prefix[0] && phoneBuffer.substr(3,3)!=prefix[1] && 
							phoneBuffer.substr(3,3)!=prefix[2] && phoneBuffer.substr(3,3)!=prefix[3]){
					throw runtime_error("Prefix not registered");
				}
			}catch(runtime_error &err){
					cerr << err.what() << endl;
					throw;
			}catch(...){
					cerr << "A fatal error has occurred" << endl;
					throw;
			}
	}

};
#endif
