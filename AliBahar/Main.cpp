#include "Costumer.h"
#include "Vendor.h"
#include "System.h"

void main()
{
	vendor** allVendors = nullptr;
	Costumer** allCostumers = nullptr;
	int vendorSize = 0, costumerSize = 0, option = 0;

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
		if (option == 8) { showCostumersDetails(allCostumers, costumerSize); }
		if (option == 9) { showVendorsDetails(allVendors, vendorSize); }
		if (option == 10) { showProductsByName(allVendors, vendorSize); }
		cout << endl << "********************************************" << endl;
	}
	if (option == 11) { freeMemory(allVendors, vendorSize, allCostumers, costumerSize); }
	system("pause");
}

