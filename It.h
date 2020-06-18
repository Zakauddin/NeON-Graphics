#pragma once

#include "Employee.h"

class ItManager: public Employee {
	char* ID;
	char* tempID;
public:
	ItManager();
	ItManager(char* id);
	char* getID();
	void print();
	~ItManager();
};