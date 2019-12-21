#ifndef _COSTUMER_H
#define _COSTUMER_H

#include <iostream>
using namespace std;

#pragma warning (disable: 4996)

#include "Address.h"
class product;
class vendor;
class Order;

class Costumer
{
private:
	char* userName;
	char* password;
	address homeAddress;
	const product** shoppingCart;
	const vendor** allVendors;			//all vendors after payment is done
	const Order** pendingOrders;
	int shoppingCartSize;
	int vendorsAmount;
	int penOrdersAmount;

public:
	Costumer(char* userName, char* password, const address& address, int shoppingCartSize=0, 
		int vendorsAmount=0, int penOrdersAmount=0);
	Costumer(const Costumer&)=delete;
	~Costumer();

	void setUserName(const char* name);
	char* getUserName() const;

	void setPassword(const char* newPassword);
	char* getPassword() const;

	void setHomeAddress(address& newHomeAddress);
	address& getHomeAddress();

	void addProduct(const product& newProduct);
	const product** getShoppingCart() const;

	void addVendor(const vendor& newVendor);
	const vendor** getAllVendors() const;

	void addOrder(const Order& newOrder);
	const Order** getPenOrders() const;

	int getShoppingCartSize() const;
	int getVendorsAmount() const;
	int getPenOrdersAmount() const;

	void removeProductsFromShoppingCart(int orderNum);
	void addVendorToVendorsList(int orderNum);
	bool checkVendor(const product& currProduct);
	void removeOrderFromPenOrders(int orderNum);
	void showDetails() const;
};

#endif // !_COSTUMER_H