#include "Vendor.h"
#include "Address.h"
#include "Product.h"
#include "Feedback.h"
#include "Costumer.h"

vendor::vendor(char* userName, char* password, const address& address, int productAmount, int feedbackAmount) :homeAddress(address)
{
	cout << "In Vendor's c'tor for " << userName << endl;

	setUserName(userName);
	setPassword(password);
}

//vendor::vendor(vendor& other)
//{
//	cout << "In Vendor's cpy c'tor for " << other.userName << endl;
//
//	setUserName(other.userName);
//	setPassword(other.password);
//	setHomeAddress(other.homeAddress);
//	productAmount = other.productAmount;
//	feedbackAmount = other.feedbackAmount;
//
//	for (int i = 0; i < productAmount; i++)
//		allProducts[i] = new product(*(other.allProducts[i]));
//
//	for (int i = 0; i < feedbackAmount; i++)
//		allFeedbacks[i] = new feedback(*(other.allFeedbacks[i]));
//
//}

vendor::~vendor()
{
	cout << "In Vendor's d'tor for " << userName << endl;

	delete[] userName;
	delete[] password;

	for (int i = 0; i < productAmount; i++)		//delete the original object of product
		delete allProducts[i];
	delete[] allProducts;

	for (int i = 0; i < feedbackAmount; i++)	//delete the original object of feedback
		delete allFeedbacks[i];
	delete[] allFeedbacks;

}

void vendor::setUserName(const char* name)
{
	delete[] userName;
	userName = new char[strlen(name) + 1];
	strcpy(userName, name);
}

char* vendor::getUserName() const
{
	return userName;
}

void vendor::setPassword(const char* newPassword)
{
	delete[] password;
	password = new char[strlen(newPassword) + 1];
	strcpy(password, newPassword);
}

char* vendor::getPassword() const
{
	return password;
}

void vendor::setHomeAddress(address& newHomeAddress)
{
	homeAddress = newHomeAddress; 
}

address& vendor::getHomeAddress()
{
	return homeAddress;
}

void vendor::addProduct(const product& newProduct)				//gets pointer to product. NOT OBJECT
{
	productAmount++;
	const product** temp = new const product*[productAmount];
	for (int i = 0; i < productAmount - 1; i++)
	{
		temp[i] = allProducts[i];
		allProducts[i] = nullptr;
	}
	temp[productAmount-1] = &newProduct;

	delete[] allProducts;
	allProducts = temp;
}

const product** vendor::getProducts() const
{
	return allProducts;
}

void vendor::addFeedback(const feedback& newFeedback)
{
	feedbackAmount++;
	const feedback** temp = new const feedback*[feedbackAmount];
	for (int i = 0; i < feedbackAmount - 1; i++)
	{
		temp[i] = allFeedbacks[i];
		allFeedbacks[i] = nullptr;
	}
	temp[feedbackAmount - 1] = &newFeedback;

	delete[] allFeedbacks;
	allFeedbacks = temp;
}

const feedback** vendor::getfeedback() const
{
	return allFeedbacks;
}

int vendor::getProductAmount() const
{
	return productAmount;
}

//int vendor::getFeedbackAmount() const
//{
//	return feedbackAmount;
//}

void vendor::showProducts() const
{
	for (int i = 0; i < productAmount; i++)
		cout << i + 1 << ". " << allProducts[i]->getName() << " " << allProducts[i]->getPrice() << "¥" << endl;
}

void vendor::showDetails() const
{
	cout << "User Name: " << this->userName << endl;
	cout << "Password: " << this->password << endl;
	this->homeAddress.show();
}

//**************************FUNCTIONS FROM MAIN*******************************************//

