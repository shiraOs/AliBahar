#include "System.h"
#include "Address.h"
#include "Costumer.h"
#include "Feedback.h"
#include "Order.h"
#include "Product.h"
#include "Vendor.h"

void printOptions()
{
	cout << "What would you like to do?\n";
	cout << "Add costumer - press 1\nAdd vendor - press2\nAdd product to vendor - press"
		" 3\nAdd feedback to vendor - press 4\nAdd product to shopping cart - press 5\nAdd"
		" order to costumer - press 6\nPayment for order - press 7\nShow all costumers"
		" - press 8\nShow all vendors - press 9\nShow all products by name - press 10\n"
		"EXIT - press 11\n";
}

void addCostumer(Costumer** allCostumers, int* costumerSize)
{
	char userName[MAX_LEN], password[MAX_LEN], state[MAX_ADD], city[MAX_ADD], street[MAX_ADD];
	int homeNum, aptNum;

	cin.ignore();
	cout << "Please enter costumer's username: MAX 20" << endl;;		//check valid name
	cin.getline(userName, MAX_LEN);

	cout << "Please enter costumer's password: MAX 20" << endl;		//check valid pass
	cin.getline(password, MAX_LEN);

	cout << "Please enter costumer's state: MAX 20";		//check valid state
	//cin.ignore();
	cin.getline(state, MAX_LEN);

	cout << "Please enter costumer's city: MAX 20";			//check valid city
	//cin.ignore();
	cin.getline(city, MAX_LEN);

	cout << "Please enter costumer's street: MAX 20";		//check valid street
	//cin.ignore();
	cin.getline(street, MAX_LEN);

	cout << "Please enter costumer's home number: ";		//check valid home number
	//cin.ignore();
	cin >> homeNum;

	cout << "Please enter costumer's apartment number: ";	//check valid apt num
	//cin.ignore();
	cin >> aptNum;

	allCostumers[(*costumerSize) - 1] = new Costumer(userName, password, address(state, city, street, homeNum, aptNum));
	(*costumerSize)++;
	Costumer** temp = new Costumer*[*costumerSize];
	for (int i = 0; i < *costumerSize - 1; i++)
	{
		temp[i] = allCostumers[i];
		allCostumers[i] = nullptr;
	}

	delete[] allCostumers;
	allCostumers = temp;	
}

void addProductToShoppingCart(Costumer** allCostumers, int costumerSize, vendor** allVendors, int vendorSize)
{
	int i = 0, choice = 0, flagCostumer = 0, j = 0;

	cout << "Choose product num or press 0 for more products." << endl;

	while (choice == 0 && i < vendorSize)		//as long as there is no choice, keep showing products.
	{
		cout << "From vendor: " << allVendors[i]->getUserName() << endl;		//show who is the vendor
		allVendors[i]->showProducts();
		cin >> choice;							//choice -1 is the idx of the product at arr products of vendor number i
		i++;
	}

	if (choice == 0)
	{
		cout << "No product has been chosen. Exit to menu" << endl;
		return;
	}

	cout << "Press 1 to choose costumer to add the product to, else press 0." << endl;	//choose the costumer

	while (flagCostumer == 0 && j < costumerSize)	//search for the wantes costumer. j is the number of the costumer
	{
		cout << "Costumer's name: " << allCostumers[j]->getUserName() << endl;
		cin >> flagCostumer;	//1 if want the costumer, else 0;
		j++;
	}

	if (flagCostumer == 0)
	{
		cout << "No costumer has been chosen. Exit to menu" << endl;
		return;
	}

	//there are vendor, which product and the costumer who want the product
	const product** currProducts = allVendors[i - 1]->getProducts();
	allCostumers[j - 1]->addProduct(*currProducts[choice - 1]);
}

void addOrderToPendingOrders(Costumer** allCostumers, int costumerSize)				//add new order- from the main menu
{
	int i = 0, flagChoice = 0, j = 0, flagProduct = 0;

	cout << "Press 1 to choose costumer to order for, or press 0 to the next costumer." << endl;	//choose the costumer

	while (!flagChoice && i < costumerSize)			//choose who is the costumer
	{
		cout << "Costumer's name: " << allCostumers[i]->getUserName() << endl;
		cin >> flagChoice;	//1 if want the costumer, else 0;
		i++;
	}

	if (!flagChoice)			//no costumer. exit
	{
		cout << "No costumer has been chosen. Exit to menu" << endl;
		return;
	}

	Order newOrder(*allCostumers[i - 1]);								//creat a new empty order
	const product** currShoppingCart = allCostumers[i - 1]->getShoppingCart();
	int shoppingCartSize = allCostumers[i - 1]->getShoppingCartSize();		//how many products to choose from

	//int penOrderAmount = allCostumers[i - 1]->getPenOrdersAmount();		//size of oreders
	//Order* CurrOrder = allCostumers[i - 1]->getPenOrders()[penOrderAmount - 1];	//order at the last place, the current order-last one to add

	cout << "Press 1 to order the product, or press 0 to the next product." << endl;

	while (j < shoppingCartSize)		//go over all the shopping cart press 1 to add product to new order
	{
		cout << "Product name: " << currShoppingCart[j]->getName() << " " << currShoppingCart[j]->getPrice() << " ¥" << endl;
		cin >> flagProduct;

		if (flagProduct)				//=1, want the product need to add to the order
		{
			newOrder.addProduct(*currShoppingCart[j]);		//add the new product to order and update the total price

			//const product* productToAdd = allCostumers[i - 1]->getShoppingCart()[j];
			//addProductToOrder(CurrOrder, productToAdd);
		//	allCostumers[i - 1]->getPenOrders()[allCostumers[i - 1]->getPenOrdersAmount()]->addProduct(allCostumers[i - 1]->getShoppingCart()[j]);
		}
		j++;
		flagProduct = 0;
	}

	allCostumers[i - 1]->addOrder(newOrder);
}

//void addOrderToPenOrders(Order& const newOrder, Costumer* currCostumer)
//{//add new order for pending oreders arr
//	int penOrderAmount = currCostumer->getPenOrdersAmount();					//get old amount
//	currCostumer->setpenOrdersAmount(penOrderAmount + 1);						//add 1 to the amount
//
//	Order** penOrder = currCostumer->getPenOrders();						//get pending orders from the costumer
//	Order** temp = new Order*[penOrderAmount+1];					//make a new array for the resize
//	for (int i = 0; i < penOrderAmount; i++)			//cpy the old to the temp
//		temp[i] = penOrder[i];
//	temp[penOrderAmount] = &newOrder;				//add the new order
//
//	delete[] penOrder;								//clear the memory of the old array
//	penOrder = temp;								//put the temp in the old one
//}

void payOrder(Costumer** allCostumers, int costumerSize)
{
	int i = 0, flagChoice = 0, j = 0, flagOrder = 0;

	cout << "Press 1 to choose costumer to order for, or press 0 to the next costumer." << endl;	//choose the costumer

	while (!flagChoice && i < costumerSize)			//choose who is the costumer who want to pay an order
	{
		cout << "Costumer's name: " << allCostumers[i]->getUserName() << endl;
		cin >> flagChoice;	//1 if want the costumer, else 0;
		i++;
	}

	if (flagChoice == 0)			//no costumer. exit
	{
		cout << "No costumer has been chosen. Exit to menu" << endl;
		return;
	}

	const Order** currOrders = allCostumers[i - 1]->getPenOrders();
	int orderAmount = allCostumers[i - 1]->getPenOrdersAmount();

	cout << "Press 1 to pay that order, or press 0 to the next order." << endl;

	while (!flagOrder && j < orderAmount)			//choose which order you want to pay
	{
		currOrders[j]->showProducts();
		cin >> flagOrder;
		j++;
	}

	if (flagChoice == 0)			//no order to pay for. exit
	{
		cout << "No order has been chosen. Exit to menu" << endl;
		return;
	}

	//there is costumer i-1 with order j-1 to pay for
	allCostumers[i - 1]->removeProductsFromShoppingCart(j - 1);

	//remove order
	allCostumers[i - 1]->removeOrderFromPenOrders(j - 1);
}

void showCostumersDetails(Costumer** allCostumers, int costumerSize)
{
	for (int i = 0; i < costumerSize; i++)
		allCostumers[i]->showDetails();
}

void showVendorsDetails(vendor ** allVendors, int vendorSize)
{
	for (int i = 0; i < vendorSize; i++)
		allVendors[i]->showDetails();
}

void showProductsByName(vendor ** allVendors, int vendorSize)
{
	char name[MAX_LEN];
	int currProductAmount;

	cout << "Enter product name: MAX 20" << endl;
	cin.getline(name, MAX_LEN);

	for (int i = 0; i < vendorSize; i++)
	{
		currProductAmount = allVendors[i]->getProductAmount();
		const product** currProducts = allVendors[i]->getProducts();

		for (int j = 0; j < currProductAmount; j++)
		{
			if (strcmp(name, currProducts[j]->getName()))
				currProducts[j]->showDetails();
		}		
	}
}


//void addProductToOrder(Order* CurrOrder, const product* newProduct)		//get point to order and a new product to add to order
//{
//	int pAmount = CurrOrder->getProductAmount();	//old amount
//	CurrOrder->setProductAmount(pAmount + 1);		//add one
//	
//	const product** purchases = CurrOrder->getPurchases();		//all products
//	const product** temp = new const product*[pAmount+1];		//temp cpy to resize 
//	for (int i = 0; i < pAmount; i++)
//		temp[i] = purchases[i];
//	temp[pAmount] = newProduct;
//
//	delete[] purchases;
//	purchases = temp;
//}

void addVendor(vendor ** allVendors, int * vendorsSize)
{
	char userName[MAX_LEN], password[MAX_LEN], state[MAX_ADD], city[MAX_ADD], street[MAX_ADD];
	int homeNum, aptNum;

	cout << "Please enter costumer's username: MAX 20";		//check valid name
	cin.ignore();
	cin.getline(userName, MAX_LEN);

	cout << "Please enter costumer's password: MAX 20";		//check valid pass
	cin.ignore();
	cin.getline(password, MAX_LEN);

	cout << "Please enter costumer's state: MAX 20";		//check valid state
	cin.ignore();
	cin.getline(state, MAX_LEN);

	cout << "Please enter costumer's city: MAX 20";			//check valid city
	cin.ignore();
	cin.getline(city, MAX_LEN);

	cout << "Please enter costumer's street: MAX 20";		//check valid street
	cin.ignore();
	cin.getline(street, MAX_LEN);

	cout << "Please enter costumer's home number: ";		//check valid home number
	cin.ignore();
	cin >> homeNum;

	cout << "Please enter costumer's apartment number: ";	//check valid apt num
	cin.ignore();
	cin >> aptNum;

	allVendors[(*vendorsSize) - 1] = new vendor(userName, password, address(state, city, street, homeNum, aptNum));
	(*vendorsSize)++;
	vendor** temp = new vendor*[*vendorsSize];
	for (int i = 0; i < *vendorsSize - 1; i++)
	{
		temp[i] = allVendors[i];
		allVendors[i] = nullptr;
	}

	delete[] allVendors;
	allVendors = temp;
}

void addPdtToVdr(vendor** allVendors, int vendorSize)		//from main
{//gets an arr of vendors and its size, search for the wanted vendor and then add a product to his list.]
	int i = 0, flagVendor = 0;

	cout << "Press 1 to choose the curr vendor, or press 0 to the next one." << endl;
	while (!flagVendor && i < vendorSize)				//print every time vendor's name, if press 1 go out the loop. vendor num i-1
	{
		cout << "Vendor's name: " << allVendors[i]->getUserName() << endl;
		cin >> flagVendor;
		i++;
	}

	//char vendorName[MAX_LEN];
	//cout << "Enter vendor's name: ";
	//cin.getline(vendorName, MAX_LEN);
	//cout << endl;
	//int i = 0;
	//while (strcmp(allVendors[i]->getUserName(), vendorName) != 0 && i < vendorSize)
	//	i++;

	if (!flagVendor)
	{
		cout << "No vendor has been chosen. Return to main menu." << endl;
		return;
	}

	eCategory category;
	char pdtName[MAX_LEN];
	int c, price, serialNumber;

	cout << "Enter product category:\n 1. Kids \n 2. Electricity \n 3. Office \n 4. Clothing" << endl;
	cin >> c;
	category = (eCategory)c;

	cout << "Enter product name: (no more then 20 letters)";
	cin.getline(pdtName, MAX_LEN);
	cout << endl;

	cout << "Enter product's price: ";
	cin >> price;
	cout << endl;

	cout << "Enter product's serial number: ";		//check valid
	cin >> serialNumber;
	cout << endl;

	allVendors[i - 1]->addProduct(product(category, pdtName, price, serialNumber, *allVendors[i - 1]));
}

void addFeedback(Costumer** allCostumers, int costumerSize, vendor** allVendors, int vendorSize)		//from main
{//gets arr of costumers and its size, search for the wanted costumer, then choose the vendor and add a feedback

	//cout << "Enter costumer's name: ";
	//cin.getline(costumerName, MAX_LEN);
	//cout << endl;
	//while (strcmp(allCostumers[i]->getUserName(), costumerName) != 0 && i < costumerSize)		//check if costumer exist
	//	i++;

	int i = 0, flagCostumer = 0, j = 0, flagVendor = 0, v = 0;

	cout << "Press 1 to choose the curr costumer, or press 0 to the next one." << endl;
	while (!flagCostumer && i < costumerSize)				//print every time costumer's name, if press 1 go out the loop. costumer num i-1
	{
		cout << "Costumer's name: " << allCostumers[i]->getUserName() << endl;
		cin >> flagCostumer;
		i++;
	}

	if (!flagCostumer)
	{
		cout << "Costumer DOES NOT exist in the system." << endl;
		return;
	}

	//cout << "Enter vendor's name: ";
	//cin.getline(vendorName, MAX_LEN);
	//cout << endl;
	//while (strcmp(allCostumers[i]->getAllVendors()[j]->getUserName(), vendorName) != 0 && j < allCostumers[i]->getVendorsAmount())
	//	//there is costumer, check if there is vendor at costumer's vendors
	//	j++;
	int vendorsAmount = allCostumers[i - 1]->getVendorsAmount();			//gets the amount of vendors in curr costumer
	const vendor** currVendors = allCostumers[i - 1]->getAllVendors();			//gets the list of vendors of curr costumer

	cout << "Press 1 to choose the curr vendor, or press 0 to the next one." << endl;
	while (!flagVendor && j < vendorsAmount)				//print every time vendor's name, if press 1 go out the loop. vendor num j-1
	{
		cout << "Vendor's name: " << currVendors[j]->getUserName() << endl;
		cin >> flagVendor;
		j++;
	}

	if (!flagVendor)
	{
		cout << "No vendor has been chosen. Return to main menu." << endl;
		return;
	}

	//there is costumer and vendor in his list, find the vendor in all vendors from main, and ask for date and feedback

	while (currVendors[j] != allVendors[v])
		v++;

	char date[MAX_LEN], feedbackDes[MAX_FEE];

	cout << "Enter today's date name: ";			//check valid
	cin.getline(date, MAX_LEN);
	cout << endl;

	cout << "Enter your feedback: ";
	cin.getline(feedbackDes, MAX_FEE);
	cout << endl;

	allVendors[v]->addFeedback(feedback(date, feedbackDes, *allCostumers[i - 1], *allVendors[v]));

	//allCostumers[i]->getAllVendors()[j]->addFeedback(feedback(date, feedbackDes, allCostumers[i], allCostumers[i]->getAllVendors()[j]));
}