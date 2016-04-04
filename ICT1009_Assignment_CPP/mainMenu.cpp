#include <string>
#include <cstdlib>
#include "FileDialog.h"
#include "Customer.h"
#include "MinShipsSort.h"
#include "Basic.h"
#include "Container.h"
#include "Heavy.h"
#include "Liquid.h"
#include "Refrigerated.h"
#include "Ship.h"
#include "Logger.h"
#include "concol.h"
using namespace std;

int menu() {
	int choice = 0;
	cout << endl;
	cout << green << "+--------------------------------------------------------------------+" << endl;
	cout << "|" << white << "               Welcome to the Ship Scheduling System                " << green << "|" << endl;
	cout << "+--------------------------------------------------------------------+" << endl;
	cout << endl;
	cout << green << "Please select one of the following option: " << endl
		<< white << "1. Display Ships and Containers" << endl
		<< "2. Display scheduling for minimum number of ships" << endl
		<< "3. Display scheduling for minimum cost and maximized ship load" << endl
		<< "4. Display scheduling for optimum solution (2 and 3 combined)" << endl
		<< "5. Display scheduling for minimum time" << endl
		<< "6. Display ships that are not full" << endl
		<< "7. Update container" << endl
		<< "8. Update ship" << endl
		<< "9. Save scheduling plan to disk" << endl
		<< "10. Track" << endl
		<< "11. Exit the program" << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	return choice;

}

int main(int argc, const char *argv[])
{
	// Create test data
	vector<Customer> custList;
	vector<Container *> temp;
	temp.push_back(new Basic("basic", 20, false, "\0"));
	temp.push_back(new Basic("basic", 30, true, "explosive,toxic"));
	temp.push_back(new Refrigerated("refrig", 60, false, "\0"));
	temp.push_back(new Liquid("liquid", 60, false, "\0"));
	Customer c1("001", "Ng James", 23, "Apple", "China", "Shanghai", 3, 10, 2015, temp);
	custList.push_back(c1);

	vector<Container *> temp2;
	temp2.push_back(new Basic("basic", 80, false, "\0"));
	temp2.push_back(new Heavy("heavy", 20, false, "\0"));
	temp2.push_back(new Heavy("heavy", 70, true, "explosive,toxic"));
	temp2.push_back(new Refrigerated("refrig", 20, false, "\0"));
	temp2.push_back(new Liquid("liquid", 5, false, "\0"));
	Customer c2("002", "Alvin Wong", 23, "HTC", "China", "Shanghai", 5, 11, 2015, temp2);
	custList.push_back(c2);

	vector<Container *> temp3;
	temp3.push_back(new Basic("basic", 120, false, "\0"));
	temp3.push_back(new Refrigerated("refrig", 300, true, "explosive,toxic"));
	temp3.push_back(new Heavy("heavy", 100, false, "\0"));
	temp3.push_back(new Liquid("liquid", 10, false, "\0"));
	Customer c3("003", "Michael Jackson", 23, "SIT", "USA", "Seattle", 5, 10, 2015, temp3);
	custList.push_back(c3);

	/*Ship(string shipName, string owner, double value, string company, int maxLoad, int basicLoad, double basicPrice,
	int heavyLoad, double heavyPrice, int liquidLoad, double liquidPrice, int refrigLoad, double refrigPrice,
	int specialLoad, double specialPrice, string country, string port, int day, int month, int year)*/

	vector<Ship> shipList;
	Ship s1("Titanic", "James Cameron", 2.0, "Paramount", 300, 300, 10.0,
		100, 20.0, 40, 80.0, 50, 40.0, 80, 20.0, "China", "Shanghai", 5, 10, 2015);
	Ship s2("Ace", "Bills Tom", 4.0, "Acess", 400, 400, 10.0,
		200, 30.0, 40, 80.0, 0, 0.0, 150, 0.0, "USA", "Seattle", 12, 12, 2015);
	Ship s3("Adda", "Charlie Wang", 10.0, "Adroit", 150, 150, 5.0,
		100, 20.0, 80, 0.0, 80, 0.0, 00, 0.0, "Ho Chi Minh", "Vietnam", 25, 4, 2015);
	Ship s4("S4", "James Cameron", 2.0, "Paramount", 300, 300, 10.0,
		100, 20.0, 40, 80.0, 50, 40.0, 80, 20.0, "China", "Shanghai", 2, 9, 2015);
	Ship s5("S5", "Bills Tom", 4.0, "Acess", 400, 400, 10.0,
		200, 30.0, 40, 80.0, 0, 0.0, 150, 0.0, "USA", "Seattle", 12, 12, 2014);
	Ship s6("S6", "James Cameron", 2.0, "Paramount", 300, 300, 10.0,
		100, 20.0, 40, 80.0, 50, 40.0, 80, 20.0, "China", "Shanghai", 5, 11, 2014);
	Ship s7("S7", "Bills Tom", 4.0, "Acess", 400, 400, 10.0,
		200, 30.0, 40, 80.0, 0, 0.0, 150, 0.0, "USA", "Seattle", 12, 12, 2013);
	shipList.push_back(s1);
	shipList.push_back(s2);
	shipList.push_back(s3);
	shipList.push_back(s4);
	shipList.push_back(s5);
	shipList.push_back(s6);
	shipList.push_back(s7);

	string path;
	while (1)
	{
		string yesOrNo = "y";
		int choice = menu();
		int trackerChoice;
		string name;
		Logger l(name);
		switch (choice)
		{
		case 1:
			path = BrowseFolder();
			cout << path << endl;
			break;

		case 3:
			shipList = minShipsSort(custList, shipList);
			cout << green << "Proceed back to menu? (y/n)." << white;
			cin >> yesOrNo;
			break;

		case 5:
			cout << green << "======== MINIMUM TIME SORT ========" << white << endl;
			minTimeShipsSort(custList, shipList);
			cout << green << "Proceed back to menu? (y/n)." << white;
			cin >> yesOrNo;
			break;

		case 11:
			cout << "Please enter which customer to view for tracking: " << endl;
			for (int i = 0; i < custList.size(); i++)
			{
				cout << i << "." << custList[i].getName() << endl;
			}
			cin >> trackerChoice;
			name = custList[trackerChoice].getName();
			l.read(name);
			cout << green << "Proceed back to menu? (y/n)." << white;
			cin >> yesOrNo;
			break;

		case 0:
			exit(0);
		default:
			break;
		}
	}

	return 0;
}