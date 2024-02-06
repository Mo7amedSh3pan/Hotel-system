#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<strstream>
#include "primary.h"
#include "secondry.h"
#include "avilable list.h"

class rooms {
	char type[10];
	char status[10];
	int room_num;
	int price;
public:

	void add_rooms();

	void check_out(int roomnum);

	bool check_if_room_is_booked(int roomnum);

	void display_all_rooms();

	void searche_in_room_by_status();

	void searche_in_room_by_type();

	void searche_in_rooms();

};

void rooms::add_rooms() {

	fstream roomsfile;
	roomsfile.open("Rooms file.txt", ios::in | ios::out | ios::binary);

	rooms r;

	for (size_t roomnum = 1; roomnum <= 20; roomnum++)
	{
		strcpy_s(r.status, "empty");
		r.room_num = roomnum;
		if (roomnum <= 10) {
			strcpy_s(r.type, "single");
			r.price = 1000;
		}

		else {
			strcpy_s(r.type, "double");
			r.price = 2000;
		}

		roomsfile.seekp(0, ios::end);

		{
			short len;
			len = strlen(r.status);
			roomsfile.write((char*)&len, sizeof(short));
			roomsfile.write(r.status, strlen(r.status));

			len = strlen(r.type);
			roomsfile.write((char*)&len, sizeof(short));
			roomsfile.write(r.type, strlen(r.type));

			len = sizeof(r.room_num);
			roomsfile.write((char*)&len, sizeof(short));
			roomsfile.write((char*)&r.room_num, len);

			len = sizeof(r.price);
			roomsfile.write((char*)&len, sizeof(short));
			roomsfile.write((char*)&r.price, len);
		}

		roomsfile.clear();
	}
	cout << "$ $ $ $ $ $ $ $ $ $ $ $ 20 Room was added $ $ $ $ $ $ $ $ $ $ $ $\n";
	roomsfile.close();
}

void rooms::check_out(int roomnum) {

	fstream roomsfile;
	roomsfile.open("Rooms file.txt", ios::in | ios::out | ios::binary);

	roomsfile.seekg(0, ios::beg);
	rooms r;
	r.room_num = 0;
	short len;
	int i = 0;
	int offset = -1;
	do {
		if (i && roomnum == r.room_num) {

			roomsfile.seekp(offset, ios::beg);
			char status[10] = "empty";

			short len;
			len = strlen(status);
			roomsfile.write((char*)&len, sizeof(short));
			roomsfile.write(status, strlen(status));

			len = strlen(r.type);
			roomsfile.write((char*)&len, sizeof(short));
			roomsfile.write(r.type, strlen(r.type));

			len = sizeof(r.room_num);
			roomsfile.write((char*)&len, sizeof(short));
			roomsfile.write((char*)&r.room_num, len);

			len = sizeof(r.price);
			roomsfile.write((char*)&len, sizeof(short));
			roomsfile.write((char*)&r.price, len);

			roomsfile.clear();
			roomsfile.close();

			return;
		}
		{
			offset = roomsfile.tellg();

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.status, len);
			r.status[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.type, len);
			r.type[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.room_num, len);

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.price, len);
		}

		i++;

	} while (!roomsfile.eof());

	roomsfile.clear();
	roomsfile.close();
}

bool rooms::check_if_room_is_booked(int roomnum) {

	fstream roomsfile;
	roomsfile.open("Rooms file.txt", ios::in | ios::out | ios::binary);

	roomsfile.seekg(0, ios::beg);
	rooms r;
	r.room_num = 0;
	short len;
	int i = 0;
	int offset = -1;
	do {
		if (i && roomnum == r.room_num) {
			if (strcmp(r.status, "empty")) {
				roomsfile.clear();
				return false;
			}
			{
				roomsfile.seekp(offset, ios::beg);
				strcpy_s(r.status, "booke");

				short len;
				len = strlen(r.status);
				roomsfile.write((char*)&len, sizeof(short));
				roomsfile.write(r.status, strlen(r.status));

				len = strlen(r.type);
				roomsfile.write((char*)&len, sizeof(short));
				roomsfile.write(r.type, strlen(r.type));

				len = sizeof(r.room_num);
				roomsfile.write((char*)&len, sizeof(short));
				roomsfile.write((char*)&r.room_num, len);

				len = sizeof(r.price);
				roomsfile.write((char*)&len, sizeof(short));
				roomsfile.write((char*)&r.price, len);
			}

			roomsfile.clear();
			return true;
		}

		{
			offset = roomsfile.tellg();

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.status, len);
			r.status[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.type, len);
			r.type[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.room_num, len);

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.price, len);
		}

		i++;

	} while (!roomsfile.eof());

	roomsfile.clear();
	roomsfile.close();
	return false;

}

void rooms::display_all_rooms() {

	fstream roomsfile;
	roomsfile.open("Rooms file.txt", ios::in | ios::out | ios::binary);

	rooms r;
	roomsfile.seekg(0, ios::beg);

	short len;
	int i = 0;
	do {
		if (i) {
			cout << "Status : " << r.status << " | " << "Type: " << r.type << " | "
				<< "Room Num: " << r.room_num << " | " << "Price: " << r.price << endl;
			roomsfile.clear();
		}

		{
			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.status, len);
			r.status[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.type, len);
			r.type[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.room_num, len);

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.price, len);
		}

		i++;

	} while (!roomsfile.eof());

	roomsfile.clear();
	roomsfile.close();
}

void rooms::searche_in_room_by_status() {

	fstream roomsfile;
	roomsfile.open("Rooms file.txt", ios::in | ios::out | ios::binary);

	cout << "1 - empty\n";
	cout << "2 - bookd\n";
	int choice;
	cin >> choice;
	rooms r;
	roomsfile.seekg(0, ios::beg);

	short len;
	int i = 0;
	do {
		if (choice == 1) {
			if (i && !strcmp(r.status, "empty")) {
				cout << "Status : " << r.status << " | " << "Type: " << r.type << " | "
					<< "Room Num: " << r.room_num << " | " << "Price: " << r.price << endl;
				roomsfile.clear();
			}
		}

		else if (choice == 2) {
			if (i && !strcmp(r.status, "booke")) {
				cout << "Status : " << r.status << " | " << "Type: " << r.type << " | "
					<< "Room Num: " << r.room_num << " | " << "Price: " << r.price << endl;
				roomsfile.clear();
			}

		}

		{
			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.status, len);
			r.status[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.type, len);
			r.type[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.room_num, len);

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.price, len);
		}

		i++;

	} while (!roomsfile.eof());

	roomsfile.clear();
	roomsfile.close();
}

void rooms::searche_in_room_by_type() {

	fstream roomsfile;
	roomsfile.open("Rooms file.txt", ios::in | ios::out | ios::binary);

	cout << "1 - single\n";
	cout << "2 - double\n";
	int choice;
	cin >> choice;
	rooms r;
	roomsfile.seekg(0, ios::beg);

	short len;
	int i = 0;
	do {
		if (choice == 1) {
			if (i && !strcmp(r.type, "single")) {
				cout << "Status : " << r.status << " | " << "Type: " << r.type << " | "
					<< "Room Num: " << r.room_num << " | " << "Price: " << r.price << endl;
				roomsfile.clear();

			}
		}
		else if (choice == 2) {
			if (i && !strcmp(r.type, "double")) {
				cout << "Status : " << r.status << " | " << "Type: " << r.type << " | "
					<< "Room Num: " << r.room_num << " | " << "Price: " << r.price << endl;
				roomsfile.clear();

			}

		}
		{
			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.status, len);
			r.status[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read(r.type, len);
			r.type[len] = '\0';

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.room_num, len);

			roomsfile.read((char*)&len, sizeof(short));
			roomsfile.read((char*)&r.price, len);
		}

		i++;

	} while (!roomsfile.eof());

	roomsfile.clear();
	roomsfile.close();
}

void rooms::searche_in_rooms() {

	cout << "1 - status\n";
	cout << "2 - type\n";
	int choice;
	cin >> choice;
	switch (choice) {
	case 1:
		searche_in_room_by_status();
		break;
	case 2:
		searche_in_room_by_type();
		break;
	}
}