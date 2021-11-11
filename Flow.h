#ifndef  FLOW_H
#define  FLOW_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include "ServiceProvider.h"

using namespace std;
namespace fs = filesystem;

class Flow :public ServiceProvider{
private:
	string parentCompany;
public:
	Flow():ServiceProvider(){
		this->parentCompany = "null";
	}

	Flow(string parentCompany):ServiceProvider(){
		this->parentCompany =  parentCompany;
	}

	void setParentCompany(string parentCompany){
		this->parentCompany = parentCompany;
	}

	string getParentCompany(){
		return parentCompany;
	}

	void addCustomer(){
		int trnBuffer;
		string detailBuffer;
		string addressBuffer ;
		string phoneBuffer;
		try{
			cout << "\nEnter Customer Infromation:\n "<< endl;
			cout << "\nEnter Trn: " ;
			cin >>trnBuffer;
			if(cin.fail()){
				throw runtime_error("There was an input error");
			}
			customer.setTrn(trnBuffer);
			cout << "\nEnter Last Name: ";
			cin >> detailBuffer;
			if(cin.fail()){
				throw runtime_error("There was an input error");
			}
			customer.setLastName(detailBuffer);
			cout << "\nEnter Customer Address: ";
			cin.ignore(); //doesnt work otherwise 
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
		ServiceProvider::customer.incrementCustomer();
		cout << "Customer Account was created and $100 was added" << endl;
	}

	void setCustomer(Customer customer){
		this->customer = customer;
	}

	bool createCustomerFile(ofstream *fileStream){
		Customer *customerObj = new Customer;
		try{
			fileStream = new ofstream("Flow_Customers",ios::out | ios::app | ios::binary);		
			if(fileStream->fail())
				throw runtime_error("Couldn not create database\n");
			for(int i =0;i<=MAX; i++){
				fileStream->seekp((i-1)* sizeof(Customer));
				fileStream->write(reinterpret_cast <const char *> (customerObj),sizeof(Customer));
			}
		}catch(runtime_error &err){
			return false;
		}
		fileStream->close();
		return true;
	}

	void saveCustomerDetails(){
		ofstream *fileStream;
		Customer *customerObj = new Customer;
		fileStream = new ofstream("Flow_Customers",ios::out|ios::app|ios::binary);

		if(createCustomerFile(fileStream)){
			fileStream->seekp(customer.getTrn()-1*sizeof(Customer));
			fileStream->write(reinterpret_cast<const char *> (&customerObj),sizeof(Customer));
			fileStream->close();
		}
	}

	void createPhoneCard(){
		ServiceProvider::createPhoneCard();
		saveCardTopUpDetails();
	}

	void saveCardTopUpDetails(){
		ofstream writeFileStream;
		writeFileStream.open("Flow_CardInformation",ios::app);
		writeFileStream << creditCard << endl;
		writeFileStream.close();
		cout << "\n\nCard Infromation Saved\n"<<endl; 
	}
	
	bool findCustomer(string search){
		ifstream readFileStream;
		string nameBuffer;
		int trnBuffer;
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
				readFileStream.close();
				return true;
			}
		}
		customer.setAddress("null");
		customer.setCreditBalance(0);
		customer.setLastName("null");
		customer.setPhoneNumber("null");
		customer.setTrn(0);
		readFileStream.close();
		return  false;
	}

	void addCredit(){//Note When updating the card the denomiation is either the last 3 or 4 digits of the card number 
		const string sign="*121*";
		string number;
		//012345678901234567890123456789
		//*121*1234567890987*8766011234#
		try{
			cout << "\n\nEnter Credit Number\n" <<
					"Important Details\n" <<
					"*121*[card number]*[phone number]#: ";
			cin >> number;

			if(cin.fail()){
				throw runtime_error("\nValue not Expected\n");
			}else if(number.length()!=30){
				throw runtime_error("Invaild Input\n\nPlease Follow Outline\n");
			}else if(number.substr(0,5)!= sign){
				cout << number.substr(0,5);
				throw runtime_error("\nIncorrect Sign\n");
			}else if(findCard(number.substr(5,13)) == false && number.substr(18,1) == "*"){
				throw runtime_error("\nCard Not Valid\n");
			}else if(findCustomer(number.substr(19,10)) == false){
				throw runtime_error("\nCustomer Number not found\n");
			}else if (number.substr(29,1) != "#"){
				throw runtime_error("# Expected at the end ");
			}

		}catch(runtime_error &err){
			cerr << err.what() << endl;
		}catch(...){
			cerr << "A fatal error has occurred "<< endl;
		}

		if(creditCard.substr(7,1) == "0"){
			customer.addCredit(1000);
		}else if (creditCard.substr(7,1) == "1"){
			customer.addCredit(100);
		}else if (creditCard.substr(7,1) == "2"){
			customer.addCredit(200);
		}else if (creditCard.substr(7,1) == "5"){
			customer.addCredit(500);
		}
		//updateCustomerInfromation
	}

	bool findCard(string findCardNumber){
		ifstream	readFileStream;
		string cardStatus;
		readFileStream.open("Flow_CardInformation",ios::in);

		while(!readFileStream.eof()){
			readFileStream >> creditCard;
			readFileStream >> cardStatus;
		
			if((findCardNumber == creditCard) && (cardStatus != "Used")){
				readFileStream.close();
				//updateCardInfo(creditCard)
				return true;
			}
		}
		creditCard = '0';
		readFileStream.close();
		return false;
	}

	bool checkPhoneNumber(string phoneBuffer){
		const string prefix[4] = {"601","602","603","604"};
	
		try{//8766011234
			if(phoneBuffer.length()!= 10 ){ //First checking the length,then the areacode then the prefix
				throw runtime_error("Not a valid phone number");
			}else if(phoneBuffer.substr(0,3) != "876"){
				throw runtime_error("Areacode not registered") ;
				}else if(phoneBuffer.substr(3,3)!=prefix[0] && phoneBuffer.substr(3,3)!=prefix[1] && 
							phoneBuffer.substr(3,3)!=prefix[2] && phoneBuffer.substr(3,3)!=prefix[3]){
					throw runtime_error("Prefix not registered");
				}
		}catch(runtime_error &err){
			return false;		
		}catch(...){
				cerr << "A fatal error has occurred" << endl;
		}
		return true;
	}

	bool login(string usrPass){
		const string password = "TheWayIFlow2021";

		if(usrPass == password){
			return true;
		}else{
			return false;
		}
	}

	void viewCustomerBase(){
		ifstream fileStream;
		string customerBuffer;
		try{
			fileStream.open("Flow_Customers",ios::in);
			if(fileStream.fail()){
				throw runtime_error ("Unable to open Database") ;
			}
			while(!fileStream.eof()){
				fileStream >> customerBuffer;
				cout << customerBuffer << " ";
				fileStream >> customerBuffer;
				cout << customerBuffer << " ";
				fileStream >> customerBuffer;
				cout << customerBuffer << " ";
				fileStream >> customerBuffer;
				cout << customerBuffer << " ";
				fileStream >> customerBuffer;
				cout << "\n";
			}
			fileStream.close();
		}catch(runtime_error &err){
			fileStream.close();
			cout<< err.what() <<endl;
		}catch(...){
			fileStream.close();
			cerr << "An unexpected error has occurred \n"<< endl;
		}
	}

	void viewAllPhoneCredit(){
		ifstream fileStream;
		string customerBuffer;
		try{
			fileStream.open("Flow_Customers",ios::in);
			if(fileStream.fail()){
				throw runtime_error ("Unable to open Database") ;
			}
			while(!fileStream.eof()){
				fileStream >> customerBuffer;
				cout << customerBuffer << "  ";
				fileStream >> customerBuffer;
				cout << customerBuffer << "  ";
				cout << "\n";
			}
			fileStream.close();
		}catch(runtime_error &err){
			fileStream.close();
			cout<< err.what() <<endl;
		}catch(...){
			fileStream.close();
			cerr << "An unexpected error has occurred \n"<< endl;
		}
	}
	
	void updateCustomerInfromation(){

		//Notice we should use a binary file to write and read customer and caard infromation 
		//we need to indec the number of customers  and use that as a primary key eck tool
		//to identfy the customer  this woull makke it easier checking the files  because
		//if u look at the question sheet we need to display the total number of customer from bother service providers
		//we arnt allowed to save the number of customers in the file directly so this would be a good workaround
		//and also we coulse associate the same number of the cutomer to the respective card info.
		//
	}

	void dispay(){
		ServiceProvider::display();
		cout << "\nParent Company: " <<  parentCompany;
	}

};
#endif
