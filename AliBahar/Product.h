#define _CRT_SECURE_NO_WARNING
#ifndef _PRODUCT_H
#define _PRODUCT_H

#include <iostream>
using namespace std;

class vendor;

#pragma warning (disable: 4996)

enum eCategory { KIDS=1, ELECTRICITY=2, OFFICE=3, CLOTHING=4 };
static const char* categories[] = { "Kids", "Electricity", "Office", "Clothing" };
static const int categoriesAmount = 4;

class product
{
private:
	const eCategory category;
	char* name;
	double price;
	const int serialNum;
	const vendor* vendorP;

public:
	product(eCategory newCategory, char* newName, double newPrice, int newSerialNum,const vendor& newV);
	product(const product&) = delete;
	~product();

	const eCategory getCategory() const;
	void setName(char* newName);
	char* getName() const;
	void setPrice(double newPrice);
	double getPrice() const;
	int getSerialNum() const;
	void setVendor(const vendor& newV);
	const vendor* getVendor() const;

	void showDetails() const;
};

#endif	//_PRODUCT_H