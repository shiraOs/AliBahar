#include "Product.h"
#include "Vendor.h"

product::product(eCategory newCategory, char* newName, int newPrice, int newSerialNum, const vendor& newV)
	: category(newCategory), serialNum(newSerialNum)
{
	cout << "In Product's c'tor for " << newName << endl;

	setName(newName);
	setPrice(newPrice);
	setVendor(newV);
}

//product::product(const product& other)
//{
//	cout << "In Product's cpy c'tor for " << other.name << endl;
//
//	setCategory(other.category);
//	setName(other.name);
//	setPrice(other.price);
//	setSerialNum(other.serialNum);
//	setVendor(other.vendorP);
//}

product::~product()
{
	cout << "In Product's d'tor for " << name << endl;

	delete[] name;
}

//void product::setCategory(eCategory newCategory)
//{
//	category = newCategory;
//}

const eCategory product::getCategory() const
{
	return category;
}

void product::setName(char* newName)
{
	delete[] name;
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

const char* product::getName() const
{
	return name;
}

void product::setPrice(int newPrice)
{
	price = newPrice;
}

const int product::getPrice() const
{
	return price;
}

//void product::setSerialNum(int newSerialNum)
//{
//	serialNum = newSerialNum;
//}

const int product::getSerialNum() const
{
	return serialNum;
}

void product::setVendor(const vendor& newV)
{
	vendorP = &newV;
}

const vendor* product::getVendor() const
{
	return vendorP;
}