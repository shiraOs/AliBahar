#include "Order.h"
#include "Costumer.h"
#include "Product.h"

Order::Order(const Costumer& costumerP, int totalPrice, int productAmount) : costumerP(&costumerP)
{
	cout << "In Order's c'tor for " << costumerP.getUserName() << endl;

	setTotalPrice(totalPrice);
	setProductAmount(productAmount);

	//purchases = new product*[productAmount];
}

Order::Order(const Order& other)
{
	cout << "In Order's cpy c'tor for " << other.costumerP->getUserName() << endl;

	setTotalPrice(other.totalPrice);
	setProductAmount(other.productAmount);
	setCostumer(*other.costumerP);

	purchases = new const product*[productAmount];

	for (int i = 0; i < productAmount; i++)
		purchases[i] = other.purchases[i];			//cpy of pointer not object
}

Order::~Order()
{
	cout << "In Order's d'tor for " << this->costumerP->getUserName() << endl;

	for (int i = 0; i < productAmount; i++)
		delete purchases[i];

	delete[] purchases;
}

void Order::setTotalPrice(int newTotalPrice)
{
	totalPrice = newTotalPrice;
}

int Order::getTotalPrice() const
{
	return totalPrice;
}

void Order::setProductAmount(int newProductAmount)
{
	productAmount = newProductAmount;
}

int Order::getProductAmount() const
{
	return productAmount;
}

void Order::setCostumer(const Costumer& newCostumer)
{
	costumerP = &newCostumer;
}

const Costumer* Order::getCostumer() const
{
	return costumerP;
}

void Order::addProduct(const product& newProduct)
{
	productAmount++;
	const product** temp = new const product*[productAmount];
	for (int i = 0; i < productAmount - 1; i++)
		temp[i] = purchases[i];
	temp[productAmount - 1] = &newProduct;

	delete[] purchases;
	purchases = temp;
	this->totalPrice = this->totalPrice + newProduct.getPrice();		//update the total price
}

const product** Order::getPurchases() const
{
	return purchases;
}

void Order::showProducts() const
{
	for (int i = 0; i < productAmount; i++)
		cout << i + 1 << ". " << purchases[i]->getName() << "...................."
		<< purchases[i]->getPrice() << "¥" << endl;

	cout << "Total price: " << totalPrice << endl;
}

/**************************************************************/

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