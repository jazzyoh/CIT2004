#include <iostream>
#include "ServiceProvider.h"
#include "Flow.h"

using namespace std;

int main(){
	
	 Flow flow;
	
	 flow.createPhoneCard();
	 flow.addCustomer();
	 flow.createPhoneCard();
	 
	 return 0;
}
