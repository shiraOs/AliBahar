#include <iostream>
using namespace std;

#pragma warning (disable: 4996)

class Costumer;
class vendor;
class product;
class feedback;

const int MAX_LEN = 20;
const int DATE_LEN = 11;	//date as "dd/mm/yyy/0"
const int MAX_FEED = 100;

//print menu
void printOptions();														

//option 1 from main
void addCostumer(Costumer**& allCostumers, int* costumerSize);				
Costumer* readCostumer(Costumer**& allCostumers, int size);

//option 2 from main
void addVendor(vendor**& allVendors, int* vendorsSize);						
vendor* readVendor(vendor**& allVendors, int size);

//option 3 from main
void addPdtToVdr(vendor**& allVendors, int vendorSize);						
product* readProduct(vendor**& allVendors, int vendorsSize, int vendorIdx);
bool checkSerialNumber(vendor**& allvendors, int seriealNumber, int allVendorSize);

//option 4 from main
void addFeedback(Costumer**& allCostumers, int costumerSize, vendor**& allVendors, int vendorsSize);
feedback* readFeedback(Costumer& costumer, vendor& vendor);

//option 5 from main
void addProductToShoppingCart(Costumer**& allCostumers, int costumerSize, vendor**& allVendors, int vendorSize);

//option 6 from main
void addOrderToPendingOrders(Costumer**& allCostumers, int costumerSize);	

//option 7 from main
void payOrder(Costumer**& allCostumers, int costumerSize);					

//option 8 from main
void showCostumersDetails(Costumer**& allCostumers, int costumerSize);		

//option 9 from main
void showVendorsDetails(vendor**& allVendors, int vendorSize);				

//option 10 from main
void showProductsByName(vendor**& allVendors, int vendorSize);	           

//free memory allocation
void freeMemory(vendor**& allVendors, int vendorSize, Costumer**& allCostumers, int costumerSize);





