#include "Basic.h"
#include "Container.h"
#include "Customer.h"
#include "Heavy.h"
#include "Liquid.h"
#include "Refrigerated.h"
#include "Ship.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef struct DestinationType
{
	vector<Customer> custList;
	vector<Ship> shipList;
}Destination;

// Get all of the ports that need to be visited
vector<string> getRequiredPorts(vector<Customer> custList)
{
	vector<string> requiredPorts;
	for (auto &i : custList)
	{
		if (find(requiredPorts.begin(), requiredPorts.end(), i.getPortName()) != requiredPorts.end())
		{
			requiredPorts.push_back(i.getPortName());
		}
	}
	return requiredPorts;
}

vector<Destination> groupDestinations(vector<Customer> custList, vector<Ship> shipList, vector<string> requiredPorts)
{
	vector<Destination> destinationList;
	for (auto &i : requiredPorts)
	{
		Destination tempDest;
		for (auto &j : custList)
		{
			if (j.getPortName() == i)
			{
				tempDest.custList.push_back(j);
			}
		}

		for (auto &j : shipList)
		{
			if (j.getPort() == i)
			{
				tempDest.shipList.push_back(j);
			}
		}
		destinationList.push_back(tempDest);
	}
	return destinationList;
}

bool custCmp(Customer c1, Customer c2)
{
	return (c1.getDate() < c2.getDate());
}

vector<Customer> sortCust(vector<Customer> custList)
{
	sort(custList.begin(), custList.end(), custCmp);
	return custList;
}

bool shipCmp(Ship s1, Ship s2)
{
	return (s1.getDate() < s2.getDate());
}

vector<Ship> sortShip(vector<Ship> shipList)
{
	sort(shipList.begin(), shipList.end(), shipCmp);
	return shipList;
}

vector<Destination> sortDestinations(vector<Destination> destinationList)
{
	for (auto &i : destinationList)
	{
		i.custList = sortCust(i.custList);
		i.shipList = sortShip(i.shipList);
	}
	return destinationList;
}

vector<Ship> minShipsSort(vector<Customer> custList, vector<Ship> shipList)
{
	// Create test data
	vector<Container *> temp;
	temp.push_back(new Basic("basic", 20, false, "\0"));
	temp.push_back(new Basic("basic_special", 30, true, "explosive,toxic"));
	temp.push_back(new Refrigerated("refrig", 60, false, "\0"));
	temp.push_back(new Liquid("liquid", 60, false, "\0"));
	Customer("001", "Ng James", 23, "Apple", "China", "Shanghai", 3, 10, 2015, temp);


	vector<string> requiredPorts = getRequiredPorts(custList);
	vector<Destination> destinationList = groupDestinations(custList, shipList, requiredPorts);
	destinationList = sortDestinations(destinationList);

	return shipList;
}

/*
group customers according to destination
reject custopmers with a destination that doesnt exit
within each group, reject customers that have a due date that cannot be met by any ship going to that destination
Order ships and customers according to their due date [earliest]
fill in said order


*/