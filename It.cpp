#include <iostream>
#include <fstream>
#include "Person.h"
#include "Employee.h"
#include "It.h"
using namespace std;

ItManager::ItManager() :Employee(), Person() {
	ID = nullptr;
	tempID = nullptr;
}

ItManager::ItManager(char* id): tempID(id) {
	int size = strlen(tempID);
	ID = new char[size + 1];
	for (int i = 0; i < size; i++) {
		ID[i] = tempID[i];
	}
	ID[size] = '\0';
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = tempID[i];
	}
	ifstream iFile;
	iFile.open(file);
	char buffer[50];
	iFile.getline(buffer, 50);
	iFile.getline(buffer, 50);
	Employee::setName(buffer);
	char temp[] = { "IT Manager" };
	Employee::setTitle(temp);
}

char* ItManager::getID() {
	return ID;
}

void ItManager::print() {
	cout << "ID: " << ID << endl;
	Employee::print();
}

ItManager::~ItManager() {
	if (ID == nullptr) {
		delete[]ID;
	}
	ID = nullptr;
}