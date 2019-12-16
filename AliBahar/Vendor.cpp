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

	for (int i = 0; i < productAmount; i++)
		delete allProducts[i];
	delete[] allProducts;

	for (int i = 0; i < feedbackAmount; i++)
		delete allFeedbacks[i];
	delete[] allFeedbacks;

}

void vendor::setUserName(const char* name)
{
	delete[] userName;
	userName = new char[strlen(name) + 1];
	strcpy(userName, name);
}

const char* vendor::getUserName() const
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
		temp[i] = allProducts[i];
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
		temp[i] = allFeedbacks[i];
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

int vendor::getFeedbackAmount() const
{
	return feedbackAmount;
}

void vendor::showProducts() const
{
	for (int i = 0; i < productAmount; i++)
		cout << i + 1 << ". " << allProducts[i]->getName() << " " << allProducts[i]->getPrice() << "¥" << endl;
}

//**************************FUNCTIONS FROM MAIN*******************************************//

void addVendor(vendor ** allVendors, int * vendorsSize)
{
	char userName[MAX_LEN], password[MAX_LEN], state[MAX_ADD], city[MAX_ADD], street[MAX_ADD];
	int homeNum, aptNum;

	cout << "Please enter costumer's username: MAX 20";		//check valid name
	cin.ignore();
	cin.getline(userName, MAX_LEN);	

	cout << "Please enter costumer's password: MAX 20";		//check valid pass
	cin.ignore();
	cin.getline(password, MAX_LEN);

	cout << "Please enter costumer's state: MAX 20";		//check valid state
	cin.ignore();
	cin.getline(state, MAX_LEN);

	cout << "Please enter costumer's city: MAX 20";			//check valid city
	cin.ignore();
	cin.getline(city, MAX_LEN);

	cout << "Please enter costumer's street: MAX 20";		//check valid street
	cin.ignore();
	cin.getline(street, MAX_LEN);

	cout << "Please enter costumer's home number: ";		//check valid home number
	cin.ignore();
	cin >> homeNum;

	cout << "Please enter costumer's apartment number: ";	//check valid apt num
	cin.ignore();
	cin >> aptNum;

	allVendors[(*vendorsSize) - 1] = new vendor(userName, password, address(state, city, street, homeNum, aptNum));
	*vendorsSize++;
	allVendors = new vendor*[*vendorsSize];
	//cpy arr
}

void addPdtToVdr(vendor** allVendors, int vendorSize)		//from main
{//gets an arr of vendors and its size, search for the wanted vendor and then add a product to his list.]
	int i = 0, flagVendor = 0;

	cout << "Press 1 to choose the curr vendor, or press 0 to the next one." << endl;
	while (!flagVendor && i < vendorSize)				//print every time vendor's name, if press 1 go out the loop. vendor num i-1
	{
		cout << "Vendor's name: " << allVendors[i]->getUserName() << endl;
		cin >> flagVendor;
		i++;
	}
	
	//char vendorName[MAX_LEN];
	//cout << "Enter vendor's name: ";
	//cin.getline(vendorName, MAX_LEN);
	//cout << endl;
	//int i = 0;
	//while (strcmp(allVendors[i]->getUserName(), vendorName) != 0 && i < vendorSize)
	//	i++;

	if (!flagVendor)
	{
		cout << "No vendor has been chosen. Return to main menu." << endl;
		return;
	}

	eCategory category;
	char pdtName[MAX_LEN];
	int c, price, serialNumber;

	cout << "Enter product category:\n 1. Kids \n 2. Electricity \n 3. Office \n 4. Clothing" << endl;
	cin >> c;
	category = (eCategory)c;

	cout << "Enter product name: (no more then 20 letters)";
	cin.getline(pdtName, MAX_LEN);
	cout << endl;

	cout << "Enter product's price: ";
	cin >> price;
	cout << endl;

	cout << "Enter product's serial number: ";		//check valid
	cin >> serialNumber;
	cout << endl;
	
	allVendors[i-1]->addProduct(product(category, pdtName, price, serialNumber, *allVendors[i-1]));
}

void addFeedback(Costumer** allCostumers, int costumerSize, vendor** allVendors, int vendorSize)		//from main
{//gets arr of costumers and its size, search for the wanted costumer, then choose the vendor and add a feedback

	//cout << "Enter costumer's name: ";
	//cin.getline(costumerName, MAX_LEN);
	//cout << endl;
	//while (strcmp(allCostumers[i]->getUserName(), costumerName) != 0 && i < costumerSize)		//check if costumer exist
	//	i++;

	int i = 0, flagCostumer = 0, j = 0, flagVendor = 0, v = 0;

	cout << "Press 1 to choose the curr costumer, or press 0 to the next one." << endl;
	while (!flagCostumer && i < costumerSize)				//print every time costumer's name, if press 1 go out the loop. costumer num i-1
	{
		cout << "Costumer's name: " << allCostumers[i]->getUserName() << endl;
		cin >> flagCostumer;
		i++;
	}

	if (!flagCostumer)	
	{
		cout << "Costumer DOES NOT exist in the system." << endl;
		return;
	}

	//cout << "Enter vendor's name: ";
	//cin.getline(vendorName, MAX_LEN);
	//cout << endl;
	//while (strcmp(allCostumers[i]->getAllVendors()[j]->getUserName(), vendorName) != 0 && j < allCostumers[i]->getVendorsAmount())
	//	//there is costumer, check if there is vendor at costumer's vendors
	//	j++;
	int vendorsAmount = allCostumers[i-1]->getVendorsAmount();			//gets the amount of vendors in curr costumer
	const vendor** currVendors = allCostumers[i - 1]->getAllVendors();			//gets the list of vendors of curr costumer

	cout << "Press 1 to choose the curr vendor, or press 0 to the next one." << endl;
	while (!flagVendor && j < vendorsAmount)				//print every time vendor's name, if press 1 go out the loop. vendor num j-1
	{
		cout << "Vendor's name: " << currVendors[j]->getUserName() << endl;
		cin >> flagVendor;
		j++;
	}

	if (!flagVendor)
	{
		cout << "No vendor has been chosen. Return to main menu." << endl;
		return;
	}

	//there is costumer and vendor in his list, find the vendor in all vendors from main, and ask for date and feedback
	
	while (currVendors[j] != allVendors[v])
		v++;

	char date[MAX_LEN], feedbackDes[MAX_FEE];

	cout << "Enter today's date name: ";			//check valid
	cin.getline(date, MAX_LEN);
	cout << endl;

	cout << "Enter your feedback: ";
	cin.getline(feedbackDes, MAX_FEE);
	cout << endl;

	allVendors[v]->addFeedback(feedback(date, feedbackDes, *allCostumers[i-1], *allVendors[v]));

	//allCostumers[i]->getAllVendors()[j]->addFeedback(feedback(date, feedbackDes, allCostumers[i], allCostumers[i]->getAllVendors()[j]));
}