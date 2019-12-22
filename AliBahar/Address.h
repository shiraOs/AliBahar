#define _CRT_SECURE_NO_WARNING
#ifndef _ADDRESS_H
#define _ADDRESS_H

#include <iostream>
using namespace std;

#pragma warning (disable: 4996)

class address
{
private:
	char* state;
	char* city;
	char* street;
	int homeNum;
	int aptNum;

public:
	address(char* newState, char* newCity, char* newStreet, int newHomeNum, int newAptNum);
	address(const address& other);
	~address();

	void setState(char* newState);
	char* getState() const;

	void setCity(char* newCity);
	char* getCity() const;

	void setStreet(char* newStreet);
	char* getStreet() const;

	void setHomeNum(int newHomeNum);
	int getHomeNum() const;

	void setAptNum(int newAptNum);
	int getAptNum() const;

	void show() const;

};

#endif //_ADDRESS_H