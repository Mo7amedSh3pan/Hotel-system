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

void Add_In_primaryFile(int id,int offset ) {

	fstream primaryfile;
	primaryfile.open("primary file.txt", ios::in | ios::out | ios::binary);

	primaryfile.seekp(0, ios::end);

	{
	short len;
	len = sizeof(id);
	primaryfile.write((char*)&len, sizeof(short));
	primaryfile.write((char*)&id, len);

	len = sizeof(offset);
	primaryfile.write((char*)&len, sizeof(short));
	primaryfile.write((char*)&offset, len); }

	primaryfile.clear();
	primaryfile.close();
}

void Delete_from_primaryfile(int idDlet) {
	cout << "$ $ $ $ $ $ $ $ $ $ $ $ Delete_from_primaryfile $ $ $ $ $ $ $ $ $ $ $ $\n";

	fstream primaryfile;
	primaryfile.open("primary file.txt", ios::in | ios::out | ios::binary);

	primaryfile.seekg(0, ios::beg);
	int id,offset;
	short len;
	int i = 0;
	int offsetrecord=0;
	do {
		if (i && id == idDlet) {
			id = -1;

			primaryfile.seekp(offsetrecord, ios::beg);

			{
				len = sizeof(id);
				primaryfile.write((char*)&len, sizeof(short));
				primaryfile.write((char*)&id, len);
			}
			break;
		}

		{
			offsetrecord = primaryfile.tellg();

			primaryfile.read((char*)&len, sizeof(short));
			primaryfile.read((char*)&id, len);

			primaryfile.read((char*)&len, sizeof(short));
			primaryfile.read((char*)&offset, len);

		}

		i++;
	} while (!primaryfile.eof());

	primaryfile.clear();
	primaryfile.close();
}

void Display_From_primaryfile( ) {

	fstream primaryfile;
	primaryfile.open("primary file.txt", ios::in | ios::out | ios::binary);

	primaryfile.seekg(0, ios::beg);
	int id, offset;
	short len;
	int i = 0;
	do {
		if (i && id!=-1) {
			cout << "Id: " << id << " | " << "offset: " << offset << endl;
		}

		{


			primaryfile.read((char*)&len, sizeof(short));
			primaryfile.read((char*)&id, len);

			primaryfile.read((char*)&len, sizeof(short));
			primaryfile.read((char*)&offset, len);
		}

		i++;
		
	} while (!primaryfile.eof());

	primaryfile.clear();
	primaryfile.close();
}

int searche_in_primaryfilr(int ids) { //return offset

	fstream primaryfile;
	primaryfile.open("primary file.txt", ios::in | ios::out | ios::binary);

	primaryfile.seekg(0, ios::beg);
	int id, offset;
	short len;
	int i = 0;
	do {
		if (i  && id==ids) {
			return offset;
		}

		{
			primaryfile.read((char*)&len, sizeof(short));
			primaryfile.read((char*)&id, len);

			primaryfile.read((char*)&len, sizeof(short));
			primaryfile.read((char*)&offset, len);
		}

		i++;

	} while (!primaryfile.eof());

	primaryfile.clear();
	primaryfile.close();
	return -1;
}

bool check_is_id_founded(int Id) {
	fstream primaryfile;
	primaryfile.open("primary file.txt", ios::in | ios::out | ios::binary);

	primaryfile.seekg(0, ios::beg);
	int id, offset;
	short len;
	int i = 0;
	do {
		if (i && id == Id) {

			primaryfile.clear();
			primaryfile.close();
			return true;
		}

		{
			primaryfile.read((char*)&len, sizeof(short));
			primaryfile.read((char*)&id, len);

			primaryfile.read((char*)&len, sizeof(short));
			primaryfile.read((char*)&offset, len);
		}

		i++;

	} while (!primaryfile.eof());

	primaryfile.clear();
	primaryfile.close();
	return false;
}