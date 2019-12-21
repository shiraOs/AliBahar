#define _CRT_SECURE_NO_WARNING
#ifndef _FEEDBACK_H
#define _FEEDBACK_H

#include <iostream>
using namespace std;

class Costumer;
class vendor;

#pragma warning (disable: 4996)

const int MAX_FEE = 100;

class feedback
{
private:
	const Costumer* const costumerP;
	const vendor* const vendorP;
	char* date;
	char* description;

public:
	feedback(const char* newDate, const char* newDescription, const Costumer& newCtm, const vendor& newVen);
	feedback(const feedback&) = delete;
	~feedback();

	const Costumer* getCostumer() const;
	const vendor* getVendor() const;
	char* getDate() const;
	void setDescription(const char* newDcp);
	char* getDescription() const;
};

#endif //_FEEDBACK_H