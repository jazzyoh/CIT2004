/*
#ifndef  DIGICEL_H
#define  DIGICEL_H

#include <iostream>

#include "ServiceProvider.h"

using namespace std;

class Digicel :public ServiceProvider{
private:
	 int branchNumber;
	 const string prefix[4] =  {"301","302","303","304"};
public:
	 Digicel(){
		  this->branchNumber = 0;
	 }

	 Digicel(int branchNumber){
		  this->branchNumber = branchNumber;
	 }

	 void addCustomer(){// Save to a file
		  ServiceProvider::addCustomer();
		  cout << "Enter Customer Infromation:\n "<< endl;
		  cout << "Enter Last Name: "<< endl;
		  getline(cin,lastName);

		  cout << "\nEnter Customer Address: " << endl;
		  getline(cin,clientAddress);
		  try{
				cout << "\nEnter Customer Number \nImportant Details\n"<<
								"Area Code (876)\nPrefix (601,602,603,604): " ;
					getline(cin,customerNumber);
					if(customerNumber.length()!= 10 ){
						  throw runtime_error("Not a valid phone number");
					 }else if(customerNumber.substr(0,3) != "876"){
						  throw runtime_error("Areacode not registered") ;
					}else if(customerNumber.substr(3,3)!=prefix[0] && customerNumber.substr(3,3)!=prefix[1] && 
								customerNumber.substr(3,3)!=prefix[2] && customerNumber.substr(3,3)!=prefix[3]){
						  throw runtime_error("Prefix not registered");
					}else{
						 customerBalance += 100;
					 	 cout << "Customer Account was created and $100 was added" << endl;
					}


		  }catch(runtime_error &err){
				cerr << err.what() << endl;
		  }catch(...){
				cerr << "A fatal error has occurred" << endl;
		  }
		   	 }



};
#endif
*/
