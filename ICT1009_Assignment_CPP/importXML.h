#pragma once
#using <System.Xml.dll>
#include <iostream>
#include "sstream"
#include <cstdlib>
#include <stdexcept>
#include <exception>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <dirent.h>
#include "Customer.h"
#include "Ship.h"
#include "Container.h"
#include "Basic.h"
#include "Heavy.h"
#include "Refrigerated.h"
#include "Liquid.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::IO;
using namespace System::Xml;
//need to load project with external lib (dirent.h)
using namespace std;

//NOTE: check if pass value is int or perfect string? 
//throw exception with filename and error

template<class EX>
class traced_error : virtual public std::exception, virtual public EX
{
public:
	traced_error(const std::string& file, int line, const EX& ex)
		: EX(ex),
		line_(line),
		file_(file)
	{
	}

	const char* what() const
	{
		std::stringstream ss;
		static std::string msg;
		ss << "File: " << file_ << " Line: " << line_ << " Error: " << EX::what();
		msg = ss.str().c_str();
		return msg.c_str();
	}

	int line_;
	std::string file_;
};

template<class EX> traced_error<EX> make_traced_error(const std::string& file, int line, const EX& ex)
{
	return traced_error<EX>(file, line, ex);
}


class my_exception : virtual public std::exception
{
public:
	my_exception() {};

	const char* what() const
	{
		return "Invalid Format (Double / Int)";
	}
};

class my_exception1 : virtual public std::exception
{
public:
	my_exception1() {};

	const char* what() const
	{
		return "Error, field cannot be null!";
	}
};

#define throwx(EX) (throw make_traced_error(__FILE__,__LINE__,EX))

//checking for null values
String^ isNull(String^ );

double checkForDouble(String^);
int checkForInt(String^);


int getxmlShipdata(std::string, vector<Ship>& );

int getxmlContainerdata(std::string containerFile, vector<Customer>& , vector<Container *> );


//checking if the file is an xml
bool checkIfXML(const std::string& );

//using a recursive method to get the all the files in seperate directories
int getdir(string dir, vector<string>&);


//check if container file is correct
int checkContainerFile(std::string );

//check if ship file is correct
int checkShipFile(std::string );

void printShips(vector<Ship>& );


void printCustomers(vector<Customer>& );

int importXML(string);



