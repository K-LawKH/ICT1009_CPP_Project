#include <iostream>
#include <string>
#include <cstdlib>
#include<iomanip>
#include "FileDialog.h"
#include "importXML.h"

using namespace std;
using std::setw;
#include"concol.h"
int menu() {
	int choice = 0;
	cout << endl;
	cout << "+--------------------------------------------------------------------+" << endl;
	cout << "|               Welcome to the Ship Scheduling System                |" << endl;
	cout << "+--------------------------------------------------------------------+" << endl;
	cout << endl;
	cout << "Please select one of the following option: " << endl;
	cout << red << "1: Select the folder path. " << endl;
	cout << red << "0: Exit program." << endl;
	cout << cyan << "Enter your choice: ";
	cin >> choice;

	return choice;
}

int main(int argc, const char *argv[])
{
	SetConsoleTitle("1009 CPP Assignment");
	string path;
	int choice = menu();
	switch (choice)
	{
	case 1:
		path = BrowseFolder();
		cout << white << path << endl;
		importXML(path);
		system("pause");
	case 0:
		exit(0);
	default:
		break;
	}

	return 0;
}

//void main5()
//{
//	char a[30];
//	SetConsoleTitle(L"1009 CPP Assignment");
//	concol b = concol(backcolor());
//	cout << red << "Hello" << endl;
//	setcolor(red, yellow);
//	cout << "Hello2" << endl;
//	setcolor(cyan, b);
//	cout << "Hello3" << endl;
//	cout << blue << "Enter a word ";
//	cin >> green >> a;
//	cout << pink << "You entered " << yellow << a << endl;
//
//
//	cout << "Print in Columns";
//	cout << setw(10) << "This" <<setw(10) << "is" <<setw(10) << "a" << setw(10) << "test" << '\n';
//
//
//	system("pause");
//}

