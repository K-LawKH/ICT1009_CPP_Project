#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <vector>
#include "Container.h"
using namespace std;

class Customer {
	friend ostream& operator<<(ostream&, const Customer&);
private:
	string id, name, company, country, portName;
	int age, day, month, year;
	vector<Container *> containerArray;
public:
	//Constructors
	Customer();
	Customer(string, string, int, string, string, string, int, int, int, vector<Container *>);
	//Getters & Setters
	string getID() const;
	void setID(string);
	string getName() const;
	int getAge() const;
	string getCompany() const;
	string getCountry() const;
	string getPortName() const;
	void setName(string);
	void setAge(int);
	void setCompany(string);
	void setCountry(string);
	void setPortName(string);
	vector<Container *> getContainerArray() const;
	void setContainerArray(vector<Container *>);

	//Methods
	bool updateCust(string, int, string);
	string getDate();
	void setDate(int, int, int);
	int getDay();
	int getMonth();
	int getYear();
};
#endif // ! CUSTOMER_H

