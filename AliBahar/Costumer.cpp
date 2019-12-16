#include "Costumer.h"
#include "Vendor.h"
#include "Address.h"
#include "Product.h"
#include "Order.h"

Costumer::Costumer(char* userName, char* password, const address& address,
	int shoppingCartSize, int vendorsAmount, int penOrdersAmount)	: homeAddress(address)
{
	cout << "In Costumer's c'tor for " << userName << endl;

	setUserName(userName);
	setPassword(password);
}

//Costumer::Costumer(const Costumer& other)
//{
//	cout << "In Costumer's cpy c'tor for " << other.userName << endl;
//
//	setUserName(other.userName);
//	setPassword(other.password);
//	setAddress(other.homeAddress);
//
//	shoppingCartSize = other.shoppingCartSize;
//	vendorsAmount = other.vendorsAmount;
//
//	for (int i = 0; i < shoppingCartSize; i++)
//		shoppingCart[i] = new product(*(other.shoppingCart[i]));
//
//	for (int i = 0; i < vendorsAmount; i++)
//		allVendors[i] = new vendor(*(other.allVendors[i]));
//
//	for (int i = 0; i < penOrdersAmount; i++)
//		pendingOrders[i] = new Order(*(other.pendingOrders[i]));
//	
//}

Costumer::~Costumer()
{
	cout << "In Costumer's d'tor for " << userName << endl;

	delete[] userName;
	delete[] password;

	for (int i = 0; i < shoppingCartSize; i++)
		delete shoppingCart[i];
	delete[] shoppingCart;

	for (int i = 0; i < vendorsAmount; i++)
		delete allVendors[i];
	delete[] allVendors;

	for (int i = 0; i < penOrdersAmount; i++)
		delete pendingOrders[i];
	delete[] pendingOrders;

}

void Costumer::setUserName(const char* name)
{
	delete[] userName;
	userName = new char[strlen(name) + 1];
	strcpy(userName, name);
}

const char* Costumer::getUserName() const
{
	return userName;
}

void Costumer::setPassword(const char* newPassword)
{
	delete[] password;
	password = new char[strlen(newPassword) + 1];
	strcpy(password, newPassword);
}

char* Costumer::getPassword() const
{
	return password;
}

void Costumer::setHomeAddress(address& newHomeAddress)
{
	homeAddress = newHomeAddress;
}

address& Costumer::getHomeAddress()
{
	return homeAddress;
}

void Costumer::addProduct(const product& newProduct)		//gets pointer to product. NOT OBJECT
{
	shoppingCartSize++;
	const product** temp = new const product*[shoppingCartSize];
	for (int i = 0; i < shoppingCartSize - 1; i++)
		temp[i] = shoppingCart[i];
	temp[shoppingCartSize - 1] = &newProduct;

	delete[] shoppingCart;
	shoppingCart = temp;
}

const product** Costumer::getShoppingCart() const
{
	return shoppingCart;
}

void Costumer::addVendor(const vendor& newVendor)
{//add a new vendor to arr of all vendors from all orders
	vendorsAmount++;
	const vendor** temp = new const vendor*[vendorsAmount];
	for (int i = 0; i < vendorsAmount - 1; i++)
		temp[i] = allVendors[i];
	temp[vendorsAmount - 1] = &newVendor;

	delete[] allVendors;
	allVendors = temp;
}
const vendor** Costumer::getAllVendors() const
{
	return allVendors;
}

void Costumer::addOrder(const Order newOrder)
{
	penOrdersAmount++;
	const Order** temp = new const Order*[penOrdersAmount];
	for (int i = 0; i < penOrdersAmount - 1; i++)
		temp[i] = pendingOrders[i];
	temp[penOrdersAmount - 1] = &newOrder;

	delete[] pendingOrders;
	pendingOrders = temp;
}

const Order** Costumer::getPenOrders() const
{
	return pendingOrders;
}

int Costumer::getShoppingCartSize() const
{
	return shoppingCartSize;
}

int Costumer::getVendorsAmount() const
{
	return vendorsAmount;
}

int Costumer::getPenOrdersAmount() const
{
	return penOrdersAmount;
}

void Costumer::removeProductsFromShoppingCart(int orderNum)
{
	int i = 0, tempI = 0;
	int shoppingCartSize = getShoppingCartSize(), orderNumOfProducts = pendingOrders[orderNum]->getProductAmount();
	const product** orderProducts = pendingOrders[orderNum]->getPurchases();	//get the products arr from the wanted order
	int newShoppingCartSize = shoppingCartSize - orderNumOfProducts;
	const product** tempCart = new const product*[newShoppingCartSize];			//new shopping cart
	int* removeIdx=new int [orderNumOfProducts];		//save the index of products to remove from shopping cart

	for (int j = 0; j < orderNumOfProducts; j++)
	{
		while (orderProducts[j] != shoppingCart[i] && i < shoppingCartSize)		//go all over the product
		{//check until find match in products
			i++;
		}
		removeIdx[tempI] = i;		//save the equal product
		tempI++;
		i = 0;
	}
	
	tempI = 0, i=0;

	for (int j = 0; j < shoppingCartSize; j++)
	{
		if (j = removeIdx[tempI])
			tempI++;
		else
		{
			tempCart[i] = shoppingCart[j];
			i++;
		}
	}

	delete[] shoppingCart;
	shoppingCart = tempCart;
	shoppingCartSize = newShoppingCartSize;
	delete[] removeIdx;
}

void Costumer::removeOrderFromPenOrders(int orderNum)
{
	penOrdersAmount--;
	const Order** temp = new const Order*[penOrdersAmount];
	int tempI = 0;
	for (int i = 0; i < penOrdersAmount+1; i++)
	{
		if (i != orderNum)
		{
			temp[tempI] = pendingOrders[i];
			tempI++;
		}
	}
	delete[] pendingOrders;
	pendingOrders = temp;
}


//void Costumer::setpenOrdersAmount(int newPenAmount)
//{
//	penOrdersAmount = newPenAmount;
//}

//*****************************FUNCTIONS FROM MAIN****************************************//

void addCostumer(Costumer** allCostumers, int* costumerSize)	
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
	
	allCostumers[(*costumerSize)-1] = new Costumer(userName, password, address(state, city, street, homeNum, aptNum));
	*costumerSize++;
	allCostumers = new Costumer*[*costumerSize];
	//cpy arr
}

void addProductToShoppingCart(Costumer** allCostumers, int costumerSize, vendor** allVendors, int vendorSize)
{
	int i = 0, choice = 0,  flagCostumer= 0, j = 0;

	cout << "Choose product num or press 0 for more products." << endl;

	while (choice==0 && i < vendorSize)		//as long as there is no choice, keep showing products.
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
	allCostumers[j - 1]->addProduct(*currProducts[choice-1]);
}

void addOrderToPendingOrders(Costumer** allCostumers, int costumerSize)				//add new order- from the main menu
{
	int i = 0, flagChoice = 0, j=0, flagProduct=0;

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
		cout << "Product name: " << currShoppingCart[j]->getName() << " "<< currShoppingCart[j]->getPrice() << " ¥" << endl;
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