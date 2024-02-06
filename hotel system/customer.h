#pragma once
avail_linkedlist  list;
rooms r2;

class customer {
	char name[20];
	char address[20];
	int id;
	int room_num;
public:
	customer add_customer_to_object();

	void insert_at_end(customer& c);

	void insert_at_place(int off, customer& c);

	void display(customer& c);

	void read(int offset);

	void DeleteById(int Id);

	void insertInDataFile();

	void searche_by_id(int id);

	void searche_by_name(char* name);

	void searche();

	void update(int id);
};

customer customer::add_customer_to_object()// as pack
{
	customer c;
	cout << "enter name" << endl;
	cin >> c.name;

	{
		bool flag = 0;
		int i = 0;
		do {
			if (i) {
				cout << "this id is dublicated \nplease try again\n";
			}
			cout << "enter id " << endl;
			cin >> c.id;
			flag = check_is_id_founded(c.id);
			i++;
		} while (flag);
	}

	cout << "enter address" << endl;
	cin >> c.address;

	cout << "enter room number" << endl;
	cin >> c.room_num;

	while (!r2.check_if_room_is_booked(c.room_num)) {
		cout << "this room number invalid\ntry again\n";
		cout << "enter room number" << endl;
		cin >> c.room_num;
	}


	return c;
}

void customer:: insert_at_end(customer& c)
{
	cout << "$ $ $ $ $ $ $ $ $ $ $ insert_at_end $ $ $ $ $ $ $ $ $ $ $\n";

	fstream customerfile;
	customerfile.open("customer file.txt", ios::in | ios::out | ios::binary);

	customerfile.seekp(0, ios::end);

	Add_In_primaryFile(c.id, customerfile.tellg());
	Add_In_secondryFile(c.name, c.id);

	{
		short len = strlen(c.name);//7mohamed 41 11mohamed.com 410
		customerfile.write((char*)&len, sizeof(short));
		customerfile.write(c.name, strlen(c.name));

		len = sizeof(c.id);
		customerfile.write((char*)&len, sizeof(short));
		customerfile.write((char*)&c.id, sizeof(c.id));

		len = strlen(c.address);
		customerfile.write((char*)&len, sizeof(short));
		customerfile.write(c.address, strlen(c.address));

		len = sizeof(c.room_num);
		customerfile.write((char*)&len, sizeof(short));
		customerfile.write((char*)&c.room_num, sizeof(c.room_num));
	}

	customerfile.clear();
	customerfile.close();

}

void customer:: insert_at_place(int off, customer& c)
{
	cout << "$ $ $ $ $ $ $ $ $ $ $ insert_at_place $ $ $ $ $ $ $ $ $ $ $\n";

	fstream customerfile;
	customerfile.open("customer file.txt", ios::in | ios::out | ios::binary);

	customerfile.seekp(off, ios::beg);

	Add_In_primaryFile(c.id, customerfile.tellg());
	Add_In_secondryFile(c.name, c.id);

	{
		short len = strlen(c.name);
		customerfile.write((char*)&len, sizeof(short));
		customerfile.write(c.name, strlen(c.name));

		len = sizeof(c.id);
		customerfile.write((char*)&len, sizeof(short));
		customerfile.write((char*)&c.id, sizeof(c.id));

		len = strlen(c.address);
		customerfile.write((char*)&len, sizeof(short));
		customerfile.write(c.address, strlen(c.address));

		len = sizeof(c.room_num);
		customerfile.write((char*)&len, sizeof(short));
		customerfile.write((char*)&c.room_num, sizeof(c.room_num));
	}

	customerfile.clear();

	customerfile.close();

}

void customer:: display(customer& c) {
	cout << "##########################\n";
	cout << "name: " << c.name << endl;
	cout << "Id: " << c.id << endl;
	cout << "Address: " << c.address << endl;
	cout << "Room num: " << c.room_num << endl;
}

void customer:: read(int offset = -1) {
	fstream customerfile;
	customerfile.open("customer file.txt", ios::in | ios::out | ios::binary);

	customer c;
	bool flag=false;
	customerfile.clear();

	if (offset == -1) {
		customerfile.seekg(0, ios::beg);
	}
	else {
		customerfile.seekg(offset, ios::beg);
	}
	short len;
	int i = 0;
	do {
		if (i && c.name[0] != '*') {
			flag = true;
			display(c);
			if (offset != -1) {
				return;
			}
		}

		{
			customerfile.read((char*)&len, sizeof(short));
			customerfile.read(c.name, len);
			c.name[len] = '\0';

			customerfile.read((char*)&len, sizeof(short));
			customerfile.read((char*)&c.id, len);

			customerfile.read((char*)&len, sizeof(short));
			customerfile.read(c.address, len);
			c.address[len] = '\0';

			customerfile.read((char*)&len, sizeof(short));
			customerfile.read((char*)&c.room_num, len);
		}

		i++;
	} while (!customerfile.eof());

	customerfile.clear();
	if (!flag) {
		cout << "$ $ $ $ $ $ $ $ $ $ $ customer file is empty $ $ $ $ $ $ $ $ $ $ $\n";
	}
	customerfile.close();
}

void customer:: DeleteById(int Id) {

	cout << "$ $ $ $ $ $ $ $ $ $ $ Delete by Id function $ $ $ $ $ $ $ $ $ $ $\n";

	fstream customerfile;
	customerfile.open("customer file.txt", ios::in | ios::out | ios::binary);

	int off=0;
	off = searche_in_primaryfilr(Id);
	while (off == -1) {
		cout << "invalid id\nplease try again\n";
		cout << "enter id\n";
		cin >> Id;
		off = searche_in_primaryfilr(Id);
	}


	customer c;
	customerfile.clear();
	customerfile.seekg(0, ios::beg);
	short len;
	int offset;
	int i = 0;
	bool flag = false;
	do {
		if (i) {
			if (c.id == Id) {
				cout << "$ $ $ $ $ $ $ $ $ $ $ Id founded $ $ $ $ $ $ $ $ $ $ $\n";

				{
					Delete_from_primaryfile(Id);
					Delete_from_secondryfile(Id);
					r2.check_out(c.room_num);
				}

				{
					long long RecordSize = strlen(c.name) + strlen(c.address) + sizeof(c.id) + sizeof(c.room_num);
					list.add_deletednode_to_list(offset, RecordSize);
					cout << "$ $ $ $ $ $ $ $ $ $ $ $ deleted record was added to available list $ $ $ $ $ $ $ $ $ $ $ $\n";

					customerfile.seekp(offset, ios::beg);
				}

				{
					c.name[0] = '*';
					short len = strlen(c.name);
					customerfile.write((char*)&len, sizeof(short));
					customerfile.write(c.name, len);
				}
				break;
			}
		}

		offset = customerfile.tellg();

		{
			//7mohamed 41 11mohamed.com 410
			customerfile.read((char*)&len, sizeof(short));
			customerfile.read(c.name, len);
			c.name[len] = '\0';

			customerfile.read((char*)&len, sizeof(short));
			customerfile.read((char*)&c.id, len);

			customerfile.read((char*)&len, sizeof(short));
			customerfile.read(c.address, len);
			c.address[len] = '\0';

			customerfile.read((char*)&len, sizeof(short));
			customerfile.read((char*)&c.room_num, len);
		}

		i++;
	} while (!customerfile.eof());

	customerfile.clear();
	customerfile.close();
}

void customer:: insertInDataFile() {
	customer cus;
	cus = add_customer_to_object();

	if (list.is_empty())
	{
		cout << "$ $ $ $ $ $ $ $ $ $ $ list is empty $ $ $ $ $ $ $ $ $ $ $\n";
		insert_at_end(cus);
	}
	else
	{
		cout << "$ $ $ $ $ $ $ $ $ $ $ list is not empty $ $ $ $ $ $ $ $ $ $ $\n";

		int recordsize = strlen(cus.name)
						+ strlen(cus.address)
						+ sizeof(cus.id)
						+ sizeof(cus.room_num);

		int off = list.search_for_valid_place(recordsize);
		if (off == -1)
		{
			insert_at_end(cus);
		}
		else
		{
			insert_at_place(off,cus);
		}
	}

}

void customer:: searche_by_id( int id) {


	int offset = searche_in_primaryfilr(id);
	while (offset == -1) {
		cout << "this id not found\nplease try again\n";
		cout << "enter Id that you want to searche\n"; 
		cin >> id;
		offset = searche_in_primaryfilr(id);
	}

	read(offset);
}

void customer:: searche_by_name(char* name) {

	int id = searche_in_secondryfilr(name);

	if (id == -1) {
		cout << "this name not foud\n";
		return;
	}
	searche_by_id( id);
}

void customer:: searche() {
	cout << "1 - Id\n";
	cout << "2 - Name\n";
	int choice;
	cin >> choice;

	while (choice != 1 && choice != 2 ) {
		cout << "Invalid input\nplease try again\n";
		cin >> choice;
	}

	if (choice == 1) {
		int id;
		cout << "enter Id that you want to searche\n"; cin >> id;
		searche_by_id(id);
	}
	else if (choice == 2) {
		char name[11];
		cout << "enter name that you want to searche\n"; cin >> name;

		searche_by_name(name);
	}
}

void customer:: update(int id) {

	searche_by_id(id);

	DeleteById(id);

	insertInDataFile();

}