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

	//void setCostumer(const Costumer& newCtm);
	const Costumer* getCostumer() const;
	//void setVendor(vendor* newVen);
	const vendor* getVendor() const;
	void setDate(const char* newDate);
	const char* getDate() const;
	void setDescription(const char* newDcp);
	const char* getDescription() const;

};

#endif //_FEEDBACK_H