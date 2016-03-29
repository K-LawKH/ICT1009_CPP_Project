#include <string>
#include <iostream>
#include <sstream>
#include "Container.h"
using namespace std;

//Contructors
Container::Container() {

}
Container::Container(string type, int amount, bool isSpecial, string specialProperties) {
	this->type = type;
	this->amount = amount;
	this->isSpecial = isSpecial;
	this->specialProperties = specialProperties;
}

//Getters & Setters
string Container::getType() const { return this->type; }
void Container::setType(string type) { this->type = type; }

int Container::getAmount() const { return this->amount; }
void Container::setAmount(int amount) { this->amount = amount; }

bool Container::getIsSpecial() const { return this->isSpecial; }
void Container::setIsSpecial(bool isSpecial) { this->isSpecial = isSpecial; }

string Container::getSpecialProperties() const { return this->specialProperties; }
void Container::setSpecialProperties(string properties) { this->specialProperties = properties; }
