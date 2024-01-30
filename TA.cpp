#include <iostream>
#include "Person.h"
#include "Employee.h"
#include "Teacher.h"
#include "Student.h"
#include "TA.h"
#include "Course.h"
using namespace std;

TA::TA(): Student(), Teacher() {
	courseID = nullptr;
}

void TA::taCourse(char* _courseID) {
	int size = strlen(_courseID);
	courseID = new char[size + 1];
	for (int i = 0; i < size; i++) {
		courseID[i] = _courseID[i];
	}
	courseID[size] = '\0';
}

char* TA::getTACourse() {
	return courseID;
}

char* TA::getID() {
	return Student::getID();
}

void TA::deleteChar() {
	if (courseID != nullptr) {
		delete[]courseID;
	}
	courseID = nullptr;
}

TA::~TA() {
	if (courseID != nullptr) {
		delete[]courseID;
	}
	courseID = nullptr;
}