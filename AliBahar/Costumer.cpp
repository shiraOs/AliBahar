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

	for (int i = 0; i < shoppingCartSize; i++)		//init the pointers of products
		shoppingCart[i] = nullptr;
	delete[] shoppingCart;							//free allocation of main arr

	for (int i = 0; i < vendorsAmount; i++)
		allVendors[i] = nullptr;					//init the pointers of vendor
	delete[] allVendors;							//free allocation of main arr

	for (int i = 0; i < penOrdersAmount; i++)		//free object of orders
		delete pendingOrders[i];
	delete[] pendingOrders;							//free allocation of main arr

}

void Costumer::setUserName(const char* name)
{
	delete[] userName;
	userName = new char[strlen(name) + 1];
	strcpy(userName, name);
}

char* Costumer::getUserName() const
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
	{
		temp[i] = shoppingCart[i];
		shoppingCart[i] = nullptr;
	}
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
	{
		temp[i] = allVendors[i];
		allVendors[i] = nullptr;
	}
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
	{
		temp[i] = pendingOrders[i];
		pendingOrders[i] = nullptr;
	}
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
			shoppingCart[j] = nullptr;
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
			pendingOrders[i] = nullptr;
			tempI++;
		}
	}
	delete[] pendingOrders;
	pendingOrders = temp;
}

void Costumer::showDetails() const
{
	cout << "User Name: " << this->userName << endl;
	cout << "Password: " << this->password << endl;
	this->homeAddress.show();
}


//void Costumer::setpenOrdersAmount(int newPenAmount)
//{
//	penOrdersAmount = newPenAmount;
//}

//*****************************FUNCTIONS FROM MAIN****************************************//

