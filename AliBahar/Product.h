#define _CRT_SECURE_NO_WARNING
#ifndef _PRODUCT_H
#define _PRODUCT_H

#include <iostream>
using namespace std;

class vendor;

#pragma warning (disable: 4996)

const int MAX_PRO = 20;
enum eCategory { KIDS=1, ELECTRICITY=2, OFFICE=3, CLOTHING=4 };
static const char* categories[] = { "Kids", "Electricity", "Office", "Clothing" };

class product
{
private:
	const eCategory category;
	char* name;
	int price;
	const int serialNum;
	const vendor* vendorP;

public:
	product(eCategory newCategory, char* newName, int newPrice, int newSerialNum,const vendor& newV);
	product(const product&) = delete;
	~product();

	//void setCategory(eCategory newCategory);
	const eCategory getCategory() const;
	void setName(char* newName);
	const char* getName() const;
	void setPrice(int newPrice);
	const int getPrice() const;
	//void setSerialNum(int newSerialNum);
	const int getSerialNum() const;
	void setVendor(const vendor& newV);
	const vendor* getVendor() const;
};

#endif	//_PRODUCT_H