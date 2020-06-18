#include <iostream>
#include <fstream>
#include "Course.h"
#include "Registration.h"
#include "Student.h"
using namespace std;

Course::Course() {
	section = nullptr;
	name = nullptr;
	count = NULL;
	ta = nullptr;
	taID = nullptr;
	numOfStudents = NULL;
	studentList = nullptr;
}

Course::Course(char* ID) :ta(nullptr) {
	count = 0;
	int size = strlen(ID);
	section = new char[size + 1];
	for (int i = 0; i < size; i++) {
		section[i] = ID[i];
	}
	section[size] = '\0';
	
	char file[] = { "       .txt" };
	for (int i = 0; i < size; i++) {
		file[i] = ID[i];
	}
	ifstream cFile(file);
	char buffer[50];
	cFile.getline(buffer, 50);
	size = strlen(buffer);
	name = new char[size  + 1];
	for (int i = 0; i < size; i++) {
		name[i] = buffer[i];
	}
	name[size] = '\0';
	cFile.getline(buffer, 50);
	size = strlen(buffer);
	taID = new char[size + 1];
	for (int i = 0; i < size; i++) {
		taID[i] = buffer[i];
	}
	taID[size] = '\0';
	cFile.getline(buffer, 50);
	numOfStudents = atoi(buffer);
	studentList = new Registration * [numOfStudents];
}

char* Course::getSection() {
	return section;
}

char* Course::getTaID() {
	return taID;
}

int Course::getNumOfStudents() {
	return numOfStudents;
}

void Course::addCurrentReg(Registration* obj) {
	studentList[count] = obj;
	count++;
}

void Course::appointTA(TA* obj) {
	ta = obj;
}

void Course::print() {
	cout << name << endl;
	cout << "TA's Name: " << taID << endl;
	cout << "Number of Students: " << numOfStudents << endl;
	for (int i = 0; i < numOfStudents; i++) {
		cout << studentList[i]->getStudentID() << endl;
	}
}

void Course::newAttend() {
	for (int i = 0; i < numOfStudents; i++) {
		char* tempGrade = studentList[i]->getGrade();
		if (tempGrade[0] != 'W') {
			studentList[i]->newAttend();
		}
		tempGrade = nullptr;
	}
}

void Course::appendAttend() {
	char studentID[7];
	cout << "Please enter the student's ID: ";
	bool validStudentID = false;
	char* input;
	int studentIndex;
	while (validStudentID == false) {
		try {
			input = new char[50];
			cin >> input;
			int size = strlen(input);
			if ((size < 6) || (size > 6)) {
				throw size;
			}
			for (int i = 0; i < 6; i++) {
				studentID[i] = input[i];
			}
			studentID[6] = '\0';
			bool found = false;
			for (int i = 0; i < numOfStudents; i++) {
				if (strcmp(studentList[i]->getStudentID(), studentID) == 0) {
					found = true;
					studentIndex = i;
				}
			}
			if (found == false) {
				throw false;
			}
			delete[]input;
			validStudentID = true;
		}
		catch (int x) {
			cout << "The size of the user ID you entered is " << x << " ." << endl;
			cout << "Please enter the 6 character user ID: ";
		}
		catch (bool) {
			cout << "This student doesn't exist in this course." << endl;
			cout << "Please enter the ID of a student in this course: ";
		}
	}
	studentList[studentIndex]->appendAttend();
}

void Course::printAttendance() {
	if (numOfStudents == 0) {
		cout << "No students registered to this course yet!" << endl;
	}
	else {
		for (int i = 0; i < numOfStudents; i++) {
			cout << studentList[i]->getStudentID() << " : ";
			int* temp = studentList[i]->getAttend();
			for (int j = 0; j < studentList[i]->getNumOfAttend(); j++) {
				cout << "Day " << j + 1 << ": ";
				if (temp[j] == 0) {
					cout << "Absent" << endl;
				}
				else {
					cout << "Present" << endl;
				}
			}
			temp = nullptr;
		}
	}
}

void Course::newMarks() {
	for (int i = 0; i < numOfStudents; i++) {
		char* tempGrade = studentList[i]->getGrade();
		if (tempGrade[0] != 'W') {
			studentList[i]->newMarks();
		}
		tempGrade = nullptr;		
	}
}

void Course::appendMarks() {
	char studentID[7];
	cout << "Please enter the student's ID: ";
	bool validStudentID = false;
	char* input;
	int studentIndex;
	while (validStudentID == false) {
		try {
			input = new char[50];
			cin >> input;
			int size = strlen(input);
			if ((size < 6) || (size > 6)) {
				throw size;
			}
			for (int i = 0; i < 6; i++) {
				studentID[i] = input[i];
			}
			studentID[6] = '\0';
			bool found = false;
			for (int i = 0; i < numOfStudents; i++) {
				if (strcmp(studentList[i]->getStudentID(), studentID) == 0) {
					found = true;
					studentIndex = i;
				}
			}
			if (found == false) {
				throw false;
			}
			delete[]input;
			validStudentID = true;
		}
		catch (int x) {
			cout << "The size of the user ID you entered is " << x << " ." << endl;
			cout << "Please enter the 6 character user ID: ";
		}
		catch (bool) {
			cout << "This student doesn't exist in this course." << endl;
			cout << "Please enter the ID of a student in this course: ";
		}
	}
	studentList[studentIndex]->appendMarks();
}

void Course::printMarks() {
	if (numOfStudents == 0) {
		cout << "No students registered to this course yet!" << endl;
	}
	else {
		for (int i = 0; i < numOfStudents; i++) {
			cout << studentList[i]->getStudentID() << " : ";
			int* temp = studentList[i]->getMarks();
			for (int j = 0; j < studentList[i]->getNumOfMarks(); j++) {
				cout << "Evaluation #" << j + 1 << ": " << temp[j] << endl;
			}
			temp = nullptr;
		}
	}
}

void Course::newGrades() {
	for (int i = 0; i < numOfStudents; i++) {
		char* tempGrade = studentList[i]->getGrade();
		if (tempGrade[0] != 'W') {
			studentList[i]->newGrades();
		}
		tempGrade = nullptr;
	}
}

void Course::printGrades() {
	if (numOfStudents == 0) {
		cout << "No students registered to this course yet!" << endl;
	}
	else {
		for (int i = 0; i < numOfStudents; i++) {
			cout << studentList[i]->getStudentID() << " : " << studentList[i]->getGrade() << endl;
		}
	}
}

void Course::addStudent(char* studentID) {
	char file[] = { "       .txt" };
	for (int i = 0; i < 7; i++) {
		file[i] = section[i];
	}
	ofstream cFile(file);
	cFile << name << endl;
	cFile << endl;
	cFile << numOfStudents + 1 << endl;
	for (int i = 0; i < numOfStudents; i++) {
		cFile << studentList[i]->getStudentID() << endl;
	}
	cFile << studentID << endl;
	cFile.close();
}

void Course::removeStudent(char* studentID) {
	char file[] = { "       .txt" };
	for (int i = 0; i < 7; i++) {
		file[i] = section[i];
	}
	ofstream cFile(file);
	cFile << name << endl;
	cFile << endl;
	cFile << numOfStudents - 1 << endl;
	for (int i = 0; i < numOfStudents; i++) {
		if (strcmp(studentList[i]->getStudentID(), studentID) != 0) {
			cFile << studentList[i]->getStudentID() << endl;
		}
	}
	cFile.close();
}

Course::~Course() {
	if (section != nullptr) {
		delete[]section;
	}
	section = nullptr;
	if (name != nullptr) {
		delete[]name;
	}
	name = nullptr;
	if (taID != nullptr) {
		delete[]taID;
	}
	taID = nullptr;
	ta = nullptr;
	delete[]studentList;
	studentList = nullptr;
}