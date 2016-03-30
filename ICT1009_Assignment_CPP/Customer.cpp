#include <string>
#include <iostream>
#include <sstream>
#include "Customer.h"
using namespace std;

//Constructors
Customer::Customer() {
	this->id = "";
	this->name = "";
	this->age = 0;
	this->company = "";

	this->day = 26;
	this->month = 5;
	this->year = 2016;
}
Customer::Customer(string id, string name, int age, string company, string country, string port, 
	int day, int month, int year, vector<Container *> temp) {
	this->id = id;
	this->name = name;
	this->age = age;
	this->company = company;

	this->country = country;
	this->portName = port;

	this->day = day;
	this->month = month;
	this->year = year;

	this->containerArray = temp;
}

//Getters & Setters
string Customer::getID() const { return this->id; }
void Customer::setID(string id) { this->id = id;  }

string Customer::getName() const{ return this->name; }
void Customer::setName(string name) { this->name = name; }

int Customer::getAge() const { return this->age; }
void Customer::setAge(int age) { this->age = age; }

string Customer::getCompany() const{ return this->company; }
void Customer::setCompany(string company) { this->company = company; }

string Customer::getCountry() const { return this->country; }
void Customer::setCountry(string country) { this->country = country; }

string Customer::getPortName() const { return this->portName; }
void Customer::setPortName(string portName) { this->portName = portName; }

vector<Container *> Customer::getContainerArray() const { return this->containerArray; }
void Customer::setContainerArray(vector<Container *> temp) { this->containerArray = temp; }

//Methods
string Customer::getDate() {
	stringstream ss;
	ss << this->year << "-";

	if (this->month >= 1 && this->month <= 9) {
		ss << "0" << this->month << "-";
	}
	else {
		ss << this->month << "-";
	}

	if (this->day >= 1 && this->day <= 9) {
		ss << "0" << this->day;
	}
	else {
		ss << this->day;
	}

	ss << " 00:00:00";

	return ss.str();
}
void Customer::setDate(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

bool Customer::updateCust(string name, int age, string company) {
	return true;
}