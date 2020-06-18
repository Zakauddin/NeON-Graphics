#include <iostream>
#include <fstream>
#include "Person.h"
#include "Employee.h"
#include "Teacher.h"
#include "Course.h"
using namespace std;

Teacher::Teacher() : Employee(), Person() {
	ID = nullptr;
	numOfCourses = NULL;
	coursesList = nullptr;
	courseID = nullptr;
}

Teacher::Teacher(char* id) {
	int size = strlen(id);
	ID = new char[size + 1];
	for (int i = 0; i < size; i++) {
		ID[i] = id[i];
	}
	ID[size] = '\0';
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = id[i];
	}
	ifstream tFile;
	tFile.open(file);
	char buffer[50];
	tFile.getline(buffer, 50);//password line
	tFile.getline(buffer, 50);
	Employee::setName(buffer);
	tFile.getline(buffer, 50);
	numOfCourses = atoi(buffer);
	if (numOfCourses > 0) {
		coursesList = new Course * [numOfCourses];
		courseID = new char* [numOfCourses];
		for (int i = 0; i < numOfCourses; i++) {
			tFile.getline(buffer, 50);
			int size = strlen(buffer);
			char* temp = new char[size + 1];
			for (int i = 0; i < size; i++) {
				temp[i] = buffer[i];
			}
			temp[size] = '\0';
			courseID[i] = temp;
		}
	}
	else {
		coursesList = nullptr;
		courseID = nullptr;
	}
}

char* Teacher::getID() {
	return ID;
}

char* Teacher::getName() {
	return Employee::getName();
}

void Teacher::print() {
	cout << "ID: " << ID << endl;
	cout << "Name: " << Employee::getName() << endl;
	cout << "Title: " << Employee::getTitle() << endl;
}

void Teacher::printCourses() {
	for (int i = 0; i < numOfCourses; i++) {
		cout << coursesList[i]->getSection() << endl;
	}
}

int Teacher::getNumOfCourse() {
	return numOfCourses;
}

char* Teacher::getCourseID(int index) {
	return courseID[index];
}

void Teacher::addCourse(int index, Course* obj) {
	coursesList[index] = obj;
}

void Teacher::setTitle(char* _title) {
	Employee::setTitle(_title);
}

void Teacher::addNewCourse(Course* obj) {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = ID[i];
	}
	ifstream tFile;
	tFile.open(file);
	char buffer[50];
	tFile.getline(buffer, 50);
	int size = strlen(buffer);
	char* tempPass = new char[size + 1];
	for (int i = 0; i < size; i++) {
		tempPass[i] = buffer[i];
	}
	tempPass[size] = '\0';
	tFile.getline(buffer, 50);
	size = strlen(buffer);
	char* tempName = new char[size + 1];
	for (int i = 0; i < size; i++) {
		tempName[i] = buffer[i];
	}
	tempName[size] = '\0';
	tFile.getline(buffer, 50);
	int tempNum = atoi(buffer);
	tempNum++;
	char** tempCourses = new char* [tempNum];
	for (int i = 0; i < tempNum - 1; i++) {
		tFile.getline(buffer, 50);
		size = strlen(buffer);
		tempCourses[i] = new char[size + 1];
		for (int j = 0; j < size; j++) {
			tempCourses[i][j] = buffer[j];
		}
		tempCourses[i][size] = '\0';
	}
	char* tempSection = obj->getSection();
	size = strlen(tempSection);
	tempCourses[tempNum - 1] = new char[size + 1];
	for (int i = 0; i < size; i++) {
		tempCourses[tempNum - 1][i] = tempSection[i];
	}
	tempCourses[tempNum - 1][size] = '\0';
	tFile.close();
	ofstream t1File(file);
	t1File << tempPass << endl;
	t1File << tempName << endl;
	t1File << tempNum << endl;
	for (int i = 0; i < tempNum; i++) {
		t1File << tempCourses[i] << endl;
	}
	t1File.close();
}

bool Teacher::courseAlreadyAssigned(char* _courseID) {
	bool assigned = false;
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(_courseID, courseID[i]) == 0) {
			assigned = true;
		}
	}
	return assigned;
}

void Teacher::passwordReset() {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = ID[i];
	}
	ifstream tFile;
	tFile.open(file);
	char buffer[50];
	tFile.getline(buffer, 50);
	tFile.getline(buffer, 50);
	int size = strlen(buffer);
	char* tempName = new char[size + 1];
	for (int i = 0; i < size; i++) {
		tempName[i] = buffer[i];
	}
	tempName[size] = '\0';
	tFile.getline(buffer, 50);
	int tempNum = atoi(buffer);
	char** tempCourses = new char* [tempNum];
	for (int i = 0; i < tempNum; i++) {
		tFile.getline(buffer, 50);
		size = strlen(buffer);
		tempCourses[i] = new char[size + 1];
		for (int j = 0; j < size; j++) {
			tempCourses[i][j] = buffer[j];
		}
		tempCourses[i][size] = '\0';
	}
	tFile.close();
	ofstream t1File(file);
	t1File << "pass" << endl;
	t1File << tempName << endl;
	t1File << tempNum << endl;
	for (int i = 0; i < tempNum; i++) {
		t1File << tempCourses[i] << endl;
	}
	t1File.close();
}

void Teacher::newPassword(char* tempPass) {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = ID[i];
	}
	ifstream tFile;
	tFile.open(file);
	char buffer[50];
	tFile.getline(buffer, 50);
	tFile.getline(buffer, 50);
	int size = strlen(buffer);
	char* tempName = new char[size + 1];
	for (int i = 0; i < size; i++) {
		tempName[i] = buffer[i];
	}
	tempName[size] = '\0';
	tFile.getline(buffer, 50);
	int tempNum = atoi(buffer);
	char** tempCourses = new char* [tempNum];
	for (int i = 0; i < tempNum; i++) {
		tFile.getline(buffer, 50);
		size = strlen(buffer);
		tempCourses[i] = new char[size + 1];
		for (int j = 0; j < size; j++) {
			tempCourses[i][j] = buffer[j];
		}
		tempCourses[i][size] = '\0';
	}
	tFile.close();
	ofstream t1File(file);
	t1File << tempPass << endl;
	t1File << tempName << endl;
	t1File << tempNum << endl;
	for (int i = 0; i < tempNum; i++) {
		t1File << tempCourses[i] << endl;
	}
	t1File.close();
}

void Teacher::viewAttend(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(coursesList[i]->getSection(), courseID) == 0) {
			coursesList[i]->printAttendance();
		}
	}
}

void Teacher::newAttend(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(coursesList[i]->getSection(), courseID) == 0) {
			coursesList[i]->newAttend();
		}
	}
}

void Teacher::appendAttend(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(coursesList[i]->getSection(), courseID) == 0) {
			coursesList[i]->appendAttend();
		}
	}
}

void Teacher::newMarks(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(coursesList[i]->getSection(), courseID) == 0) {
			coursesList[i]->newMarks();
		}
	}
}

void Teacher::appendMarks(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(coursesList[i]->getSection(), courseID) == 0) {
			coursesList[i]->appendMarks();
		}
	}
}

void Teacher::viewMarks(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(coursesList[i]->getSection(), courseID) == 0) {
			coursesList[i]->printMarks();
		}
	}
}

void Teacher::setGrades(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(coursesList[i]->getSection(), courseID) == 0) {
			coursesList[i]->newGrades();
		}
	}
}

Teacher::~Teacher() {
	if (ID != nullptr) {
		delete[]ID;
	}
	ID = nullptr;
	if (coursesList != nullptr) {
		delete[]coursesList;
	}
	coursesList = nullptr;
	if (courseID != nullptr) {
		for (int i = 0; i < numOfCourses; i++) {
			delete[]courseID[i];
		}
		delete[]courseID;
	}
	courseID = nullptr;
}