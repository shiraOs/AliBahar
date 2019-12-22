#include "Order.h"
#include "Costumer.h"
#include "Product.h"

Order::Order(const Costumer& costumerP, double totalPrice, int productAmount) : costumerP(&costumerP)
{
	this->totalPrice = totalPrice;
	this->productAmount = productAmount;
}

Order::Order(const Order& other)
{
	this->totalPrice = other.totalPrice;
	this->productAmount = other.productAmount;
	this->costumerP = other.costumerP;

	purchases = new const product*[productAmount];

	for (int i = 0; i < productAmount; i++)
		purchases[i] = other.purchases[i];			//cpy of pointer not object
}

Order::~Order()
{
	costumerP = nullptr;

	for (int i = 0; i < productAmount; i++)		//init the pointers to products
		purchases[i] = nullptr;
	delete[] purchases;							//remove the allocation of main arr
}

double Order::getTotalPrice() const
{
	return totalPrice;
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
	{
		temp[i] = purchases[i];
		purchases[i] = nullptr;
	}
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
		<< purchases[i]->getPrice() << "$" << endl;

	cout << "Total price: " << totalPrice << "$" << endl;
}