#include "Basic.h"
#include "Container.h"
#include "Heavy.h"
#include "Liquid.h"
#include "Refrigerated.h"
#include "MinShipsSort.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

bool checkMinDateShips(Ship s1, Ship s2) {// returns index of min num in vec
	if (s1.getDay() < s2.getDay() && s1.getMonth() <= s2.getMonth() && s1.getYear() <= s2.getYear())
	{
		return true;
	}
	if (s1.getDay() >= s2.getDay() && s1.getMonth() < s2.getMonth() && s1.getYear() <= s2.getYear())
	{
		return true;
	}
	if (s1.getYear() < s2.getYear())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int indexOfEarliestDateShips(vector<Ship> shipList)
{
	int getIndex = 0;
	Ship temp;
	//need put today's(current date)
	temp.setDate(1, 4, 2016);
	string min = temp.getDate();
	for (int i = 0; i < shipList.size(); i++)
	{
		if (checkMinDateShips(shipList[i], temp) == true)
		{
			temp = shipList[i];
			getIndex = i;
		}
	}
	return getIndex;
}

vector<Ship> returnUnsortedShips(vector<Ship> shipList, int index)
{
	shipList.erase(shipList.begin() + index);
	/*for (int i = 0; i < shipList.size(); i++)
	{
	cout << "Return unsorted [" << i << "] " << shipList[i].getShipName() << endl;
	}*/
	return shipList;
}

vector<Ship> returnSortedShips(vector<Ship> shipList)
{
	int index = -1;
	Ship ship;
	int indexOfMinDate;
	int tempCheck = -1;
	vector<Ship>tempShipList;

	while (shipList.size() != 0)
	{
		//cout << "Array size is: " << shipList.size() << endl;
		//cout << "Index: " << index << endl;
		index++;
		if (index == shipList.size())
		{
			index = 0;
		}

		if (index != shipList.size())
		{
			indexOfMinDate = indexOfEarliestDateShips(shipList);
			ship = shipList[indexOfMinDate];
			//cout << "Earliest date is: " << shipList[indexOfMinDate].getDate() << endl;
			shipList = returnUnsortedShips(shipList, indexOfMinDate);
			tempShipList.push_back(ship);
			index = 0;
		}
	}
	return tempShipList;
}


bool checkMinDateCust(Customer c1, Customer c2) {// returns index of min num in vec
	if (c1.getDay() < c2.getDay() && c1.getMonth() <= c2.getMonth() && c1.getYear() <= c2.getYear())
	{
		return true;
	}
	if (c1.getDay() >= c2.getDay() && c1.getMonth() < c2.getMonth() && c1.getYear() <= c2.getYear())
	{
		return true;
	}
	if (c1.getYear() < c2.getYear())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int indexOfEarliestDateCust(vector<Customer> custList)
{
	int getIndex = 0;
	Customer temp;
	//need put today's(current date)
	temp.setDate(1, 4, 2016);
	string min = temp.getDate();
	for (int i = 0; i < custList.size(); i++)
	{
		if (checkMinDateCust(custList[i], temp) == true)
		{
			temp = custList[i];
			getIndex = i;
		}
	}
	return getIndex;
}

vector<Customer> returnUnsortedCust(vector<Customer> custList, int index)
{
	custList.erase(custList.begin() + index);
	/*for (int i = 0; i < shipList.size(); i++)
	{
	cout << "Return unsorted [" << i << "] " << shipList[i].getShipName() << endl;
	}*/
	return custList;
}

vector<Customer> returnSortedCust(vector<Customer> custList)
{
	int index = -1;
	Customer cust;
	int indexOfMinDate;
	int tempCheck = -1;
	vector<Customer>tempCustList;

	while (custList.size() != 0)
	{
		//cout << "Array size is: " << shipList.size() << endl;
		//cout << "Index: " << index << endl;
		index++;
		if (index == custList.size())
		{
			index = 0;
		}

		if (index != custList.size())
		{
			indexOfMinDate = indexOfEarliestDateCust(custList);
			cust = custList[indexOfMinDate];
			//cout << "Earliest date is: " << shipList[indexOfMinDate].getDate() << endl;
			custList = returnUnsortedCust(custList, indexOfMinDate);
			tempCustList.push_back(cust);
			index = 0;
		}
	}
	return tempCustList;
}