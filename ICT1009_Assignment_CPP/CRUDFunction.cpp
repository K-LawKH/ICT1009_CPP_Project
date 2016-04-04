#include <iostream>
#include <string>
#include "CRUDFunction.h"
using namespace std;

void displayAllCust(vector<Customer> custArr) {
	system("cls");
	for (int i = 0; i < custArr.size(); i++) {
		cout << custArr[i];
	}
}

vector<Customer> deleteCust(vector<Customer> custArr, int pos) {
	string tempId = custArr[pos].getID();
	custArr.erase(custArr.begin() + pos);
	cout << endl;
	cout << "Customer ID " << tempId << " had been removed." << endl;

	return custArr;
}

void displayAllShip(vector<Ship> shipsArr) {
	system("cls");
	for (int i = 0; i < shipsArr.size(); i++) {
		cout << shipsArr[i];
	}
}

vector<Ship> deleteShip(vector<Ship> shipsArr, int pos) {
	string shipName = shipsArr[pos].getShipName();
	shipsArr.erase(shipsArr.begin() + pos);
	cout << endl;
	cout << "Ship Name: " << shipName << " had been deleted." << endl;

	return shipsArr;
}

vector<Ship> addNewShip(vector<Ship> shipsArr) {
}