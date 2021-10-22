#include <iostream>
#include "ServiceProvider.h"
#include "Flow.h"

using namespace std;

int main(){
	
	string section;
	Flow *flow = new Flow();
	cout << "Admin" << endl;
	cout << "Customer" << endl;
	cin >> section;

	if(section == "admin"){
		cout << "Flow" << endl;
		cout << "Digicel" << endl;
		cin >>section;

		if(section == "Flow"){
		}

	}else if(section == "customer" ){
		cout << "add - Add Credit" << endl;
		cout << "check - Check Balance " << endl;
		cin >> section;

		if(section == "add"){
			flow->addCustomer();
		}else if (section == "check"){
			string search;
			cout << "Enter phone number " << endl;
			cin >> search;
			flow->findCustomer(search);
			cout << flow->getCustomerBalance() << "\n" << endl;
		}
	}
	return 0;
}
