#include "Vendor.h"
#include "Product.h"
#include "Costumer.h"

void printOptions();

void main()
{
	vendor** allVendors;
	Costumer** allCostumers;
	int vendorSize =1 , costumerSize = 1, option = 0;
	allCostumers = new Costumer*[costumerSize];
	allVendors = new vendor*[vendorSize];


	while (option != 11)
	{
		printOptions();
		cin >> option;
		
		if (option == 1) { addCostumer(allCostumers, &costumerSize); }	
		if (option == 2) { addVendor(allVendors, &vendorSize); }
		if (option == 3) { addPdtToVdr(allVendors, vendorSize); }
		if (option == 4) { addFeedback(allCostumers, costumerSize, allVendors, vendorSize); }
		if (option == 5) { addProductToShoppingCart(allCostumers, costumerSize, allVendors, vendorSize); }
		if (option == 6) { addOrderToPendingOrders(allCostumers, costumerSize); }
		if (option == 7) { payOrder(allCostumers, costumerSize); }
		//if (option == 8);
		//if (option == 9);
		//if (option == 10);
		//if (option == 11);
	}

}

void printOptions()
{
	cout << "What would you like to do?\n";
	cout << "Add costumer - press 1\nAdd vendor - press2\nAdd product to vendor - press"
		" 3\nAdd feedback to vendor - press 4\nAdd product to shopping cart - press 5\nAdd"
		" order to costumer - press 6\nPayment for order - press 7\nShow all costumers"
		" - press 8\nShow all vendors - press 9\nShow all products by name - press 10\n"
		"EXIT - press 11\n";
}

