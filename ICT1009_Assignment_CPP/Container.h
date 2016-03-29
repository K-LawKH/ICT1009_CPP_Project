#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
using namespace std;

class Container {
private:
	string type;
	int amount;
	bool isSpecial;
	string specialProperties;
public:
	Container();
	Container(string, int, bool, string);
	string getType() const;
	int getAmount() const;
	bool getIsSpecial() const;
	string getSpecialProperties() const;
	void setType(string);
	void setAmount(int);
	void setIsSpecial(bool);
	void setSpecialProperties(string);
};
#endif // !CONTAINER_H

