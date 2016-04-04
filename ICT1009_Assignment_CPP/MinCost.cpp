#include "Basic.h"
#include "Container.h"
#include "Heavy.h"
#include "Liquid.h"
#include "Logger.h"
#include "MinCost.h"
#include "Refrigerated.h"
#include "Sorting.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

vector<mcValidShips> mcSortShips(vector<Customer> custList, vector<Ship> &shipList)
{
	vector<mcValidShips> validShipsList;
	for (auto &i : custList)
	{
		mcValidShips temp;
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

void mcPrintUsedShips(vector<Ship> &shipListIn) {
	std::cout << std::fixed << std::setprecision(2);
	cout << "List of ships used:" << endl;
	for (auto &i : shipListIn) {
		if (i.getCurrentBasicLoad() + i.getCurrentHeavyLoad() + i.getCurrentLiquidLoad() + i.getCurrentRefrigLoad()
			+ i.getCurrentSpecialBasic() + i.getCurrentSpecialHeavy() + i.getCurrentSpecialLiquid() + i.getCurrentSpecialRefrig() != 0) {
			cout << i.getShipName() << endl;
			cout << "Basic: " << i.getCurrentBasicLoad() << "/" << i.getBasicLoad() << endl;
			cout << "Liquid: " << i.getCurrentLiquidLoad() << "/" << i.getLiquidLoad() << endl;
			cout << "Heavy: " << i.getCurrentHeavyLoad() << "/" << i.getHeavyLoad() << endl;
			cout << "Refrigerated: " << i.getCurrentRefrigLoad() << "/" << i.getRefrigeratedLoad() << endl;
			cout << "Special: " << i.getCurrentSpecialTotal() << "/" << i.getSpecialLoad() << endl;
			cout << "Total cost: $" << i.getCurrentCost() << endl << endl;
			cout << "============Breadkdown============" << endl;
			cout << "Basic: " << i.getBasicPrice() * i.getCurrentBasicLoad()<<endl;
			cout << "Liquid: " << i.getLiquidPrice() * i.getCurrentLiquidLoad() << endl;
			cout << "Heavy: " << i.getHeavyPrice() * i.getCurrentHeavyLoad() << endl;
			cout << "Refrigerated: " << i.getRefrigeratedPrice() * i.getCurrentRefrigLoad() << endl;
			cout << "Special: " << i.getSpecialPrice() * i.getCurrentSpecialTotal() << endl << endl;
			
		}
	}

}

void mcPrintUnusedShips(vector<Ship> &shipListIn) {
	cout << "List of unused ships:" << endl;
	for (auto &i : shipListIn) {
		if (i.getCurrentBasicLoad() + i.getCurrentHeavyLoad() + i.getCurrentLiquidLoad() + i.getCurrentRefrigLoad()
			+ i.getCurrentSpecialBasic() + i.getCurrentSpecialHeavy() + i.getCurrentSpecialLiquid() + i.getCurrentSpecialRefrig() == 0) {
			cout << i.getShipName() << endl;

		}
	}

}


bool mcCustCmp(mcValidShips v1, mcValidShips v2)
{
	return (v1.cust.getDate() < v2.cust.getDate());
}

vector<mcValidShips> mcSortCustByDate(vector<mcValidShips> validShipsList)
{
	sort(validShipsList.begin(), validShipsList.end(), mcCustCmp);
	return validShipsList;
}

vector<mcValidShips> mcSortShipsByCost(vector<mcValidShips> validShipsList, int input)
{
	switch (input) {
	case 1:
		for (auto &i : validShipsList)
		{
			sort(i.shipList.begin(), i.shipList.end(), basicShipCmp);
			reverse(i.shipList.begin(), i.shipList.end());
		}
		break;
	case 2:
		for (auto &i : validShipsList)
		{
			sort(i.shipList.begin(), i.shipList.end(), heavyShipCmp);
			reverse(i.shipList.begin(), i.shipList.end());
		}
		break;
	case 3:
		for (auto &i : validShipsList)
		{
			sort(i.shipList.begin(), i.shipList.end(), refrigShipCmp);
			reverse(i.shipList.begin(), i.shipList.end());
		}
		break;
	case 4:
		for (auto &i : validShipsList)
		{
			sort(i.shipList.begin(), i.shipList.end(), liquidShipCmp);
			reverse(i.shipList.begin(), i.shipList.end());
		}
		break;
	case 5:
		for (auto &i : validShipsList)
		{
			sort(i.shipList.begin(), i.shipList.end(), specialShipCmp);
			reverse(i.shipList.begin(), i.shipList.end());
		}
		break;
	}
	
	return validShipsList;
}

bool basicShipCmp(Ship *s1, Ship *s2)
{
	return (s1->getBasicPrice() > s2->getBasicPrice());
}
bool heavyShipCmp(Ship *s1, Ship *s2)
{
	return (s1->getHeavyPrice() > s2->getHeavyPrice());
}
bool refrigShipCmp(Ship *s1, Ship *s2)
{
	return (s1->getRefrigeratedPrice() > s2->getRefrigeratedPrice());
}
bool liquidShipCmp(Ship *s1, Ship *s2)
{
	return (s1->getLiquidPrice() > s2->getLiquidPrice());
}
bool specialShipCmp(Ship *s1, Ship *s2)
{
	return (s1->getSpecialPrice() > s2->getSpecialPrice());
}

vector<Ship> minCost(vector<Customer> custList, vector<Ship> shipList)
{
	// Map each customer to a vector of valid ships
	vector<mcValidShips> validShipsList = mcSortShips(custList, shipList);

	// Sort customers by date (earliest date first), sort valid ships by capacity (largest max capacity first)
	validShipsList = mcSortCustByDate(validShipsList);
	validShipsList = mcSortShipsByCost(validShipsList, 1);
	// Fill customers
	shipList = mcFillFun(validShipsList, shipList); //take note that this shiplist, unlike the java version, returns empty ships too
												  //iterate through list of ships, identify ships used.
	mcPrintUsedShips(shipList);
	//iterate through list of ships, identify ships not used.
	mcPrintUnusedShips(shipList);


	return shipList;
}



void mcTracker(string customerName, int containers, string shipName, int containerType) {
	
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

vector<Ship> mcFillFun(vector<mcValidShips> input, vector<Ship> &shipListIn)
{
	//Refrig Special Loop
	input = mcSortShipsByCost(input, 5);
	for (auto &i : input) {
		for (auto &j : i.cust.getContainerArray()) {
			if (j->getType() == "refrig" && j->getIsSpecial() == true) {
				cout << "Filling " << i.cust.getName() << "'s refrigerated (special) containers... " << endl;
				int amount = j->getAmount();
				for (auto &k : i.shipList) {
					cout << "Attempting to fill " << k->getShipName() << " with " << amount << " containers." << endl;
					int amountFilled = amount;
					amount = k->setCurrentSpecialRefrig(amount);
					amountFilled = amountFilled - amount;
					double total = (amountFilled)* k->getSpecialPrice();
					k->setCurrentCost(total);

					mcTracker(i.cust.getName(), amountFilled, k->getShipName(), 8);

					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." << endl << endl;
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
					double total = (amountFilled)* k->getSpecialPrice();
					k->setCurrentCost(total);

					mcTracker(i.cust.getName(), amountFilled, k->getShipName(), 7);
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
					double total = (amountFilled)* k->getSpecialPrice();
					k->setCurrentCost(total);

					mcTracker(i.cust.getName(), amountFilled, k->getShipName(), 6);
					if (amount == 0) {
						//done with this type of container for this customer
						cout << "All containers loaded. No error." << endl << endl;
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
					double total = (amountFilled)* k->getSpecialPrice();
					k->setCurrentCost(total);

					mcTracker(i.cust.getName(), amountFilled, k->getShipName(), 5);
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
	input = mcSortShipsByCost(input, 3);
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
					double total = (amountFilled)* k->getRefrigeratedPrice();
					k->setCurrentCost(total);

					mcTracker(i.cust.getName(), amountFilled, k->getShipName(), 4);
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
	input = mcSortShipsByCost(input, 2);
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
					double total = (amountFilled)* k->getHeavyPrice();
					k->setCurrentCost(total);

					mcTracker(i.cust.getName(), amountFilled, k->getShipName(), 3);
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
	input = mcSortShipsByCost(input, 4);
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
					double total = (amountFilled) * k->getLiquidPrice();
					k->setCurrentCost(total);

					mcTracker(i.cust.getName(), amountFilled, k->getShipName(), 2);
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
	input = mcSortShipsByCost(input, 1);
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
					double total = (amountFilled)* k->getBasicPrice();
					k->setCurrentCost(total);


					cout << "basic price; " << k->getBasicPrice();
					mcTracker(i.cust.getName(), amountFilled, k->getShipName(), 8);
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