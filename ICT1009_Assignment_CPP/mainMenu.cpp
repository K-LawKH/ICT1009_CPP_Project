#include <string>
#include <cstdlib>
#include "FileDialog.h"
#include "Customer.h"
using namespace std;

int menu() {
	int choice = 0;
	cout << endl;
	cout << "+--------------------------------------------------------------------+" << endl;
	cout << "|               Welcome to the Ship Scheduling System                |" << endl;
	cout << "+--------------------------------------------------------------------+" << endl;
	cout << endl;
	cout << "Please select one of the following option: " << endl;
	cout << "1: Select the folder path. " << endl;
	cout << "0: Exit program." << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	return choice;
}

int main(int argc, const char *argv[])
{
	string path;
	int choice = menu();
	switch (choice)
	{
	case 1:
		path = BrowseFolder();
		cout << path << endl;
	case 0:
		exit(0);
	default:
		break;
	}

	return 0;
}