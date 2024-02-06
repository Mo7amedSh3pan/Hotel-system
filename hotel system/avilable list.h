#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<strstream>
#include "primary.h"
#include "secondry.h"
#include "avilable list.h"

struct Node {
	int offset;
	int size;
	Node* next;
};

class avail_linkedlist {
	Node* head;
	Node* rear;
public:
	avail_linkedlist()
	{
		head = NULL;
		rear = NULL;
	}

	void add_deletednode_to_list(int off, int s)
	{
		Node* newnode = new Node;

		newnode->offset = off;
		newnode->size = s;

		if (head == NULL && rear == NULL)
		{
			head = newnode;

			rear = newnode;
			newnode->next = NULL;
		}

		else
		{
			rear->next = newnode;
			newnode->next = NULL;
			rear = newnode;
		}
	}

	int search_for_valid_place(int size_record)//delete
	{
		Node* curr = head;
		Node* prv = NULL;


		while (curr != NULL)
		{

			if (curr->size == size_record)
			{
				if (prv == NULL)
				{
					head = curr->next;
					if (curr->next == NULL) {
						rear = NULL;
					}
				}
				else
				{
					prv->next = curr->next;
					if (curr->next == NULL) {
						rear = prv;
					}

				}
				int a = curr->offset;
				delete curr;

				return a;
			}
			prv = curr;
			curr = curr->next;
		}

		return -1;
	}

	bool is_empty()
	{
		return (head == NULL);
	}
};