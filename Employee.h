#pragma once

#include "Person.h"

class Employee : virtual public Person {
	char* title;
public:
	Employee();
	char* getName();
	void setName(char* _name);
	void setTitle(char* _title);
	char* getTitle();
	virtual void print();
	virtual ~Employee();
};