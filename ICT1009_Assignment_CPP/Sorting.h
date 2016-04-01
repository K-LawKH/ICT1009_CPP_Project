#ifndef SORTING_H
#define SORTING_H
#include <vector>
#include <string>
#include "Customer.h"
#include "Ship.h"
#include <string>
using namespace std;
//Sorting
bool checkMinDateShips(Ship, Ship);
int indexOfEarliestDateShips(vector<Ship>);
vector<Ship> returnUnsortedShips(vector<Ship>, int);
vector<Ship> returnSortedShips(vector<Ship>);

bool checkMinDateCust(Customer, Customer);
int indexOfEarliestDateCust(vector<Customer>);
vector<Customer> returnUnsortedCust(vector<Customer>, int);
vector<Customer> returnSortedCust(vector<Customer>);
#endif