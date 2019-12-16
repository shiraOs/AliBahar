#include <iostream>
using namespace std;

class Costumer;
class vendor;


#pragma warning (disable: 4996)

void printOptions();														//print menu

void addCostumer(Costumer** allCostumers, int* costumerSize);				//option 1 from main
void addVendor(vendor** allVendors, int* vendorsSize);						//option 2 from main
void addPdtToVdr(vendor** allVendors, int vendorSize);						//option 3 from main
void addFeedback(Costumer** allCostumers, int costumerSize, vendor** allVendors, int vendorsSize);				//option 4 from main
void addProductToShoppingCart(Costumer** allCostumers, int costumerSize, vendor** allVendors, int vendorSize);	//option 5 from main
void addOrderToPendingOrders(Costumer** allCostumers, int costumerSize);										//option 6 from main
void payOrder(Costumer** allCostumers, int costumerSize);					//option 7 from main
void showCostumersDetails(Costumer** allCostumers, int costumerSize);		//option 8 from main
void showVendorsDetails(vendor** allVendors, int vendorSize);				//option 9 from main
void showProductsByName(vendor** allVendors, int vendorSize);				//option 10 from main


//void addOrderToPenOrders(const Order& newOrder, Costumer* currCostumer);
//void addProductToOrder(const Order* CurrOrder, const product* newProduct);





