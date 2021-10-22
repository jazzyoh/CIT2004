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
	void setCustomer(Customer customer){
		this->customer = customer;
	}


	void setParentCompany(string parentCompany){
		  this->parentCompany = parentCompany;
	}

	 string getParentCompany(){
		  return parentCompany;
	 }

	 void addCustomer(){// Save to a file
	 	string detailBuffer;
		const string prefix[4] = {"601","602","603","604"};
		try{
				cout << "Enter Customer Infromation:\n "<< endl;
				cout << "Enter Trn: " ;
				getline(cin,detailBuffer);
				cout << "\n";
				customer.setTrn(detailBuffer);
				cout << "\n";
				cout << "Enter Last Name: ";
				cout << "\n";
				getline(cin,detailBuffer);
				customer.setLastName(detailBuffer);

				if(cin.fail()){
					throw runtime_error("There was an input error");
				}

				cout << "\nEnter Customer Address: " << endl;
				getline(cin,detailBuffer);
				customer.setAddress(detailBuffer);

				if(cin.fail()){
					throw runtime_error("There was an input error");
				}

				cout << "\nEnter Customer Number \nImportant Details\n"<<
								"Area Code (876)\nPrefix (601,602,603,604): " ;
				getline(cin,detailBuffer);

				if(detailBuffer.length()!= 10 ){ //First checking the length,then the areacode then the prefix
					throw runtime_error("Not a valid phone number");
				}else if(detailBuffer.substr(0,3) != "876"){
					throw runtime_error("Areacode not registered") ;
					}else if(detailBuffer.substr(3,3)!=prefix[0] && detailBuffer.substr(3,3)!=prefix[1] && 
								detailBuffer.substr(3,3)!=prefix[2] && detailBuffer.substr(3,3)!=prefix[3]){
						throw runtime_error("Prefix not registered");
					}
				else{
					customer.setPhoneNumber(detailBuffer);
				}
		}catch(runtime_error &err){
				cerr << err.what() << endl;
				throw;
		}catch(...){
				cerr << "A fatal error has occurred" << endl;
				throw;
		}
	customer.setCreditBalance(100);
	saveCustomerDetails();
	cout << "Customer Account was created and $100 was added" << endl;
	
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
	
	void findCustomer(string search){
		ifstream readFileStream;
		string buffer(NULL);
		int creditBuffer;
		readFileStream.open("Flow_Customers",ios::in);
		
		while(!readFileStream.eof()){
			readFileStream >> buffer;
			customer.setTrn(buffer);
			readFileStream >> buffer;
			customer.setLastName(buffer);
			readFileStream >> buffer;
			customer.setAddress(buffer);
			readFileStream >> buffer;
			customer.setPhoneNumber(buffer);
			readFileStream >> creditBuffer; 
			customer.setCreditBalance(creditBuffer);
			if(buffer == search){
				customer.setTrn(buffer);
				
			setCustomer(customer);
			}
		}
	}
		




};
#endif
