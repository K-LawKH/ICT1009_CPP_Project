#include "Logger.h"

inline bool Logger::fileExists(const string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

Logger::Logger(string custName)
{
	fileName = custName + ".txt";
}


void Logger::forCustomer(string custName)
{
	fileName = custName + ".txt";
}

void Logger::logFill(string data)
{
	out.open(fileName, ios_base::app);
	if (!out)
	{
		cout << "Failed to open file." << endl;
	}
	else
	{
		out << data << endl;
		cout << "File written" << endl;
	}
	out.close();
}

void Logger::read(string fileName)
{
	in.open(fileName + ".txt");
	while (!in.eof())
	{
		getline(in, saveLine);
		cout << saveLine << endl;
	}
	
	in.close();
}