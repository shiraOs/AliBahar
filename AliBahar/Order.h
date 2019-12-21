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
	double totalPrice;
	const Costumer* costumerP;
	int productAmount;

public:
	Order(const Costumer& costumerP, double totalPrice = 0, int productAmount = 0);
	Order(const Order& other);
	~Order();

	double getTotalPrice() const;
	int getProductAmount() const;

	void setCostumer(const Costumer& newCostumer);
	const Costumer* getCostumer() const;

	void addProduct(const product& newProduct);
	const product** getPurchases() const;

	void showProducts() const;
};

#endif // !_ORDER_H


