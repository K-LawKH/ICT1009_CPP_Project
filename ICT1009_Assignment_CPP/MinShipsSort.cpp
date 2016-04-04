#include "Basic.h"
#include "Container.h"
#include "Heavy.h"
#include "Liquid.h"
#include "Refrigerated.h"
#include "MinShipsSort.h"
#include "Logger.h"
#include <algorithm>
#include <iostream>
#include "Sorting.h"
using namespace std;

vector<ValidShips> sortShips(vector<Customer> custList, vector<Ship> &shipList)
{
	vector<ValidShips> validShipsList;
	for (auto &i : custList)
	{
		ValidShips temp;
		temp.cust = i;
		for (auto &j : shipList)
		{
			if (i.getPortName() == j.getPort() && i.getDate() >= j.getDate())
			{
				temp.shipList.push_back(&j);
			}
		}
		if (temp.shipList.size() == 0)
		{
			cout << "No ships for " << i.getName() << endl;
		}
		else
		{
			validShipsList.push_back(temp);
		}
	}
	return validShipsList;
}

bool custCmp(ValidShips v1, ValidShips v2)
{
	return (v1.cust.getDate() < v2.cust.getDate());
}

vector<ValidShips> sortCustByDate(vector<ValidShips> validShipsList)
{
	sort(validShipsList.begin(), validShipsList.end(), custCmp);
	return validShipsList;
}

bool shipCmp(Ship *s1, Ship *s2)
{
	return (s1->getMaxLoad() > s2->getMaxLoad());
}

vector<ValidShips> sortShipsByCapacity(vector<ValidShips> validShipsList)
{
	for (auto &i : validShipsList)
	{
		sort(i.shipList.begin(), i.shipList.end(), shipCmp);
	}
	return validShipsList;
}

void printUsedShips(vector<Ship> &shipListIn) {
	cout << "List of ships used:" << endl;
	for (auto &i : shipListIn) {
		if (i.getCurrentBasicLoad() + i.getCurrentHeavyLoad() + i.getCurrentLiquidLoad() + i.getCurrentRefrigLoad()
			+ i.getCurrentSpecialBasic() + i.getCurrentSpecialHeavy() + i.getCurrentSpecialLiquid() + i.getCurrentSpecialRefrig() != 0) {
			cout << i.getShipName() << endl;
			cout << "Basic: " << i.getCurrentBasicLoad() << "/" << i.getBasicLoad() << endl;
			cout << "Liquid: " << i.getCurrentLiquidLoad() << "/" << i.getLiquidLoad() << endl;
			cout << "Heavy: " << i.getCurrentHeavyLoad() << "/" << i.getHeavyLoad() << endl;
			cout << "Refrigerated: " << i.getCurrentRefrigLoad() << "/" << i.getRefrigeratedLoad() << endl;
			cout << "Special: " << i.getCurrentSpecialTotal() << "/" << i.getSpecialLoad() << endl <<endl;

		}
	}

}

void printUnusedShips(vector<Ship> &shipListIn) {
	cout << "List of unused ships:" << endl;
	for (auto &i : shipListIn) {
		if (i.getCurrentBasicLoad() + i.getCurrentHeavyLoad() + i.getCurrentLiquidLoad() + i.getCurrentRefrigLoad()
			+ i.getCurrentSpecialBasic() + i.getCurrentSpecialHeavy() + i.getCurrentSpecialLiquid() + i.getCurrentSpecialRefrig() == 0) {
			cout << i.getShipName() << endl;
		
		}
	}
	
}
vector<Ship> minTimeShipsSort(vector<Customer> custList, vector<Ship>shipList)
{
	//Sort shipList and custList based on earliest date
	shipList = returnSortedShips(shipList);
	custList = returnSortedCust(custList);
	// Map each customer to a vector of valid ships
	vector<ValidShips> validShipsList = sortShips(custList, shipList);
	// Sort customers by date (earliest date first)
	validShipsList = sortCustByDate(validShipsList);
	shipList = fillFun(validShipsList, shipList);

	printUsedShips(shipList);
	//iterate through list of ships, identify ships not used.
	printUnusedShips(shipList);
	return shipList;
}

vector<Ship> minShipsSort(vector<Customer> custList, vector<Ship> shipList)
{
	// Map each customer to a vector of valid ships
	vector<ValidShips> validShipsList = sortShips(custList, shipList);
	
	// Sort customers by date (earliest date first), sort valid ships by capacity (largest max capacity first)
	validShipsList = sortCustByDate(validShipsList);
	validShipsList = sortShipsByCapacity(validShipsList);
	// Fill customers
	shipList = fillFun(validShipsList, shipList); //take note that this shiplist, unlike the java version, returns empty ships too
	//iterate through list of ships, identify ships used.
	printUsedShips(shipList);
    //iterate through list of ships, identify ships not used.
	printUnusedShips(shipList);


	return shipList;
}

void tracker(string customerName, int containers, string shipName, int containerType) {\
	string containerName;
	string details;
	switch (containerType) {
	case 8:
		containerName = " refrigerated (special) containers in ";
		break;
	case 7:
		containerName = " heavy (special) containers in ";
		break;
	case 6:
		containerName = " liquid (special) containers in ";
		break;
	case 5:
		containerName = " basic (special) containers in ";
		break;
	case 4:
		containerName = " refrigerated containers in ";
		break;
	case 3:
		containerName = " heavy containers in ";
		break;
	case 2:
		containerName = " liquid containers in ";
		break;
	case 1:
		containerName = " basic containers in ";
		break;
	}

	if (containers != 0) {
		Logger l(customerName);
		l.logFill(customerName + " has " + to_string(containers) + containerName + shipName);
	}
	else { //else nothing was filled into this ship
		cout << "No room to carry any" << containerName << shipName << endl;
	}	
	
}

vector<Ship> fillFun(vector<ValidShips> input, vector<Ship> &shipListIn) 
{

	//Refrig Special Loop
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "refrig" && j->getIsSpecial() == true) {
				cout << "Filling " << i.cust.getName() << "'s refrigerated (special) containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." <<endl;
					int amountFilled = amount;
					amount = k->setCurrentSpecialRefrig(amount);
					amountFilled = amountFilled - amount;

					tracker(i.cust.getName(), amountFilled, k->getShipName(), 8);

					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." <<endl << endl;
						break;
					}
				}
				if (amount != 0) {
					cout << "Failed to fit " << amount << " refrigerated (special) containers for " << i.cust.getName() << endl << endl;
				}
				break; //break after finding the correct container type
			}
		}
	}

	//Heavy Special Loop
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "heavy" && j->getIsSpecial() == true) {
				cout << "Filling " << i.cust.getName() << "'s heavy (special) containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." << endl;
					int amountFilled = amount;
					amount = k->setCurrentSpecialHeavy(amount);
					amountFilled = amountFilled - amount;

					tracker(i.cust.getName(), amountFilled, k->getShipName(), 7);
					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." << endl << endl;
						break;
					}
				}
				if (amount != 0) {
					cout << "Failed to fit " << amount << " heavy (special) containers for " << i.cust.getName() << endl << endl;
				}
				break; //break after finding the correct container type
			}
		}
	}

	//Liquid Special Loop
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "liquid" && j->getIsSpecial() == true) {
				cout << "Filling " << i.cust.getName() << "'s liquid (special) containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." << endl;
					int amountFilled = amount;
					amount = k->setCurrentLiquidLoad(amount);
					amountFilled = amountFilled - amount;

					tracker(i.cust.getName(), amountFilled, k->getShipName(), 6);
					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." <<endl << endl;
						break;
					}
				}
				if (amount != 0) {
					cout << "Failed to fit " << amount << " liquid (special) containers for " << i.cust.getName() << endl << endl;
				}
				break; //break after finding the correct container type
			}
		}
	}

	//Basic Special Loop
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "basic" && j->getIsSpecial() == true) {
				cout << "Filling " << i.cust.getName() << "'s basic (special) containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." << endl;
					int amountFilled = amount;
					amount = k->setCurrentSpecialBasic(amount);
					amountFilled = amountFilled - amount;

					tracker(i.cust.getName(), amountFilled, k->getShipName(), 5);
					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." << endl << endl;
						break;
					}
				}
				if (amount != 0) {
					cout << "Failed to fit " << amount << " basic (special) containers for " << i.cust.getName() << endl << endl;
				}
				break; //break after finding the correct container type
			}
		}
	}

	//Refrig Loop
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "refrig" && j->getIsSpecial() == false) {
				cout << "Filling " << i.cust.getName() << "'s refrigerated containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." << endl;
					int amountFilled = amount;
					amount = k->setCurrentRefrigLoad(amount);
					amountFilled = amountFilled - amount;

					tracker(i.cust.getName(), amountFilled, k->getShipName(), 4);
					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." << endl << endl;
						break;
					}
				}
				if (amount != 0) {
					cout << "Failed to fit " << amount << " refrigerated containers for " << i.cust.getName() << endl << endl;
				}
				break; //break after finding the correct container type
			}
		}
	}

	//Heavy Loop
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "heavy" && j->getIsSpecial() == false) {
				cout << "Filling " << i.cust.getName() << "'s heavy containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." << endl;
					int amountFilled = amount;
					amount = k->setCurrentHeavyLoad(amount);
					amountFilled = amountFilled - amount;

					tracker(i.cust.getName(), amountFilled, k->getShipName(), 3);
					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." << endl << endl;
						break;
					}
				}
				if (amount != 0) {
					cout << "Failed to fit " << amount << " heavy containers for " << i.cust.getName() << endl << endl;
				}
				break; //break after finding the correct container type
			}
		}
	}

	//Liquid Loop
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "liquid" && j->getIsSpecial() == false) {
				cout << "Filling " << i.cust.getName() << "'s liquid containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." << endl;
					int amountFilled = amount;
					amount = k->setCurrentLiquidLoad(amount);
					amountFilled = amountFilled - amount;

					tracker(i.cust.getName(), amountFilled, k->getShipName(), 2);
					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." << endl << endl;
						break;
					}
				}
				if (amount != 0) {
					cout << "Failed to fit " << amount << " liquid containers for " << i.cust.getName() << endl << endl;
				}
				break; //break after finding the correct container type
			}
		}
	}

	//Basic Loop
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "basic" && j->getIsSpecial() == false) {
				cout << "Filling " << i.cust.getName() << "'s basic containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." << endl;
					int amountFilled = amount;
					amount = k->setCurrentBasicLoad(amount);
					amountFilled = amountFilled - amount;

					tracker(i.cust.getName(), amountFilled, k->getShipName(), 8);
					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." << endl << endl;
						break;
					}
				}
				if (amount != 0) {
					cout << "Failed to fit " << amount << " basic containers for " << i.cust.getName() << endl << endl;
				}
				break; //break after finding the correct container type
			}
		}
	}
	return shipListIn;
}