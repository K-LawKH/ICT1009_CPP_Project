#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <iomanip>
#include "FileDialog.h"
#include "CRUDFunction.h"
using namespace std;

void header() {
	cout << "+--------------------------------------------------------------------+" << endl;
	cout << "|               Welcome to the Ship Scheduling System                |" << endl;
	cout << "+--------------------------------------------------------------------+" << endl;
	cout << endl;
}

int menu() {
	char choice = '\0';
	header();
	cout << "Please select one of the following option: " << endl;
	cout << "1: Select the folder path. " << endl;
	cout << "0: Exit program." << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	return choice;
}

void customerListMenu(vector<Customer> custArr) {
	int choice;
	bool flag = true;

	while (flag == true) {
		system("cls");
		header();
		cout << "Please select the customer you wish to view:" << endl;
		for (int i = 0; i < custArr.size(); i++) {
			cout << (i + 1) << ": " << custArr[i].getName() << endl;
		}
		cout << "0: Back to pervious menu" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 0) {
			flag = false;
		} 
		else if ((choice - 1) <= custArr.size()) {
			system("cls");
			cout << custArr[(choice - 1)];
			system("pause");
		}
		else {
			cout << "Invalid Choice! Please Enter Again!" << endl;
			system("pause");
		}

	}
}

void shipListMenu(vector<Ship> shipsArr) {
	int choice;
	bool flag = true;

	while (flag == true) {
		system("cls");
		header();
		cout << "Please select the ship you wish to view:" << endl;
		for (int i = 0; i < shipsArr.size(); i++) {
			cout << (i + 1) << ": " << shipsArr[i].getShipName() << endl;
		}
		cout << "0: Back to pervious menu" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 0) {
			flag = false;
		}
		else if ((choice - 1) <= shipsArr.size()) {
			system("cls");
			cout << shipsArr[(choice - 1)];
			system("pause");
		}
		else {
			cout << "Invalid Choice! Please Enter Again!" << endl;
			system("pause");
		}
	}
}

vector<Customer> customerDeleteMenu(vector<Customer> custArr) {
	int choice;
	bool flag = true;

	while (flag == true) {
		system("cls");
		header();
		cout << "Please select the customer you wish to delete:" << endl;
		for (int i = 0; i < custArr.size(); i++) {
			cout << (i + 1) << ": " << custArr[i].getName() << endl;
		}
		cout << "0: Back to pervious menu" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 0) {
			flag = false;
		}
		else if ((choice - 1) <= custArr.size()) {
			custArr = deleteCust(custArr, (choice - 1));
			system("pause");
		}
		else {
			cout << "Invalid Choice! Please Enter Again!" << endl;
			system("pause");
		}
	}

	return custArr;
}

vector<Customer> customerMenu(vector<Customer> custArr) {
	char choice;
	bool flag = true;

	while (flag == true) {
		system("cls");
		header();
		cout << "Please select one of the following option: " << endl;
		cout << "1: View All Customer Details" << endl;
		cout << "2: View Selected Customer Details" << endl;
		cout << "3: Update Selected Customer Details" << endl;
		cout << "4: Delete Selected Customer Details" << endl;
		cout << "5: Insert a new Customer" << endl;
		cout << "0: Back to pervious menu" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case '1':
			//View All Customer Info
			displayAllCust(custArr);
			system("pause");
			break;
		case '2':
			//View Selected Customer Details
			customerListMenu(custArr);
			break;
		case '3':
			//Update Selected Customer Details
			//updateCustInfo(cust);
			break;
		case '4':
			//Delete Selected Customer Details
			custArr = customerDeleteMenu(custArr);
			break;
		case '5':
			//Insert new customer
		case '0':
			flag = false;
			break;
		default:
			cout << "Invalid Choice! Please Enter Again!" << endl;
			system("pause");
			break;
		}
	}

	return custArr;
}

vector<Ship> shipDeleteMenu(vector<Ship> shipsArr) {
	int choice;
	bool flag = true;

	while (flag == true) {
		system("cls");
		header();
		cout << "Please select the customer you wish to delete:" << endl;
		for (int i = 0; i < shipsArr.size(); i++) {
			cout << (i + 1) << ": " << shipsArr[i].getShipName() << endl;
		}
		cout << "0: Back to pervious menu" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 0) {
			flag = false;
		}
		else if ((choice - 1) <= shipsArr.size()) {
			shipsArr = deleteShip(shipsArr, (choice - 1));
			system("pause");
		}
		else {
			cout << "Invalid Choice! Please Enter Again!" << endl;
			system("pause");
		}
	}

	return shipsArr;
}

vector<Ship> shipMenu(vector<Ship> shipsArr){
	char choice;
	bool flag = true;

	while (flag == true) {
		system("cls");
		header();
		cout << "Please select one of the following option: " << endl;
		cout << "1: View All Ship Details" << endl;
		cout << "2: View Selected Ship Details" << endl;
		cout << "3: Update Selected Ship Details" << endl;
		cout << "4: Delete Selected Ship Details" << endl;
		cout << "5: Insert a new Ship" << endl;
		cout << "0: Back to pervious menu" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case '1':
			//View All Ship Info
			displayAllShip(shipsArr);
			system("pause");
			break;
		case '2':
			//View Selected Customer Details
			shipListMenu(shipsArr);
			break;
		case '3':
			//Update Selected Customer Details
			//updateShipInfo(cust);
			break;
		case '4':
			//Delete Selected Ship Details
			shipsArr = shipDeleteMenu(shipsArr);
			break;
		case '5':
			//Insert new Ship
		case '0':
			flag = false;
			break;
		default:
			cout << "Invalid Choice! Please Enter Again!" << endl;
			system("pause");
			break;
		}
	}

	return shipsArr;
}

void mainMenu(vector<Customer> custArr, vector<Ship> shipsArr) {
	char choice;
	bool flag = true;

	while (flag == true) {
		system("cls");
		header();
		cout << "Please select one of the following option: " << endl;
		cout << "1: View, Update, Delete and Insert Customer" << endl;
		cout << "2: View, Update, Delete and Insert Ship" << endl;
		cout << "3: Scheduling of Containers" << endl;
		cout << "0: Back to pervious menu" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case '1':
			custArr = customerMenu(custArr);
			break;
		case '2':
			shipMenu(shipsArr);
			break;
		case '3':
			//Scheduling Part goes here
			break;
		case '0':
			flag = false;
			break;
		default:
			cout << "Invalid Choice! Please Enter Again!" << endl;
			system("pause");
			break;
		}

	}
}

int main(int argc, const char *argv[])
{
	bool flag = true;
	string path;
	vector<Customer> customerArr;
	vector<Container *> containerArr;
	vector<Container *> containerArr2;
	vector<Ship> shipsArr;
	containerArr.push_back(new Basic("Basic", 150, false, "\0"));
	containerArr.push_back(new Basic("Basic_Special", 100, true, "explosive"));
	Customer cust("001", "John", 29, "Ace Pte Ltd", "Singapore", "Tuas", 26, 8, 2016, containerArr);
	customerArr.push_back(cust);
	containerArr2.push_back(new Basic("Basic", 150, false, "\0"));
	containerArr2.push_back(new Heavy("Heavy", 200, false, "\0"));
	Customer cust2("002", "Bye", 32, "Beta Pte Ltd", "China", "ShangHai", 22, 1, 2016, containerArr2);
	customerArr.push_back(cust2);

	while (flag) {
		system("cls");
		char choice = menu();

		switch (choice)
		{
		case '1':
			path = BrowseFolder();
			cout << path << endl;
			system("pause");
			mainMenu(customerArr, shipsArr);
			break;
		case '0':
			flag = false;
			exit(0);
			break;
		default:
			cout << "Invalid Choice! Please Enter Again!" << endl;
			system("pause");
			break;
		}
	}
	
	return 0;
}