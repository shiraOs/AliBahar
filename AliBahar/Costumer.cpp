#include "Costumer.h"
#include "Vendor.h"
#include "Product.h"
#include "Order.h"

Costumer::Costumer(char* userName, char* password, const address& address,
	int shoppingCartSize, int vendorsAmount, int penOrdersAmount) : homeAddress(address)
{
	setUserName(userName);
	setPassword(password);
	shoppingCart = nullptr;
	allVendors = nullptr;
	pendingOrders = nullptr;
}

Costumer::~Costumer()
{
	delete[] userName;
	delete[] password;

	for (int i = 0; i < shoppingCartSize; i++)		//init the pointers of products
		shoppingCart[i] = nullptr;
	delete[] shoppingCart;							//free allocation of main arr

	for (int i = 0; i < vendorsAmount; i++)
		allVendors[i] = nullptr;					//init the pointers of vendor
	delete[] allVendors;							//free allocation of main arr

	for (int i = 0; i < penOrdersAmount; i++)		//free object of orders
		delete pendingOrders[i];					//free original object memory
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

void Costumer::addOrder(const Order& newOrder)
{//add order to all orders arr
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
{//after paying an order- remove purchased products from cart
	int shoppingCartSize = getShoppingCartSize(), orderNumOfProducts = pendingOrders[orderNum]->getProductAmount();
	const product** orderProducts = pendingOrders[orderNum]->getPurchases();	//gets the products arr from the wanted order

	for (int j = 0; j < orderNumOfProducts; j++)
	{
		for (int i = 0; i < shoppingCartSize; i++)
		{
			if (orderProducts[j] == this->shoppingCart[i])	//if the same product, reset the pointer at shopping cart
				this->shoppingCart[i] = nullptr;
		}
	}

	//make a new shopping cart-remove all null pointers
	int newShoppingCartSize = shoppingCartSize - orderNumOfProducts, tempI = 0;
	const product** tempCart = new const product*[newShoppingCartSize];			//new shopping cart

	for (int i = 0; i < this->shoppingCartSize; i++)
	{
		if (this->shoppingCart[i] != nullptr)
		{//if not removed prudcts. copy to temp arr
			tempCart[tempI] = shoppingCart[i];
			shoppingCart[i] = nullptr;
			tempI++;								//rise up temp cart index
		}
	}

	delete[] shoppingCart;							//free memory old cart
	shoppingCart = tempCart;
	this->shoppingCartSize = newShoppingCartSize;	//update to new size
}

void Costumer::removeOrderFromPenOrders(int orderNum)
{//delete order after paying
	penOrdersAmount--;
	if (penOrdersAmount > 0)
	{
		const Order** temp = new const Order*[penOrdersAmount];
		int tempI = 0;
		for (int i = 0; i < penOrdersAmount + 1; i++)
		{
			if (i != orderNum)
			{//copy all other orders
				temp[tempI] = pendingOrders[i];
				pendingOrders[i] = nullptr;
				tempI++;
			}
			else
				delete pendingOrders[i];	//free memory of order
		}
		delete[] pendingOrders;
		pendingOrders = temp;
	}
	else
	{//had only one order-needs to be removed
		delete pendingOrders[penOrdersAmount];
		pendingOrders = nullptr;
	}
}

void Costumer::addVendorToVendorsList(int orderNum)
{//after paying an order, add vendors (one time each) of purchased products.
	const product** currOrder = this->pendingOrders[orderNum]->getPurchases();
	int numOfProducts = this->pendingOrders[orderNum]->getProductAmount();

	for (int i = 0; i < numOfProducts; i++)
	{
		if (!checkVendor((*currOrder)[i]))
		{//needs to add the new vendor to vendors list
			const vendor* v = (*currOrder)[i].getVendor();
			this->addVendor(*v);
		}
	}
}

bool Costumer::checkVendor(const product& currProduct)
{//gets product from order, check if its vendor in vendors list
	for (int i = 0; i < vendorsAmount; i++)
		if (currProduct.getVendor() == this->allVendors[i])
			return true;
	return false;
}

void Costumer::showDetails() const
{
	cout << "User Name: " << this->userName << endl;
	cout << "Password: " << this->password << endl;
	this->homeAddress.show();
}


