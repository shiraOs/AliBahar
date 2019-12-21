#include <iostream>
using namespace std;

#pragma warning (disable: 4996)

class Costumer;
class vendor;
class product;
class feedback;

const int MAX_LEN = 20;
const int DATE_LEN = 11;	//date as "dd/mm/yyy/0"

void printOptions();														//print menu

void addCostumer(Costumer**& allCostumers, int* costumerSize);				//option 1 from main
void addVendor(vendor**& allVendors, int* vendorsSize);						//option 2 from main
void addPdtToVdr(vendor**& allVendors, int vendorSize);						//option 3 from main
void addFeedback(Costumer**& allCostumers, int costumerSize, vendor**& allVendors, int vendorsSize);				//option 4 from main
void addProductToShoppingCart(Costumer**& allCostumers, int costumerSize, vendor**& allVendors, int vendorSize);	//option 5 from main
void addOrderToPendingOrders(Costumer**& allCostumers, int costumerSize);	//option 6 from main
void payOrder(Costumer**& allCostumers, int costumerSize);					//option 7 from main
void showCostumersDetails(Costumer**& allCostumers, int costumerSize);		//option 8 from main
void showVendorsDetails(vendor**& allVendors, int vendorSize);				//option 9 from main
void showProductsByName(vendor**& allVendors, int vendorSize);	            //option 10 from main

Costumer* readCostumer();
vendor* readVendor();
product* readProduct(vendor**& allVendors, int vendorsSize, int vendorIdx);
feedback* readFeedback(Costumer& costumer, vendor& vendor);
//bool checkCategory(int category);
bool checkSerialNumber(vendor**& allvendors, int seriealNumber, int allVendorSize); //new sn





