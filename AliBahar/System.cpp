#include "System.h"
#include "Costumer.h"
#include "Feedback.h"
#include "Order.h"
#include "Product.h"
#include "Vendor.h"

void printOptions()
{
	cout << "What would you like to do? press number of desired option.\n";
	cout << "1. Add costumer\n2. Add vendor\n3. Add product to vendor"
		"\n4. Add feedback to vendor\n5. Add product to shopping cart\n6. Add"
		" order to costumer\n7. Payment for order\n8. Show all costumers"
		"\n9. Show all vendors\n10. Show all products by name\n"
		"11. EXIT\n";
}

void addCostumer(Costumer**& allCostumers, int* costumerSize)		//option 1 from main
{
	(*costumerSize)++;										//rise up the number of cotumers
	Costumer** temp = new Costumer*[(*costumerSize)];		//create new temp arr of costumers
	for (int i = 0; i < *costumerSize - 1; i++)
	{//copy the old arr
		temp[i] = allCostumers[i];
		allCostumers[i] = nullptr;
	}

	//create a pointer to new costumer
	temp[(*costumerSize) - 1] = readCostumer();
	delete[] allCostumers;									//free memory of old arr
	allCostumers = temp;									//put the new address to old arr
}

Costumer* readCostumer()
{
	char userName[MAX_LEN], password[MAX_LEN], state[MAX_ADD], city[MAX_ADD], street[MAX_ADD];
	int homeNum = 0, aptNum = 0;

	cin.ignore();
	cout << "Please enter costumer's username: maximum 20 chars" << endl;
	cin.getline(userName, MAX_LEN);

	cout << "Please enter costumer's password: maximum 20 chars" << endl;
	cin.getline(password, MAX_LEN);

	cout << "Please enter costumer's state: maximum 20 chars" << endl;
	cin.getline(state, MAX_LEN);

	cout << "Please enter costumer's city: maximum 20 chars" << endl;
	cin.getline(city, MAX_LEN);

	cout << "Please enter costumer's street: maximum 20 chars" << endl;
	cin.getline(street, MAX_LEN);

	while (homeNum < 1)
	{
		cout << "Please enter costumer's home number:" << endl;
		cin >> homeNum;
	}

	while (aptNum < 1)
	{
		cout << "Please enter costumer's apartment number:" << endl;
		cin >> aptNum;
	}

	return new Costumer(userName, password, address(state, city, street, homeNum, aptNum));
}

void addVendor(vendor**& allVendors, int * vendorsSize)		//option 2 from main
{
	(*vendorsSize)++;										//rise up the number of vendors
	vendor** temp = new vendor*[*vendorsSize];				//create new temp arr of vendors
	for (int i = 0; i < *vendorsSize - 1; i++)
	{//copy the old arr
		temp[i] = allVendors[i];
		allVendors[i] = nullptr;
	}

	//create a pointer to new vendor
	temp[(*vendorsSize) - 1] = readVendor();
	delete[] allVendors;									//free memory of old arr
	allVendors = temp;										//put the new address to old arr
}

vendor* readVendor()
{
	char userName[MAX_LEN], password[MAX_LEN], state[MAX_ADD], city[MAX_ADD], street[MAX_ADD];
	int homeNum = 0, aptNum = 0;

	cin.ignore();
	cout << "Please enter vendor's username: maximum 20 chars" << endl;
	cin.getline(userName, MAX_LEN);

	cout << "Please enter vendor's password: maximum 20 chars" << endl;
	cin.getline(password, MAX_LEN);

	cout << "Please enter vendor's state: maximum 20 chars" << endl;
	cin.getline(state, MAX_LEN);

	cout << "Please enter vendor's city: maximum 20 chars" << endl;
	cin.getline(city, MAX_LEN);

	cout << "Please enter vendor's street: maximum 20 chars" << endl;
	cin.getline(street, MAX_LEN);

	while (homeNum < 1)
	{
		cout << "Please enter vendor's home number:" << endl;
		cin >> homeNum;
	}

	while (aptNum < 1)
	{
		cout << "Please enter vendor's apartment number: " << endl;
		cin >> aptNum;
	}

	return new vendor(userName, password, address(state, city, street, homeNum, aptNum));
}

void addPdtToVdr(vendor**& allVendors, int vendorSize)		//option 3 from main
{//gets an arr of vendors and its size, search for the wanted vendor and then add a product to his list.
	int i = 0, flagVendor = 0;

	cout << "Press 1 to choose the curr vendor, or press 0 to the next one." << endl;
	while (!flagVendor && i < vendorSize)				//print every time vendor's name, if press 1 go out the loop. vendor num i-1
	{
		cout << "Vendor's name: " << allVendors[i]->getUserName() << endl;
		cin >> flagVendor;
		i++;
	}

	if (!flagVendor)
	{
		cout << "No vendor has been chosen. Return to main menu." << endl;
		return;
	}

	//create new pointer to a new product
	product* p = readProduct(allVendors, vendorSize, i - 1);
	allVendors[i - 1]->addProduct(*p);		//add the product to the list

}

product* readProduct(vendor**& allVendors, int vendorsSize, int vendorIdx)
{
	eCategory category;
	char pdtName[MAX_LEN];
	int c = 0, serialNumber = 0;
	double price = 0;

	cin.ignore();
	while (c > categoriesAmount || c < 1)
	{
		cout << "Enter product category:\n 1. Kids \n 2. Electricity \n 3. Office \n 4. Clothing" << endl;
		cin >> c;
	}
	category = (eCategory)c;

	cin.ignore();

	cout << "Enter product name: maximum 20 chars" << endl;
	cin.getline(pdtName, MAX_LEN);

	while (price < 1)
	{
		cout << "Enter product's price:" << endl;
		cin >> price;
	}

	do
	{
		cout << "Enter product's serial number:" << endl;
		cin >> serialNumber;
	} while (serialNumber < 1 || !checkSerialNumber(allVendors, serialNumber, vendorsSize));	//check if serial number valid

	return new product(category, pdtName, price, serialNumber, *(allVendors[vendorIdx]));
}

void addFeedback(Costumer**& allCostumers, int costumerSize, vendor**& allVendors, int vendorSize)	//option 4 from main
{//gets arr of costumers and its size, search for the wanted costumer, then choose the vendor and add a feedback
	int i = 0, flagCostumer = 0, j = 0, flagVendor = 0, v = 0;

	cout << "Press 1 to choose the curr costumer, or press 0 to the next one." << endl;
	while (!flagCostumer && i < costumerSize)
	{//print every time costumer's name, if press 1 go out the loop. costumer num i-1
		cout << "Costumer's name: " << allCostumers[i]->getUserName() << endl;
		cin >> flagCostumer;
		i++;
	}

	if (!flagCostumer)
	{
		cout << "Costumer DOES NOT exist in the system." << endl;
		return;
	}

	int vendorsAmount = allCostumers[i - 1]->getVendorsAmount();			//gets the amount of vendors in curr costumer
	const vendor** currVendors = allCostumers[i - 1]->getAllVendors();		//gets the list of vendors of curr costumer

	if (vendorsAmount == 0)
	{
		cout << "No vendors to feedback! return to menu." << endl;
		return;
	}

	cout << "Press 1 to choose the curr vendor, or press 0 to the next one." << endl;
	while (!flagVendor && j < vendorsAmount)
	{//print every time vendor's name, if press 1 go out the loop. vendor num j-1
		cout << "Vendor's name: " << currVendors[j]->getUserName() << endl;
		cin >> flagVendor;
		j++;
	}

	if (!flagVendor)
	{
		cout << "No vendor has been chosen. Return to main menu." << endl;
		return;
	}

	//there is costumer and vendor in his list
	//find the vendor j-1 in all vendors from main, and ask for date and feedback
	while (currVendors[j-1] != allVendors[v])
		v++;

	//create a new pointer to a new feedback
	feedback* f = readFeedback(*allCostumers[i - 1], *allVendors[v]);
	allVendors[v]->addFeedback(*f);		//add the new feedback to vendors list of feedbacks
}

feedback* readFeedback(Costumer& costumer, vendor& vendor)
{
	char date[DATE_LEN], feedbackDes[MAX_FEE];
	bool flagDate = false;
	int day, month, year;
	cin.ignore();
	while (!flagDate)
	{
		cout << "Enter today's date name: dd/mm/yyyy" << endl;			//check valid
		cin.getline(date, DATE_LEN);
		day = 10 * (int)(date[0] - '0') + (int)(date[1] - '0');
		month = 10 * (int)(date[3] - '0') + (int)(date[4] - '0');
		year = 1000 * (int)(date[6] - '0') + 100 * (int)(date[7] - '0') + 10 * (int)(date[8]-'0') + (int)(date[9]-'0'); 
		if ((day < 1 || day>31) || (month < 1 || month>12) || (year > 2019) || (date[2]!='/') || (date[5]!='/'))
			flagDate = false;
		else
			flagDate = true; 
		
	}

	cout << "Enter your feedback: maximum 100 chars " << endl; 
	cin.getline(feedbackDes, MAX_FEE);
	return new feedback(date, feedbackDes, costumer, vendor);
}

void addProductToShoppingCart(Costumer**& allCostumers, int costumerSize, vendor**& allVendors, int vendorSize)
{//option 5 from main
	int i = 0, choice = 0, flagCostumer = 0, j = 0;

	cout << "Choose product num or press 0 for more products." << endl;
	while (choice == 0 && i < vendorSize)		
	{//search for the wanted product. choice-1 is the idx of the product at arr products of vendor number i-1
		cout << "From vendor: " << allVendors[i]->getUserName() << endl;		//show who is the vendor
		allVendors[i]->showProducts();
		cin >> choice;
		i++;
	}

	if (choice == 0)
	{
		cout << "No product has been chosen. Exit to menu" << endl;
		return;
	}

	cout << "Press 1 to choose costumer to add the product to, or press 0 for another costumer." << endl;
	while (flagCostumer == 0 && j < costumerSize)	
	{//search for the wanted costumer. j-1 is the idx of the costumer in allcostumers arr
		cout << "Costumer's name: " << allCostumers[j]->getUserName() << endl;
		cin >> flagCostumer;
		j++;
	}

	if (flagCostumer == 0)
	{
		cout << "No costumer has been chosen. Exit to menu" << endl;
		return;
	}

	//there is vendor, whith product and the costumer who want the product
	const product** currProducts = allVendors[i - 1]->getProducts();	//get the products list from vendor
	allCostumers[j - 1]->addProduct(*currProducts[choice - 1]);			//add the pointed product to costumer's shopping list
}

void addOrderToPendingOrders(Costumer**& allCostumers, int costumerSize)			//option 6 from main
{
	int i = 0, flagChoice = 0, j = 0, flagProduct = 0;

	cout << "Press 1 to choose costumer to order for, or press 0 to the next costumer." << endl;	
	while (!flagChoice && i < costumerSize)	
	{//print every time costumer's name, if press 1 go out the loop. costumer num i-1
		cout << "Costumer's name: " << allCostumers[i]->getUserName() << endl;
		cin >> flagChoice;
		i++;
	}

	if (!flagChoice)			
	{//no costumer. exit
		cout << "No costumer has been chosen. Exit to menu" << endl;
		return;
	}

	if (allCostumers[i-1]->getShoppingCartSize() == 0)
	{//no products to shop. exit
		cout << "No products in shopping cart. Exit to menu" << endl;
		return;
	}

	//create new pointer to new order
	Order* newOrder = new Order(*allCostumers[i - 1]);
	const product** currShoppingCart = allCostumers[i - 1]->getShoppingCart();	//gets shopping cart from costumer
	int shoppingCartSize = allCostumers[i - 1]->getShoppingCartSize();			//gets how many products to choose from


	cout << "Press 1 to order the product, or press 0 to the next product." << endl;
	while (j < shoppingCartSize)
	{//print every time costumer's product, if press 1 add products to order else keep showing next products until no more
		cout << "Product name: " << currShoppingCart[j]->getName() << " " << currShoppingCart[j]->getPrice() << " ¥" << endl;
		cin >> flagProduct;

		if (flagProduct)				
		{//flagProduct=1, want the product. Add the new product to order and update the total price
			newOrder->addProduct(*currShoppingCart[j]);		
		}
		j++;
		flagProduct = 0;
	}

	if (newOrder->getProductAmount() == 0)
		delete newOrder; 
	else
		allCostumers[i - 1]->addOrder(*newOrder);
}

void payOrder(Costumer**& allCostumers, int costumerSize)		//option 7 from main
{
	int i = 0, flagChoice = 0, j = 0, flagOrder = 0;

	cout << "Press 1 to choose costumer to order for, or press 0 to the next costumer." << endl;
	while (!flagChoice && i < costumerSize)			
	{//print every time costumer's name, if press 1 go out the loop. costumer num i-1
		cout << "Costumer's name: " << allCostumers[i]->getUserName() << endl;
		cin >> flagChoice;
		i++;
	}

	if (flagChoice == 0)
	{//no costumer. exit
		cout << "No costumer has been chosen. Exit to menu" << endl;
		return;
	}

	const Order** currOrders = allCostumers[i - 1]->getPenOrders();		//gets all orders from costumer
	int orderAmount = allCostumers[i - 1]->getPenOrdersAmount();		//gets how many orders there are

	if (orderAmount == 0)
	{
		cout << "No orders to pay for. return menu." << endl;
		return;
	}

	cout << "Press 1 to pay that order, or press 0 to the next order." << endl;
	while (!flagOrder && j < orderAmount)
	{//print every time costumer's order, if press 1 go out the loop. order num j-1
		currOrders[j]->showProducts();
		cin >> flagOrder;
		j++;
	}

	if (flagOrder == 0)
	{//no order to pay for. exit
		cout << "No order has been chosen. Exit to menu" << endl;
		return;
	}

	//there is costumer i-1 with order j-1 to pay for
	allCostumers[i - 1]->removeProductsFromShoppingCart(j - 1);

	//add vendor to vendors list
	allCostumers[i - 1]->addVendorToVendorsList(j - 1);

	//remove order
	allCostumers[i - 1]->removeOrderFromPenOrders(j - 1);
}

void showCostumersDetails(Costumer**& allCostumers, int costumerSize)		//option 8 from main
{
	for (int i = 0; i < costumerSize; i++)
		allCostumers[i]->showDetails();
}

void showVendorsDetails(vendor**& allVendors, int vendorSize)		//option 9 from main
{
	for (int i = 0; i < vendorSize; i++)
		allVendors[i]->showDetails();
}

void showProductsByName(vendor**& allVendors, int vendorSize)		//option 10 from main
{
	char name[MAX_LEN];
	int currProductAmount;

	cin.ignore();
	cout << "Enter product name: MAX 20" << endl;
	cin.getline(name, MAX_LEN);

	for (int i = 0; i < vendorSize; i++)
	{
		currProductAmount = allVendors[i]->getProductAmount();
		const product** currProducts = allVendors[i]->getProducts();

		for (int j = 0; j < currProductAmount; j++)
		{
			if (strcmp(name, currProducts[j]->getName()) == 0)
				currProducts[j]->showDetails();
		}		
	}
}

bool checkSerialNumber(vendor**& allvendors, int seriealNumber, int allVendorSize)
{
	for (int i = 0; i < allVendorSize; i++)
	{
		for (int j = 0; j < allvendors[i]->getProductAmount(); j++)
		{
			const product** currProducts = allvendors[i]->getProducts(); 
			if (seriealNumber == currProducts[j]->getSerialNum())
				return false; 
		}
	}
	return true;
}