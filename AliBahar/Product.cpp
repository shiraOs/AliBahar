#include "Product.h"
#include "Vendor.h"

product::product(eCategory newCategory, char* newName, double newPrice, int newSerialNum, const vendor& newV)
	: category(newCategory), serialNum(newSerialNum)
{
	setName(newName);
	setPrice(newPrice);
	setVendor(newV);
}

product::~product()
{
	vendorP = nullptr;
	delete[] name;
}


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

char* product::getName() const
{
	return name;
}

void product::setPrice(double newPrice)
{
	price = newPrice;
}

double product::getPrice() const
{
	return price;
}

int product::getSerialNum() const
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

void product::showDetails() const
{
	cout << "Category: " << categories[this->category - 1] << endl;
	cout << "Name: " << this->name << endl;
	cout << "Price: " << this->price << "$" << endl;
	cout << "Serial Number: " << this->serialNum << endl;
}
