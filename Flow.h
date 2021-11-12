#ifndef  FLOW_H
#define  FLOW_H
#define MAX 256

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include "ServiceProvider.h"

using namespace std;

class Flow :public ServiceProvider {
private:
	string parentCompany;
public:
	Flow() {
		this->parentCompany = "null";
	}

	Flow(string parentCompany) {
		this->parentCompany = parentCompany;
	}

	void setParentCompany(string parentCompany) {
		this->parentCompany = parentCompany;
	}

	string getParentCompany() {
		return parentCompany;
	}

	void addCustomer() {
		int trnBuffer;
		string detailBuffer;
		string addressBuffer;
		string phoneBuffer;
		try {
			cout << "\nEnter Customer Infromation:\n " << endl;
			cout << "\nEnter Trn: ";
			cin >> trnBuffer;
			if (cin.fail()) {
				throw runtime_error("There was an input error");
			}
			customer.setTrn(trnBuffer);
			cout << "\nEnter Last Name: ";
			cin >> detailBuffer;
			if (cin.fail()) {
				throw runtime_error("There was an input error");
			}
			customer.setLastName(detailBuffer);
			cout << "\nEnter Customer Address: ";
			cin.ignore(); //doesnt work otherwise 
			getline(cin, addressBuffer);
			customer.setAddress(addressBuffer);
			if (cin.fail()) {
				throw runtime_error("There was an input error");
			}
			A:
			cout << "\nEnter Customer Number \nImportant Details\n" <<
				"Area Code (876)\nPrefix (601,602,603,604): ";
			getline(cin, phoneBuffer);
			try {
				checkPhoneNumber(phoneBuffer);
			}
			catch (...) {
				goto A;
			}
		}
		catch (runtime_error& err) {
			cerr << err.what() << endl;
			throw;
		}
		catch (...) {
			cerr << "A fatal error has occurred" << endl;
			throw;
		}
		customer.setPhoneNumber(phoneBuffer);
		customer.setCreditBalance(100);
		saveCustomerDetails();
		ServiceProvider::customer.incrementCustomer();
		cout << "Customer Account was created and $100 was added" << endl;

	}

	void setCustomer(Customer customer) {
		this->customer = customer;
	}

	void saveCustomerDetails() {

		/*fstream fileStream;
		try {
			fileStream.open("Flow_Customers", ios::in | ios::out | ios::app | ios::binary);
			if (fileStream.fail())
				throw runtime_error("Couldn not create database\n");
			for (int i = 0;i <= MAX; i++) {
				fileStream.seekp((i - 1) * sizeof(Customer));
				fileStream.write(reinterpret_cast <const char*> (&customer), sizeof(customer));
			}
			fileStream.close();
		}
		catch (runtime_error& err) {
			cerr << err.what() << endl;
		}
		fileStream.seekp(customer.getTrn() - 1 * sizeof(customer));
		fileStream.write(reinterpret_cast<const char*> (&customer), sizeof(customer));
		*/
	
		ofstream writeFileStream;
		writeFileStream.open("Flow_Customers",ios::out | ios::app);
		writeFileStream << customer.getTrn() << "\t" <<customer.getLastName()
							<< "\t" << customer.getAddress() << "\t" << customer.getPhoneNumber() << "\t"
							<< customer.getCreditBalance() << endl;;
		writeFileStream.close();
		cout << "\n\nCustomer Infromation Saved\n" << endl;
	}

	void createPhoneCard() {
		ServiceProvider::createPhoneCard();
		//saveCardTopUpDetails(); //*121*6929555306200*8766025655#
	}

	void saveCardTopUpDetails() {
		ofstream writeFileStream;
		writeFileStream.open("Flow_CardInformation", ios::out | ios::app);
		writeFileStream << ServiceProvider::creditCard << endl;
		writeFileStream.close();
		cout << "\n\nCard Infromation Saved\n" << endl;
	}

	bool findCustomer(string search) {
		ifstream readFileStream;
		string nameBuffer;
		int trnBuffer;
		string addressBuffer;
		string phoneBuffer;
		int creditBuffer;
		readFileStream.open("Flow_Customers", ios::in);

		while (!readFileStream.eof()) {
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
			if (phoneBuffer == search) {
				return true;
			}
		}
		customer.setAddress("null");
		customer.setCreditBalance(0);
		customer.setLastName("null");
		customer.setPhoneNumber("null");
		customer.setTrn(0);
		return  false;
	}

	void addCredit() {//Note When updating the card the denomiation is either the last 3 or 4 digits of the card number 
		const string sign = "*121*";
		string number;
		//012345678901234567890123456789
		//*121*1234567890987*8766011234#
		try {
			cout << "\n\nEnter Credit Number\n" <<
				"Important Details\n" <<
				"*121*[card number]*[phone number]#: ";
			cin >> number;

			if (cin.fail()) {
				throw runtime_error("\nValue not Expected\n");
			}
			else if (number.length() != 30) {
				throw runtime_error("Invaild Input\n\nPlease Follow Outline\n");
			}
			else if (number.substr(0, 5) != sign) {
				cout << number.substr(0, 5);
				throw runtime_error("\nIncorrect Sign\n");
			}
			else if (findCard(number.substr(5, 13)) == false && number.substr(18, 1) == "*") {
				throw runtime_error("\nCard Not Valid\n");
			}
			else if (findCustomer(number.substr(19, 10)) == false) {
				throw runtime_error("\nCustomer Number not found\n");
			}
			else if (number.substr(29, 1) != "#") {
				throw runtime_error("# Expected at the end ");
			}

		}
		catch (runtime_error& err) {
			cerr << err.what() << endl;
		}
		catch (...) {
			cerr << "A fatal error has occurred " << endl;
		}

		if (creditCard.substr(7, 1) == "0") {
			customer.addCredit(1000);
		}
		else if (creditCard.substr(7, 1) == "1") {
			customer.addCredit(100);
		}
		else if (creditCard.substr(7, 1) == "2") {
			customer.addCredit(200);
		}
		else if (creditCard.substr(7, 1) == "5") {
			customer.addCredit(500);
		}
		updateCustomerInfromation();
		//updateCardinfo(); change to USED
	}

	bool findCard(string findCardNumber) {
		ifstream	readFileStream;
		string cardStatus;
		readFileStream.open("Flow_CardInformation", ios::in);

		while (!readFileStream.eof()) {
			readFileStream >> creditCard;
			readFileStream >> cardStatus;

			if ((findCardNumber == creditCard) && (cardStatus != "Used")) {
				//updateCardInfo(creditCard)
				return true;
			}
		}
		creditCard = '0';
		return false;
	}

	void checkPhoneNumber(string phoneBuffer) {
		const string prefix[4] = { "601","602","603","604" };
		
		try {//8766011234
			if (phoneBuffer.length() != 10) { //First checking the length,then the areacode then the prefix
				throw runtime_error("Not a valid phone number");
			}
			else if (phoneBuffer.substr(0, 3) != "876") {
				throw runtime_error("Areacode not registered");
			}
			else if (phoneBuffer.substr(3, 3) != prefix[0] && phoneBuffer.substr(3, 3) != prefix[1] &&
				phoneBuffer.substr(3, 3) != prefix[2] && phoneBuffer.substr(3, 3) != prefix[3]) {
				throw runtime_error("Prefix not registered");
			}
		}
		catch (runtime_error& err) {
			cerr << err.what() << endl;
			throw;
		}
		catch (...) {
			cerr << "A fatal error has occurred" << endl;
		}
	}

	bool login(string usrPass) {
		const string password = "TheWayIFlow2021";

		if (usrPass == password) {
			return true;
		}
		else {
			return false;
		}
	}

	void viewCustomerBase() {
		ifstream fileStream;
		string customerBuffer;
		try {
			fileStream.open("Flow_Customers", ios::in);
			if (fileStream.fail()) {
				throw runtime_error("Unable to open Database");
			}
			while (!fileStream.eof()) {
				fileStream >> customerBuffer;
				cout << customerBuffer << "  ";
				fileStream >> customerBuffer;
				cout << customerBuffer << "  ";
				fileStream >> customerBuffer;
				cout << customerBuffer << "  ";
				fileStream >> customerBuffer;
				cout << customerBuffer << "  ";
				fileStream >> customerBuffer;
				cout << "\n";
			}
		}
		catch (runtime_error& err) {
			cout << err.what() << endl;
		}
		catch (...) {
			cerr << "An unexpected error has occurred \n" << endl;
		}
	}

	void viewAllPhoneCredit() {
		ifstream fileStream;
		string customerBuffer;
		try {
			fileStream.open("Flow_Customers", ios::in);
			if (fileStream.fail()) {
				throw runtime_error("Unable to open Database");
			}
			while (!fileStream.eof()) {
				fileStream >> customerBuffer;
				cout << customerBuffer << "  ";
				fileStream >> customerBuffer;
				cout << customerBuffer << "  ";
				cout << "\n";
			}

		}
		catch (runtime_error& err) {
			cout << err.what() << endl;
		}
		catch (...) {
			cerr << "An unexpected error has occurred \n" << endl;
		}
	}

	void updateCustomerInfromation() {
		try
		{
			//Read from file >> array of data >> delete file >> recreate file >> save array to it
			string PhoneNum[MAX], lastName[MAX], address[MAX];
			int creditBalance[MAX], trn[MAX], count = 0;
			fstream updateCustFileStream;
			
			updateCustFileStream.open("Flow_Customers", ios::in); //reading file
			if (updateCustFileStream.fail())
			{
				throw runtime_error("File cannot be not accessed.");
			}

			if (updateCustFileStream.is_open()) 
			{ 
				cout << "OPEN"; 
			} 
			else { 
				cout << "ERROR NOT OPEN"; 
			}

			for (int i = 0; i < MAX; i++)
			{
				++count;//keeps track of number of records read
				updateCustFileStream >> trn[i] >> lastName[i] >> address[i] >> PhoneNum[i] >> creditBalance[i];
				cout << trn[i] << " " << lastName[i] << " " << address[i] << " " << PhoneNum[i]
					<< " " << creditBalance[i] << endl;

				if (updateCustFileStream.eof()) {
					updateCustFileStream.close();
					break;
				}
			}

			int check;
			check = remove("Flow_Customers");
			//deleting file
			if(check==0)
			{
				cout << "File deleted successfully" << endl;
			}
			
			//creating new file
			updateCustFileStream.open("Flow_Customers", ios::out); //writing to new file, same name

			if (updateCustFileStream.fail())
			{
				throw runtime_error("File cannot be not accessed.");
			}

			for (int i = 0; i <= count; i++)
			{
				//updateCustFileStream << trn[i] << lastName[i] << address[i] << PhoneNum[i] << creditBalance[i];
				if (customer.getPhoneNumber() == PhoneNum[i])
				{
					creditBalance[i] += customer.getCreditBalance();
					cout << "New Credit Balance is: " << creditBalance[i] << endl;
				
					//actually updating...
					updateCustFileStream << trn[i] << "\t" << lastName[i] << "\t" 
						<< address[i] << "\t" << PhoneNum[i] << "\t" << creditBalance[i] << endl;

					cout << "File found and updated" << endl;
				}
				else
				{
					updateCustFileStream << trn[i] << "\t" << lastName[i] << "\t"
						<< address[i] << "\t" << PhoneNum[i] << "\t" << creditBalance[i] << endl;
				}
			}

			updateCustFileStream.close();

		}
		catch (...)
		{
			cerr << "Oh no, our code... its broken";
		}
	}

	int updateCardInfo(string creditCard)
	{

		try
		{
			//Read from file >> array of data >> delete file >> recreate file >> save array to it
			string creditcard[MAX];
			int count = 0;
			fstream updateCardInfoFileStream;

			updateCardInfoFileStream.open("Flow_CardInformation", ios::in); //reading file
			if (updateCardInfoFileStream.fail())
			{
				throw runtime_error("File cannot be not accessed.");
			}

			if (updateCardInfoFileStream.is_open())
			{
				cout << "OPEN";
			}
			else {
				cout << "ERROR NOT OPEN";
			}

			for (int i = 0; i < MAX; i++)
			{
				++count;//keeps track of number of records read
				updateCardInfoFileStream >> creditcard[i];
				cout << creditcard[i]<< endl;

				if (updateCardInfoFileStream.eof()) {
					updateCardInfoFileStream.close();
					break;
				}
			}

			int check;
			check = remove("Flow_CardInformation");
			//deleting file
			if (check == 0)
			{
				cout << "File deleted successfully" << endl;
			}

			//creating new file
			updateCardInfoFileStream.open("Flow_CardInformation", ios::out); //writing to new file, same name

			if (updateCardInfoFileStream.fail())
			{
				throw runtime_error("File cannot be not accessed.");
			}

			for (int i = 0; i <= count; i++)
			{
				if (ServiceProvider::creditCard == creditcard[i])
				{
					creditcard[i].substr(21, 9) = "Used";//changing status from available to used
					
					cout << "Checking Card Update...: " << creditcard[i] << endl;

					//actually updating...
					updateCardInfoFileStream << creditcard[i] << endl;

					cout << "File found and updated" << endl;
				}
				else
				{
					updateCardInfoFileStream << creditcard[i] << endl;
				}
			}

			updateCardInfoFileStream.close();

		}
			catch (...)
		{
			cerr << "Oh no, our code... its broken";
		}
	}

};
#endif
