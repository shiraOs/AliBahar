#include "Address.h"

address::address(char* newState, char* newCity, char* newStreet, int newHomeNum, int newAptNum)
{
	this->state = nullptr;
	this->city = nullptr;
	this->street = nullptr;

	setState(newState);
	setCity(newCity);
	setStreet(newStreet);
	setHomeNum(newHomeNum);
	setAptNum(newAptNum);
}

address::address(const address& other)
{
	setState(other.state);
	setCity(other.city);
	setStreet(other.street);
	setHomeNum(other.homeNum);
	setAptNum(other.aptNum);
}

address::~address()
{
	delete[] state;
	delete[] city;
	delete[] street;
}

void address::setState(char* newState)
{
	delete[] state;
	state = new char[strlen(newState) + 1];
	strcpy(state, newState);
}

char* address::getState() const
{
	return state;
}

void address::setCity(char* newCity)
{
	delete[] city;
	this->city = new char[strlen(newCity) + 1];
	strcpy(this->city, newCity);
}

char* address::getCity() const
{
	return city;
}

void address::setStreet(char* newStreet)
{
	delete[] street;
	this->street = new char[strlen(newStreet) + 1];
	strcpy(this->street, newStreet);
}

char* address::getStreet() const
{
	return street;
}

void address::setHomeNum(int newHomeNum)
{
	homeNum = newHomeNum;
}

int address::getHomeNum() const
{
	return homeNum;
}

void address::setAptNum(int newAptNum)
{
	aptNum = newAptNum;
}

int address::getAptNum() const
{
	return aptNum;
}

void address::show() const
{
	cout << "Address: " << endl;
	cout << " State: " << this->state << ", city: " << this->city << endl;
	cout << " Street: " << this->street << " number " << this->homeNum << ", apartment: " << this->aptNum << endl;
}
