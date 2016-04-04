#ifndef  LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger
{
private:
	ofstream out;
	ifstream in;
	string fileName;
	string saveLine;
	inline bool fileExists(const string&);
public:
	Logger(string);
	void forCustomer(string);
	void logFill(string);
	void read(string);
};
#endif // ! LOGGER_H
