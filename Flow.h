#ifndef  FLOW_H
#define  FLOW_H

#include <iostream>

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
		ServiceProvider::addCustomer();
	 	string detailBuffer;
		const string prefix[4] =  {"601","602","603","604"};
		try{
				cout << "Enter Customer Infromation:\n "<< endl;
				cout << "Enter Last Name: "<< endl;
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

				if(detailBuffer.length()!= 10 ){
					throw runtime_error("Not a valid phone number");
				}else if(detailBuffer.substr(0,3) != "876"){
					throw runtime_error("Areacode not registered") ;
					}else if(detailBuffer.substr(3,3)!=prefix[0] && detailBuffer.substr(3,3)!=prefix[1] && 
								detailBuffer.substr(3,3)!=prefix[2] && detailBuffer.substr(3,3)!=prefix[3]){
						  throw runtime_error("Prefix not registered");
					}else{
						customer.setCreditBalance(100);
					 	cout << "Customer Account was created and $100 was added" << endl;
						saveCustomerDetails();
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
