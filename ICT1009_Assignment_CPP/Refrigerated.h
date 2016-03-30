#ifndef REFRIGERATED_H
#define REFRIGERATED_H
#include <string>
#include "Heavy.h"
using namespace std;

class Refrigerated : public Heavy {
public:
	Refrigerated() :Heavy() {};
	Refrigerated(string type, int amount, bool isSpecial, string specialProperties) : Heavy(type, amount,
		isSpecial, specialProperties) {};
};
#endif // !REFRIGERATED_H

