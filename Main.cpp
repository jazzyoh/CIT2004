#include <iostream>
#include <string.h>
#include "ServiceProvider.h"
#include "Flow.h"
//#include "Digicel.h"
using namespace std;

int main(){

	string section;

	ServiceProvider *serviceProvider;
	
	serviceProvider = new Flow();
	//string usrPass;	
	//cout <<"Enter PassWord: ";
	//cin >> usrPass;
	//serviceProvider->login(usrPass);
	//serviceProvider->addCredit();
	serviceProvider->addCustomer();
	serviceProvider->display();
	serviceProvider->createPhoneCard();
	serviceProvider->viewCustomerBase();
	serviceProvider->viewAllPhoneCredit();


	/*	//Digicel *digicel = new Digicel();
	cout << "Welcome"<< endl;
	cout << "admin - Admin" << endl;
	cout << "customer - Customer" << endl; //Needs error handling 
	cin >> section;


	if(section == "admin"){				//Needs error handling
		cout << "flow - Flow" << endl;
		cout << "digicel - Digicel" << endl;
		cin >>section;

		do{
			 if(section == "flow"){ //Needs error handling 
				serviceProvider = new Flow();
				string usrPass;
				cout << "Please Enter The Password: ";
				cin >> usrPass;
				if(serviceProvider->login(usrPass)){
					cout << "add -Add customer\n" << endl;
					cout << "create - Create Phone Card\n" <<endl;
					cin >>section;

					if(section == "add"){
						 serviceProvider->addCustomer();
					}else if(section == "create"){
						serviceProvider->createPhoneCard();
					}
				}
			 }else{
				cout << "Incorrect Password ";
			 }
		}while(true); 
	}
	else if(section == "customer" ){//Needs error handling 
		cout << "add - Add Credit" << endl;
		cout << "check - Check Balance " << endl;
		cin >> section;

		if(section == "add"){
			serviceProvider->addCredit(); // Update Is not working 
		
		}else if (section == "check"){ //Needs error handling
			string search;
			cout << "Enter phone number " << endl;
			cin >> search;

			if(serviceProvider->findCustomer(search) == true){
				cout << serviceProvider->getCustomerName() <<"'s " << "Balance is: " <<  serviceProvider->getCustomerBalance() << "\n" << endl;
			}
			else{
				cerr << "\nCustomer not Found\n" << endl;
			}
		}
	}*/
	return 0;
}
