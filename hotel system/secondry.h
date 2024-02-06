#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<strstream>
#include "primary.h"
#include "secondry.h"
#include "avilable list.h"

using namespace std;

avail_linkedlist secondrylist;

void Add_In_secondryFile(char* name, int id) {

	fstream secondryfile;
	secondryfile.open("secondry file.txt", ios::in | ios::out | ios::binary);

	if (secondrylist.is_empty()) {
		cout << "list empty\n";
		secondryfile.seekp(0, ios::end);

	}

	else {
		cout << "list not empty\n";
		int sizerecord = sizeof(id) + strlen(name);
		int offset = secondrylist.search_for_valid_place(sizerecord);

		if (offset == -1) {
			cout << "offset = -1\n";
			secondryfile.seekp(0, ios::end);
		}

		else
			secondryfile.seekp(offset, ios::beg);
	}

	{
		short len;
		len = sizeof(id);
		secondryfile.write((char*)&len, sizeof(short));
	    secondryfile.write((char*)&id, len);

		len = strlen(name);
		secondryfile.write((char*)&len, sizeof(short));
		secondryfile.write(name, strlen(name));
	}

	secondryfile.clear();
	secondryfile.close();
}

void Delete_from_secondryfile(int Id) {
	cout << "$ $ $ $ $ $ $ $ $ $ $ $ Delete_from_secondryfile $ $ $ $ $ $ $ $ $ $ $ $\n";

	fstream secondryfile;
	secondryfile.open("secondry file.txt", ios::in | ios::out | ios::binary);

	secondryfile.seekg(0, ios::beg);
	char name[11];
	int id;
	short len;
	int i = 0;
	int offsetrecord = 0;
	do {
		if (i && id == Id) {
			id = -1;
			int sizerecord = strlen(name)+ sizeof(id);
			secondrylist.add_deletednode_to_list(offsetrecord,sizerecord);

			secondryfile.seekp(offsetrecord, ios::beg);
			{
				len = sizeof(id);
				secondryfile.write((char*)&len, sizeof(short));
				secondryfile.write((char*)&id, sizeof(id));
			}
			break;
		}

		{
			offsetrecord = secondryfile.tellg();
			secondryfile.read((char*)&len, sizeof(short));
			secondryfile.read((char*)&id, len);

			secondryfile.read((char*)&len, sizeof(short));
			secondryfile.read(name, len);
			name[len] = '\n';
		}
		i++;
	} while (!secondryfile.eof());

	secondryfile.clear();
	secondryfile.close();
}

void Display_From_secondryfile() {

	fstream secondryfile;
	secondryfile.open("secondry file.txt", ios::in | ios::out | ios::binary);

	cout << "---------------Display_From_secondryfile-----------\n";

	secondryfile.seekg(0, ios::beg);

	char name[11];
	int id;
	short len;
	int i = 0;
	do {
		if (i && id!=-1) {
			cout << "name: " << name << " | "  << "Id: " << id << endl;
			secondryfile.clear();

		}

		{
			secondryfile.read((char*)&len, sizeof(short));
			secondryfile.read((char*)&id, len);

			secondryfile.read((char*)&len, sizeof(short));
			secondryfile.read(name, len);
			name[len] = '\0';
		}

		i++;

	} while (!secondryfile.eof());

	secondryfile.clear();
	secondryfile.close();
}

int searche_in_secondryfilr(char *names) {

	fstream secondryfile;
	secondryfile.open("secondry file.txt", ios::in | ios::out | ios::binary);

	secondryfile.seekg(0, ios::beg);
	char name[11];
	int id;
	short len;
	int i = 0;
	bool flag = 0;
	do {
		if (i && (!strcmp(name, names))) {
			cout << "name: " << name << " -> " << "Id: " << id << endl;
			flag = true;
		}

		{
			secondryfile.read((char*)&len, sizeof(short));
			secondryfile.read((char*)&id, len);

			secondryfile.read((char*)&len, sizeof(short));
			secondryfile.read(name, len);
			name[len] = '\0';
		}

		i++;

	} while (!secondryfile.eof());

	secondryfile.clear();
	secondryfile.close();
	if (flag) {
		int Id;
		cout << "enter id that you want\n";
		cin >> Id;
		return Id;
	}
	return -1;

}