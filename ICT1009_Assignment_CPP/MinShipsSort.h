#ifndef MINSHIPSSORT_H
#define MINSHIPSSORT_H
#include <vector>
#include <string>
#include "Customer.h"
#include "Ship.h"
using namespace std;

typedef struct ValidShipsType
{
	Customer cust;
	vector<Ship *> shipList;
}ValidShips;

vector<ValidShips> sortCustByDate(vector<ValidShips>);
vector<Ship> minShipsSort(vector<Customer>, vector<Ship>);
vector<Ship>minTimeShipsSort(vector<Customer>, vector<Ship>);
vector<ValidShips> sortShips(vector<Customer>, vector<Ship>&);
bool custCmp(ValidShips, ValidShips);
bool shipCmp(Ship *, Ship *);
vector<Ship> fillFun(vector<ValidShips>, vector<Ship>&);
void printUsedShips(vector<Ship>&);
void printUnusedShips(vector<Ship>&);
void tracker(string, int, string, int);
#endif