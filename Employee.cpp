#include <iostream>
#include "Person.h"
#include "Employee.h"
using namespace std;

Employee::Employee(): Person() {
	title = nullptr;
}

char* Employee::getName() {
	return Person::getName();
}

void Employee::setName(char* _name) {
	Person::setName(_name);
}

void Employee::setTitle(char* _title) {
	int size = strlen(_title); 
	title = new char[size + 1];
	for (int i = 0; i < size; i++) {
		title[i] = _title[i];
	}
	title[size] = '\0';
}

char* Employee::getTitle() {
	return title;
}

void Employee::print() {
	cout << "Title: " << title << endl;
	cout << "Name: " << Person::getName() << endl;
}

Employee::~Employee() {
	if (title != nullptr) {
		delete[]title;
	}
	title = nullptr;
}