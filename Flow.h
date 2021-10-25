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

	void addCustomer(){
		ServiceProvider::addCustomer();
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
		//ServiceProvider::totalNoCustomer++;
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

	void addCredit(){//Note When updating the card the denomiation is either the last 3 or 4 digits of the card number 
		const string sign="*121*";
		string number;
		//012345678901234567890123456789
		//*121*1234567890987*8766011234#
		try{
			cout << "\n\nEnter Credit Number\n" <<
					"Important Details\n" <<
					"*121*[card number]*[phone number]#: ";
			getline(cin,number);
			getline(cin,number);

			if(cin.fail()){
				throw runtime_error("\nValue not Expected\n");
			}else if(number.length()!=30){
				throw runtime_error("Invaild Input\n\nPlease Follow Outline\n");
			}else if(number.substr(0,5)!= sign){
				throw runtime_error("\nIncorrect Sign\n");
			}else if(findCard(number.substr(5,13)) == false){
				throw runtime_error("\nCard Not Valid\n");
			}else if(findCustomer(number.substr(19,10)) == false){
				throw runtime_error("\nCustomer Number not found\n");
			}else if (number.substr(29,0) != "#"){
				throw runtime_error("# Expected at the end ");
			}

		}catch(runtime_error &err){
			cerr << err.what() << endl;
		}catch(...){
			cerr << "A fatal error has occurred "<< endl;
		}

		if(creditCard.substr(7,0) == "0"){
			customer.addCredit(1000);
		}else if (creditCard.substr(7,0) == "1"){
			customer.addCredit(100);
		}else if (creditCard.substr(7,0) == "2"){
			customer.addCredit(200);
		}else if (creditCard.substr(7,0) == "5"){
			customer.addCredit(500);
		}
		//updateCustomer(number.substr(19,10))
	}

	bool findCard(string findCardNumber){
		ifstream	readFileStream;
		string cardStatus;
		readFileStream.open("Flow_CardInformation",ios::in);

		while(!readFileStream.eof()){
			readFileStream >> creditCard;
			readFileStream >> cardStatus;
		
			if((findCardNumber == creditCard) && (cardStatus != "Used")){
				//updateCardInfo(creditCard)
				return true;
			}
		}
		creditCard = '0';
		return false;
	}

	void checkPhoneNumber(string phoneBuffer){
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
					cerr << err.what() << endl;
					throw;
			}catch(...){
					cerr << "A fatal error has occurred" << endl;
					throw;
			}
	}

};
#endif
