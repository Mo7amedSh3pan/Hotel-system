
#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<strstream>
#include "primary.h"
#include "secondry.h"
#include "avilable list.h"
#include "Rooms.h"
#include "customer.h"

using namespace std;

int Room_number;
rooms r;
customer c;


void CustomerMedule() {
	system("CLS");

	cout << "Enter 1 to add customer" << endl;
	cout << "Enter 2 to remove customer\n";
	cout << "Enter 3 to Display customer's data\n";
	cout << "Enter 4 to searche about customer\n";
	cout << "Enter 5 to update customer\n";

	int choice;
	int id;
	cin >> choice;

	while (choice < 1 || choice > 5) {
		cout << "Invalid input\nplease try again\n";
		cin >> choice;
	}


	switch (choice) {
	case 1:
		c.insertInDataFile();
		break;
	case 2:
		cout << "enter Id that you want to delete\n"; cin >> id;
		c.DeleteById(id);
		break;
	case 3:
		c.read();
		break;
	case 4:
		c.searche();
		break;
	case 5:
		cout << "enter id\n"; cin >> id;
		c.update(id);
		break;
	}
}

void rooms_medule() {

	system("CLS");

	cout << "1 - add_rooms\n";
	cout << "2 - display_all_rooms\n";
	cout << "3 - searche_in_rooms\n";
	int choice;
	cin >> choice;
	while (choice != 1 && choice != 2 && choice != 3) {
		cout << "Invalid input\nplease try again\n";
		cin >> choice;
	}

	switch (choice) {
	case 1:
		r.add_rooms();
		break;
	case 2:
		r.display_all_rooms();
		break;
	case 3:
		r.searche_in_rooms();
		break;
	}
}

void firstWindo() {
	{
		cout << "-------------------------------------------------------" << endl;
		cout << "              HOTEL managment system				    " << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "1 - Customer Medule\n";
		cout << "2 - Rooms Medule\n";

	}

	int choice;
	cin >> choice;
	while (choice != 1 && choice != 2) {
		cout << "Invalid input\nplease try again\n";
		cin >> choice;
	}

	switch (choice) {
	case 1:
		CustomerMedule();
		break;
	case 2:
		rooms_medule();
		break;
	}

}

int main()
{
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();
	firstWindo();

}