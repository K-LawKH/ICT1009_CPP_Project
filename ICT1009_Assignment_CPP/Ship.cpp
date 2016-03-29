#include <string>
#include <iostream>
#include <sstream>
#include "Ship.h"
using namespace std;

//Empty Constructor
Ship::Ship() { this->shipName = ""; }
//Constructor with everything
Ship::Ship(string shipName, string owner, double value, string company, int maxLoad, int basicLoad, double basicPrice, 
	int heavyLoad, double heavyPrice, int liquidLoad, double liquidPrice, int refrigLoad, double refrigPrice,
	int specialLoad, double specialPrice, string country, string port, int day, int month, int year)
{
	this->shipName = shipName;
	this->owner = owner;
	this->shipValue = value;
	this->company = company;

	this->maxLoad = maxLoad;
	this->basicLoad = basicLoad;
	this->basicPrice = basicPrice;
	this->heavyLoad = heavyLoad;
	this->heavyPrice = heavyPrice;
	this->liquidLoad = liquidLoad;
	this->liquidPrice = liquidPrice;
	this->refrigeratedLoad = refrigLoad;
	this->refrigeratedPrice = refrigPrice;
	this->specialLoad = specialLoad;
	this->specialPrice = specialPrice;

	this->country = country;
	this->port = port;
	this->day = day;
	this->month = month;
	this->year = year;
}
//Constructor without special and refrigerated
Ship::Ship(string shipName, string owner, double value, string company, int maxLoad, int basicLoad, double basicPrice,
	int heavyLoad, double heavyPrice, int liquidLoad, double liquidPrice ,string country, string port, int day, int month, int year)
{
	this->shipName = shipName;
	this->owner = owner;
	this->shipValue = value;
	this->company = company;

	this->maxLoad = maxLoad;
	this->basicLoad = basicLoad;
	this->basicPrice = basicPrice;
	this->heavyLoad = heavyLoad;
	this->heavyPrice = heavyPrice;
	this->liquidLoad = liquidLoad;
	this->liquidPrice = liquidPrice;

	this->country = country;
	this->port = port;
	this->day = day;
	this->month = month;
	this->year = year;
}


//Getters & Setters
string Ship::getShipName() const { return this->shipName; }
void Ship::setShipName(string name) { this->shipName = name; }
string Ship::getOwner() const { return this->owner; }
void Ship::setOwner(string owner) { this->owner = owner; }
double Ship::getShipValue() const { return this->shipValue; }
void Ship::setShipValue(double value) { this->shipValue = value; }
string Ship::getCompany() const { return this->company; }
void Ship::setCompany(string company) { this->company = company; }
string Ship::getCountry() const { return this->country; }
void Ship::setCountry(string country) { this->country = country; }
string Ship::getPort() const { return this->port; }
void Ship::setPort(string port) { this->port = port; }

int Ship::getMaxLoad() const { return this->maxLoad; }
void Ship::setMaxLoad(int load) { this->maxLoad = load; }
int Ship::getBasicLoad() const { return this->basicLoad; }
void Ship::setBasicLoad(int load) { this->basicLoad = load; }
int Ship::getHeavyLoad() const { return this->heavyLoad; }
void Ship::setHeavyLoad(int load) { this->heavyLoad = load; }
int Ship::getLiquidLoad() const { return this->liquidLoad; }
void Ship::setLiquidLoad(int load) { this->liquidLoad = load; }
int Ship::getRefrigeratedLoad() const { return this->refrigeratedLoad; }
void Ship::setRefrigeratedLoad(int load) { this->refrigeratedLoad = load; }
int Ship::getSpecialLoad() const { return this->specialLoad; }
void Ship::setSpecialLoad(int load) { this->specialLoad = load; }

double Ship::getBasicPrice() const { return this->basicPrice; }
void Ship::setBasicPrice(double price) { this->basicPrice = price; }
double Ship::getHeavyPrice() const { return this->heavyPrice; }
void Ship::setHeavyPrice(double price) { this->heavyPrice = price; }
double Ship::getLiquidPrice() const { return this->liquidPrice; }
void Ship::setLiquidPrice(double price) { this->liquidPrice = price; }
double Ship::getRefrigeratedPrice() const { return this->refrigeratedPrice; }
void Ship::setRefrigeratedePrice(double price) { this->refrigeratedPrice = price; }
double Ship::getSpecialPrice() const { return this->specialPrice; }
void Ship::setSpecialPrice(double price) { this->specialPrice = price; }

double Ship::getCurrentCost() const { return this->currentCost; }
void Ship::setCurrentCost(double cost) { this->currentCost = cost; }

int Ship::getCurrentMaxLoad() const { return this->currentMaxLoad; }
void Ship::setCurrentMaxLoad(int load) { this->currentMaxLoad = load; }
int Ship::getCurrentBasicLoad() const { return this->currentBasicLoad; }
void Ship::setCurrentBasicLoad(int load) { this->currentBasicLoad = load; }
int Ship::getCurrentHeavyLoad() const { return this->currentHeavyLoad; }
void Ship::setCurrentHeavyLoad(int load) { this->currentHeavyLoad = load; }
int Ship::getCurrentRefrigLoad() const { return this->currentRefrigLoad; }
void Ship::setCurrentRefrigLoad(int load) { this->currentRefrigLoad = load; }
int Ship::getCurrentLiquidLoad() const { return this->currentLiquidLoad; }
void Ship::setCurrentLiquidLoad(int load) { this->currentLiquidLoad = load; }

int Ship::getCurrentSpecialTotal() const { return this->currentSpecialTotal; }
void Ship::setCurrentSpecialTotal(int load) { this->currentSpecialTotal = load; }
int Ship::getCurrentSpecialBasic() const { return this->currentSpecialBasic; }
void Ship::setCurrentSpecialBasic(int  load) { this->currentSpecialBasic = load; }
int Ship::getCurrentSpecialHeavy() const { return this->currentSpecialHeavy; }
void Ship::setCurrentSpecialHeavy(int load) { this->currentSpecialHeavy = load; }
int Ship::getCurrentSpecialLiquid() const { return this->currentSpecialLiquid; }
void Ship::setCurrentSpecialLiquid(int load) { this->currentSpecialLiquid = load; }
int Ship::getCurrentSpecialRefrig() const { return this->currentSpecialRefrig; }
void Ship::setCurrentSpecialRefrig(int load) { this->currentSpecialRefrig = load; }

bool Ship::getBasicIsFull() const { return this->basicIsFull; }
void Ship::setBasicIsFull(bool flag) { this->basicIsFull = flag; }
bool Ship::getHeavyIsFull() const { return this->heavyIsFull; }
void Ship::setHeavyIsFull(bool flag) { this->heavyIsFull = flag; }
bool Ship::getLiquidIsFull() const { return this->liquidIsFull; }
void Ship::setLiquidIsFull(bool flag) { this->liquidIsFull = flag; }
bool Ship::getRefrigIsFull() const { return this->refrigIsFull; }
void Ship::setRefrigIsFull(bool flag) { this->refrigIsFull = flag; }
bool Ship::getSpecialIsFull() const { return this->specialIsFull; }
void Ship::setSpecialIsFull(bool flag) { this->specialIsFull = flag; }

//Methods
string Ship::getDate() {
	stringstream ss;
	if (this->day >= 1 && this->day <= 9) {
		ss << "0" << this->day << "-";
	}
	else {
		ss << this->day << "-";
	}

	if (this->month >= 1 && this->month <= 9) {
		ss << "0" << this->month << "-";
	}
	else {
		ss << this->month << "-";
	}

	ss << this->year << " 00:00:00";

	return ss.str();
}
void Ship::setDate(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

bool Ship::isShipFull() { return false; }
void Ship::checkFull() { }
