#ifndef CRUDFUNCTION_H
#define CRUDFUNCTION_H
#include "Customer.h"
#include "Container.h"
#include "Basic.h"
#include "Heavy.h"
#include "Liquid.h"
#include "Refrigerated.h"
#include "Ship.h"

void displayAllCust(vector<Customer>);
vector<Customer> deleteCust(vector<Customer>, int);
void insertNewCust(vector<Customer>);
void displayAllShip(vector<Ship>);
vector<Ship> deleteShip(vector<Ship>,int);
void insertVewShip(vector<Ship>);


#endif // !CRUDFUNCTION_H

