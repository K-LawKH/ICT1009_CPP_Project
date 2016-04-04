#ifndef MINCOST_H
#define MINCOST_H

#include <vector>
#include <string>
#include "Customer.h"
#include "Ship.h"
using namespace std;

typedef struct mcValidShipsType
{
	Customer cust;
	vector<Ship *> shipList;
}mcValidShips;


vector<mcValidShips> mcSortShips(vector<Customer>, vector<Ship>&);
void mcPrintUsedShips(vector<Ship>&);
void mcPrintUnusedShips(vector<Ship>&);
bool mcCustCmp(mcValidShips, mcValidShips);
vector<mcValidShips> mcSortCustByDate(vector<mcValidShips>);
vector<mcValidShips> mcSortShipsByCost(vector<mcValidShips> validShipsList, int input);


bool basicShipCmp(Ship *s1, Ship *s2);
bool heavyShipCmp(Ship *s1, Ship *s2);
bool refrigShipCmp(Ship *s1, Ship *s2);
bool liquidShipCmp(Ship *s1, Ship *s2);
bool specialShipCmp(Ship *s1, Ship *s2);

vector<Ship> minCost(vector<Customer> custList, vector<Ship> shipList);

void mcTracker(string, int, string, int);


vector<Ship> mcFillFun(vector<mcValidShips>, vector<Ship>&);
#endif