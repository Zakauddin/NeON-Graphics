#include <iostream>
using namespace std;

#include "Person.h"

Person::Person() {
	name = nullptr;
	numOfPeople++;
}

char* Person::getName() {
	return name;
}

int Person::getNumOfPeople() {
	return numOfPeople;
}

void Person::setName(char* _name) {
	int size = strlen(_name);
	name = new char[size + 1];
	for (int i = 0; i < size; i++) {
		name[i] = _name[i];
	}
	name[size] = '\0';
}

void Person::print() {
	cout << "Name: " << name << endl;
}

Person::~Person() {
	if (name != nullptr) {
		delete[]name;
	}
	name = nullptr;
}