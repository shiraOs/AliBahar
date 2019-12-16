#ifndef _ORDER_H
#define _ORDER_H

#include <iostream>
using namespace std;

#pragma warning (disable: 4996)
class product;
class Costumer;

class Order
{
private:
	const product** purchases;
	int totalPrice;
	const Costumer* costumerP;
	int productAmount;

public:
	Order(const Costumer& costumerP, int totalPrice = 0, int productAmount = 0);
	Order(const Order& other);
	~Order();

	void setTotalPrice(int newTotalPrice);
	int getTotalPrice() const;

	void setProductAmount(int newProductAmount);
	int getProductAmount() const;

	void setCostumer(const Costumer& newCostumer);
	const Costumer* getCostumer() const;

	void addProduct(const product& newProduct);
	const product** getPurchases() const;

	void showProducts() const;
};

#endif // !_ORDER_H

//void addProductToOrder(const Order* CurrOrder, const product* newProduct);

