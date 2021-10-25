#include <iostream>
#include "ServiceProvider.h"
#include "Flow.h"

using namespace std;

int main(){
	
	string section;
	Flow *flow = new Flow();
	//Digicel *digicel = new Digicel();
	
	cout << "admin - Admin" << endl;
	cout << "customer - Customer" << endl; //Needs error handling 
	cin >> section;

	if(section == "admin"){				//Needs error handling
		cout << "flow - Flow" << endl;
		cout << "digicel - Digicel" << endl;
		cin >>section;

		if(section == "flow"){ //Needs error handling 
			cout << "add -Add customer\n" << endl;
			cout << "create - Create Phone Card\n" <<endl;
			cin >>section;
			
			if(section == "add"){
				flow->addCustomer();
			}else if(section == "create"){
				flow->createPhoneCard();
			}
		}
	}
	else if(section == "customer" ){//Needs error handling 
		cout << "add - Add Credit" << endl;
		cout << "check - Check Balance " << endl;
		cin >> section;

		if(section == "add"){
			flow->addCredit(); // Update Is not working 
		
		}else if (section == "check"){ //Needs error handling
			string search;
			cout << "Enter phone number " << endl;
			cin >> search;

			if(flow->findCustomer(search) == true){
				cout << flow->getCustomerName() <<"'s " << "Balance is: " <<  flow->getCustomerBalance() << "\n" << endl;
			}
			else{
				cerr << "\nCustomer not Found\n" << endl;
			}
		}
	}
	return 0;
}
