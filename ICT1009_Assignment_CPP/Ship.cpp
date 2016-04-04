#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "Ship.h"
using namespace std;

//Empty Constructor
Ship::Ship() { 
	this->shipName = ""; 
	currentMaxLoad = 0, currentBasicLoad = 0, currentHeavyLoad = 0, currentRefrigLoad = 0, currentLiquidLoad = 0;
	currentSpecialTotal = 0;
	currentSpecialBasic = 0;
	currentSpecialHeavy = 0;
	currentSpecialRefrig = 0;
	currentSpecialLiquid = 0;
	double currentCost = 0;
}
//Constructor with everything
Ship::Ship(string shipName, string owner, double value, string company, int maxLoad, int basicLoad, double basicPrice, 
	int heavyLoad, double heavyPrice, int liquidLoad, double liquidPrice, int refrigLoad, double refrigPrice,
	int specialLoad, double specialPrice, string country, string port, int day, int month, int year)
{
	currentMaxLoad = 0, currentBasicLoad = 0, currentHeavyLoad = 0, currentRefrigLoad = 0, currentLiquidLoad = 0;
	currentSpecialTotal = 0;
	currentSpecialBasic = 0;
	currentSpecialHeavy = 0;
	currentSpecialRefrig = 0;
	currentSpecialLiquid = 0;
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
	currentMaxLoad = 0, currentBasicLoad = 0, currentHeavyLoad = 0, currentRefrigLoad = 0, currentLiquidLoad = 0;
	currentSpecialTotal = 0;
	currentSpecialBasic = 0;
	currentSpecialHeavy = 0;
	currentSpecialRefrig = 0;
	currentSpecialLiquid = 0;
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

int Ship::getDay()
{
	return this->day;
}
int Ship::getMonth()
{
	return this->month;
}
int Ship::getYear()
{
	return this->year;
}

double Ship::getCurrentCost() const { return this->currentCost; }


void Ship::setCurrentCost(double value) 
{
	this->currentCost += value;
}

int Ship::getCurrentBasicLoad() const { return this->currentBasicLoad; }
int Ship::setCurrentBasicLoad(int load) 
{ 
	int remainder = 0;
	// can fit
	if ((basicLoad - currentBasicLoad) >= load)
	{
		currentBasicLoad += load;
	}
	// cannot fit
	else
	{
		remainder = load - (basicLoad - currentBasicLoad);
		currentBasicLoad = basicLoad;
	}
	checkFull();
	return remainder;
}
int Ship::getCurrentHeavyLoad() const { return this->currentHeavyLoad; }
int Ship::setCurrentHeavyLoad(int load)
{
	int remainder = 0;
	// can fit
	if ((heavyLoad - currentHeavyLoad) >= load)
	{
		currentHeavyLoad += load;
	}
	// cannot fit
	else
	{
		remainder = load - (heavyLoad - currentHeavyLoad);
		currentHeavyLoad = heavyLoad;
	}
	checkFull();
	return remainder;
}
int Ship::getCurrentRefrigLoad() const { return this->currentRefrigLoad; }
int Ship::setCurrentRefrigLoad(int load)
{
	int remainder = 0;
	// can fit
	if ((refrigeratedLoad - currentRefrigLoad) >= load)
	{
		currentRefrigLoad += load;
	}
	// cannot fit
	else
	{
		remainder = load - (refrigeratedLoad - currentRefrigLoad);
		currentRefrigLoad = refrigeratedLoad;
	}
	checkFull();
	return remainder;
}
int Ship::getCurrentLiquidLoad() const { return this->currentLiquidLoad; }
int Ship::setCurrentLiquidLoad(int load)
{
	int remainder = 0;
	// can fit
	if ((liquidLoad - currentLiquidLoad) >= load)
	{
		currentLiquidLoad += load;
	}
	// cannot fit
	else
	{
		remainder = load - (liquidLoad - currentLiquidLoad);
		currentLiquidLoad = liquidLoad;
	}
	checkFull();
	return remainder;
}

int Ship::getCurrentSpecialTotal() const { return this->currentSpecialTotal; }
int Ship::getCurrentSpecialBasic() const { return this->currentSpecialBasic; }
int Ship::setCurrentSpecialBasic(int load)
{
	int remainder = 0;
	// can fit
	if ((basicLoad - currentBasicLoad) >= load && (specialLoad - currentSpecialTotal) >= load)
	{
		currentBasicLoad += load;
		currentSpecialTotal = load;
	}
	// cannot fit
	else
	{
		int max = min((basicLoad - currentBasicLoad), (specialLoad - currentSpecialTotal));
		remainder = load - max;
		currentBasicLoad += max;
		currentSpecialTotal += max;
	}
	checkFull();
	return remainder;
}
int Ship::getCurrentSpecialHeavy() const { return this->currentSpecialHeavy; }
int Ship::setCurrentSpecialHeavy(int load)
{
	int remainder = 0;
	// can fit
	if ((heavyLoad - currentHeavyLoad) >= load && (specialLoad - currentSpecialTotal) >= load)
	{
		currentHeavyLoad += load;
		currentSpecialTotal = load;
	}
	// cannot fit
	else
	{
		int max = min((heavyLoad - currentHeavyLoad), (specialLoad - currentSpecialTotal));
		remainder = load - max;
		currentHeavyLoad += max;
		currentSpecialTotal += max;
	}
	checkFull();
	return remainder;
}
int Ship::getCurrentSpecialLiquid() const { return this->currentSpecialLiquid; }
int Ship::setCurrentSpecialLiquid(int load)
{
	int remainder = 0;
	// can fit
	if ((liquidLoad - currentLiquidLoad) >= load && (specialLoad - currentSpecialTotal) >= load)
	{
		currentLiquidLoad += load;
		currentSpecialTotal = load;
	}
	// cannot fit
	else
	{
		int max = min((liquidLoad - currentLiquidLoad), (specialLoad - currentSpecialTotal));
		remainder = load - max;
		currentLiquidLoad += max;
		currentSpecialTotal += max;
	}
	checkFull();
	return remainder;
}
int Ship::getCurrentSpecialRefrig() const { return this->currentSpecialRefrig; }
int Ship::setCurrentSpecialRefrig(int load)
{
	int remainder = 0;
	// can fit
	if ((refrigeratedLoad - currentRefrigLoad) >= load && (specialLoad - currentSpecialTotal) >= load)
	{
		currentRefrigLoad += load;
		currentSpecialTotal = load;
	}
	// cannot fit
	else
	{
		int max = min((refrigeratedLoad - currentRefrigLoad), (specialLoad - currentSpecialTotal));
		remainder = load - max;
		currentRefrigLoad += max;
		currentSpecialTotal += max;
	}
	checkFull();
	return remainder;
}

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
void Ship::setDate(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

bool Ship::isShipFull() 
{
	return (basicIsFull && heavyIsFull && refrigIsFull && specialIsFull && liquidIsFull); 
}
void Ship::checkFull() 
{
	if (currentBasicLoad >= basicLoad) basicIsFull = true;
	else basicIsFull = false;
	if (currentHeavyLoad >= heavyLoad) heavyIsFull = true;
	else heavyIsFull = false;
	if (currentRefrigLoad >= refrigeratedLoad) refrigIsFull = true;
	else refrigIsFull = false;
	if (currentSpecialTotal >= specialLoad) specialIsFull = true;
	else specialIsFull = false;
	if (currentLiquidLoad >= liquidLoad) liquidIsFull = true;
	else liquidIsFull = false;
}

ostream& operator<<(ostream& out, const Ship& aShip) {
	out << setfill('-') << setw(40) << "-" << endl;
	out << "Ship Name: " << aShip.shipName << endl;
	out << setfill('-') << setw(40) << "-" << endl;
	out << "Owner: " << aShip.owner << setfill('\0') << setw(10) << "Value in billion: " << aShip.shipValue << endl;
	out << "Company: " << aShip.company << endl;
	out << endl;
	out << "Destination: " << endl;
	out << "Country: " << aShip.country << setfill('\0') << setw(10) << "Port: " << aShip.port << endl;
	out << "Dateline: " << aShip.day << "/" << aShip.month << "/" << aShip.year << endl;
	out << endl;
	out << "Container Details: " << endl;
	out << "Max Load: " << aShip.maxLoad;
	out << "Basic Load: " << aShip.basicLoad << setfill('\0') << setw(10) << "Price: " << aShip.basicPrice << endl;
	out << "Heavy Load: " << aShip.heavyLoad << setfill('\0') << setw(10) << "Price: " << aShip.heavyPrice << endl;
	out << "Liquid Load: " << aShip.liquidLoad << setfill('\0') << setw(10) << "Price: " << aShip.liquidPrice << endl;
	if (aShip.refrigeratedLoad > 0) {
		out << "Regfrigerated Load: " << aShip.refrigeratedLoad << setfill('\0') << setw(10) << "Price: " << aShip.refrigeratedPrice << endl;
	}
	if (aShip.specialLoad > 0) {
		out << "Special Load: " << aShip.specialLoad << setfill('\0') << setw(10) << "Price: " << aShip.specialPrice << endl;
	}
	return out;
}