#define _CRT_SECURE_NO_WARNING
#ifndef _VENDOR_H
#define _VENDOR_H

#include <iostream>
using namespace std;

#include "Address.h"
class product;
class feedback;
class Costumer;

#pragma warning (disable: 4996)

const int MAX_LEN = 20;

class vendor
{
private:
	char* userName;
	char* password;
	address homeAddress;
	const product** allProducts;
	const feedback** allFeedbacks;
	int productAmount;
	int feedbackAmount;

public:
	vendor(char* userName, char* password, const address& address, int productAmount = 0, int feedbackAmount = 0);	//why const address
	vendor(const vendor&)=delete;
	~vendor();

	void setUserName(const char* name);
	const char* getUserName() const;

	void setPassword(const char* newPassword);
	char* getPassword() const;

	void setHomeAddress(address& newHomeAddress);
	address& getHomeAddress();

	void addProduct(const product& newProduct);
	const product** getProducts() const;

	void addFeedback(const feedback& newFeedback);
	const feedback** getfeedback() const;

	int getProductAmount() const;
	int getFeedbackAmount() const;

	void showProducts() const;
};

#endif // !_VENDOR_H

//*********************************************************************//

void addVendor(vendor** allVendors, int* vendorsSize);			//option 2 from main
void addPdtToVdr(vendor** allVendors, int vendorSize);			//option 3 from main
void addFeedback(Costumer** allCostumers, int costumerSize, vendor** allVendors, int vendorsSize);	//option 4 from main
