#pragma once
#include <iostream>
#include "Observer.h"

class Subject
{
public:
	Subject() :head(NULL) {}
	Subject(Observer* head) :head(head) {}

	void AddObserver(Observer* ob)
	{
		ob->next = head;
		head = ob;
	}

	void RemoveObserver(Observer* ob)
	{
		if (head == NULL)
			return;
		if (head == ob)
		{
			head = ob->next;
			ob->next = NULL;
			return;
		}
		
		Observer* temp = head;
		while (temp != NULL)
		{
			if (temp->next == ob)
			{
				temp->next = ob->next;
				ob->next = NULL;
				return;
			}
			temp = temp->next;
		}
	}

	void notify(int id)
	{
		if (head == NULL)
			return;
		Observer* current = head;

		while (current != NULL)
		{
			current->onNotify(id);
			current = current->next;
		}
	}

private:
	Observer* head;
};

class EveryDay : public Subject
{
public:
	EveryDay(Observer* ob) :Subject(ob) {}
};