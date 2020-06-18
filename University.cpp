#include <iostream>
#include <fstream>
#include "University.h"
#include "Department.h"
#include "Course.h"
#include "Registration.h"
#include "Teacher.h"
#include "It.h"
#include "Student.h"
using namespace std;

University::University() {
	ifstream uniFile("UniInfo.txt");
	char buffer[50];
	uniFile.getline(buffer, 50);
	int tempSize = strlen(buffer);
	name = new char[tempSize + 1];
	for (int i = 0; i < tempSize; i++) {
		name[i] = buffer[i];
	}
	name[tempSize] = '\0';
	uniFile.getline(buffer, 50);
	totalDep = atoi(buffer);
	depList = new Department * [totalDep];
	for (int i = 0; i < totalDep; i++) {
		uniFile.getline(buffer, 50);
		Department* temp = new Department(buffer);
		depList[i] = temp;
	}
	teacherCount = NULL;
	teachList = nullptr;
	itCount = NULL;
	itList = nullptr;
	studentCount = NULL;
	stList = nullptr;
}

char* University::getName() {
	return name;
}

void University::setName(char* _name) {
	if (name != nullptr) {
		delete[]name;
	}
	int size = strlen(_name);
	name = new char[size + 1];
	for (int i = 0; i < size; i++) {
		name[i] = _name[i];
	}
	name[size] = '\0';
}

int University::getNumOfDep() {
	return totalDep;
}

void University::setNumOfDep(int _num) {
	totalDep = _num;
}

void University::addTeacherArray(Teacher** point, int size) {
	teachList = point;
	teacherCount = size;
}

void University::addITArray(ItManager** point, int size) {
	itList = point;
	itCount = size;
}

void University::addStudentArray(Student** point, int size) {
	stList = point;
	studentCount = size;
}

void University::addTeacher(char* depID, int index, Teacher* obj) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->addTeacher(index, obj);
		}
		temp = nullptr;
	}
}

void University::addIT(char* depID, ItManager* obj) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->addIT(obj);
		}
		temp = nullptr;
	}
}

void University::addStudent(char* depID, int index, Student* obj) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->addStudent(index, obj);
		}
	}
}

char* University::getDepId(int index) {
	return depList[index]->getID();
}

void University::print() {
	cout << name << endl << endl;
	for (int i = 0; i < totalDep; i++) {
		depList[i]->print();
		cout << endl << endl;
	}
}

bool University::addCourse(char* depID, char* _section) {
	bool added = false;
	for (int i = 0; i < totalDep && added == false; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->addCourse(_section);
			added = true;
		}
		temp = nullptr;
	}
	return added;
}

bool University::hodChecker(Teacher* obj) {
	bool found = false;
	for (int i = 0; i < totalDep && found == false; i++) {
		found = depList[i]->hodChecker(obj);
	}
	return found;
}

char* University::depGetter(Teacher* obj) {
	for (int i = 0; i < totalDep; i++) {
		if (depList[i]->hodChecker(obj) == true) {
			return depList[i]->getID();
		}
	}
	return nullptr;
}


bool University::courseChecker(char* depID, char* courseID) {
	bool courseFound = false;
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			courseFound = depList[i]->courseChecker(courseID);
		}
		temp = nullptr;
	}
	return courseFound;
}

//bool University::courseAlreadyAssigned(char* courseID) {
//	bool found = false;
//	for (int i = 0; i < teacherCount && found == false; i++) {
//		found = teachList[i]->courseAlreadyAssigned(courseID);
//	}
//	return found;
//}

bool University::courseAlreadyRegistered(char* studentID, char* courseID) {
	bool found = false;
	for (int i = 0; i < studentCount && found == false; i++) {
		if (strcmp(stList[i]->getID(), studentID) == 0) {
			found = stList[i]->courseAlreadyRegistered(courseID);
		}
	}
	return found;
}

bool University::courseAlreadyRegistered1(char* studentID, char* courseID) {
	bool found = false;
	for (int i = 0; i < studentCount && found == false; i++) {
		if (strcmp(stList[i]->getID(), studentID) == 0) {
			found = stList[i]->courseAlreadyRegistered1(courseID);
		}
	}
	return found;
}

void University::registerNewCourse(char* studentID, char* courseID) {
	char depID[3];
	depID[0] = courseID[0];
	depID[1] = courseID[1];
	depID[2] = '\0';
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->registerNewCourse(studentID, courseID);
		}
		temp = nullptr;
	}
	for (int i = 0; i < studentCount; i++) {
		if (strcmp(stList[i]->getID(), studentID) == 0) {
			stList[i]->registerNewCourse(courseID);
		}
	}
}

void University::unregisterCourse(char* studentID, char* courseID) {
	char depID[3];
	depID[0] = courseID[0];
	depID[1] = courseID[1];
	depID[2] = '\0';
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->unregisterCourse(studentID, courseID);
		}
		temp = nullptr;
	}
	for (int i = 0; i < studentCount; i++) {
		if (strcmp(stList[i]->getID(), studentID) == 0) {
			stList[i]->unregisterCourse(courseID);
		}
	}
}

bool University::courseAlreadyAssigned(char* depID, char* courseID) {
	bool assigned = false;
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			assigned = depList[i]->courseAlreadyAssigned(courseID);
		}
	}
	return assigned;
}

bool University::teacherChecker(char* teachID) {
	bool teacherFound = false;
	for (int i = 0; i < teacherCount && teacherFound == false; i++) {
		if (strcmp(teachList[i]->getID(), teachID) == 0) {
			teacherFound = true;
		}
	}
	return teacherFound;
}

bool University::studentChecker(char* studentID) {
	bool found = false;
	for (int i = 0; i < studentCount && found == false; i++) {
		if (strcmp(stList[i]->getID(), studentID) == 0) {
			found = true;
		}
	}
	return found;
}

bool University::teacherDepChecker(char* depID, char* teachID) {
	bool TeacherFound = false;
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			TeacherFound = depList[i]->teacherChecker(teachID);
		}
		temp = nullptr;
	}
	return TeacherFound;
}

bool University::studentDepChecker(char* depID, char* studentID) {
	bool student = false;
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			student = depList[i]->studentChecker(studentID);
		}
		temp = nullptr;
	}
	return student;
}

//void University::assignCourse(char* teachID, char* courseID) {
//	char depID[3];
//	depID[0] = courseID[0];
//	depID[1] = courseID[1];
//	depID[2] = '\0';
//	for (int i = 0; i < totalDep; i++) {
//		char* temp = depList[i]->getID();
//		bool found = true;
//		for (int j = 0; j < 2; j++) {
//			if (depID[j] != temp[j]) {
//				found = false;
//			}
//		}
//		if (found == true) {
//			for (int j = 0; j < teacherCount; j++) {
//				if (strcmp(teachList[j]->getID(), teachID) == 0) {
//					depList[i]->assignCourse(teachList[j], courseID);
//				}
//			}
//			
//		}
//	}
//}

void University::assignCourse(char* depID, char* teachID, char* courseID) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->assignCourse(teachID, courseID);
		}
		temp = nullptr;
	}
}

char* University::itDepGetter(ItManager* obj) {
	for (int i = 0; i < totalDep; i++) {
		if (depList[i]->itChecker(obj) == true) {
			return depList[i]->getID();
		}
	}
	return nullptr;
}

bool University::depChecker(char* depID, char* userID) {
	bool exists = false;
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			if (userID[0] == 't') {
				exists = depList[i]->teacherChecker(userID);
			}
			else if (userID[0] == 's') {
				exists = depList[i]->studentChecker(userID);
			}
		}
		temp = nullptr;
	}
	return exists;
}

void University::newTeacher(char* depID, char* userID, char* fName, char* lName) {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = userID[i];
	}
	ofstream newFile(file);
	newFile << "pass" << endl;
	newFile << fName << " " << lName << endl;
	newFile << "0" << endl;
	teacherCount++;
	ofstream updateFile("TeacherInfo.txt");
	updateFile << teacherCount << endl;
	for (int i = 0; i < teacherCount - 1; i++) {
		updateFile << teachList[i]->getID() << endl;
	}
	updateFile << userID << endl;
	updateFile.close();

	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->newTeacher(userID);
		}
		temp = nullptr;
	}
}

void University::removeTeacher(char* depID, char* userID) {
	teacherCount--;
	ofstream updateFile("TeacherInfo.txt");
	updateFile << teacherCount << endl;
	for (int i = 0; i < teacherCount + 1; i++) {
		if (strcmp(teachList[i]->getID(), userID) != 0) {
			updateFile << teachList[i]->getID() << endl;
		}
	}
	updateFile.close();
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->removeTeacher(userID);
		}
		temp = nullptr;
	}
}

void University::newStudent(char* depID, char* userID, char* fName, char* lName) {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = userID[i];
	}
	ofstream newFile(file);
	newFile << "pass" << endl;
	newFile << fName << " " << lName << endl;
	newFile << "0" << endl;
	studentCount++;
	ofstream updateFile("StudentInfo.txt");
	updateFile << studentCount << endl;
	for (int i = 0; i < studentCount - 1; i++) {
		updateFile << stList[i]->getID() << endl;
	}
	updateFile << userID << endl;
	updateFile.close();

	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->newStudent(userID);
		}
		temp = nullptr;
	}
}

void University::removeStudent(char* depID, char* userID) {
	studentCount--;
	ofstream updateFile("StudentInfo.txt");
	updateFile << studentCount << endl;
	for (int i = 0; i < studentCount + 1; i++) {
		if (strcmp(stList[i]->getID(), userID) != 0) {
			updateFile << stList[i]->getID() << endl;
		}
	}
	updateFile.close();
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->removeStudent(userID);
		}
		temp = nullptr;
	}
}

void University::addRegToCourse(char* depID, char* courseID, Registration* obj) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->addRegToCourse(courseID, obj);
		}
		temp = nullptr;
	}
}

void University::addTeacherToDep(char* depID, char* teachID) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->addTeacherToDep(teachID);
		}
		temp = nullptr;
	}
}

void University::printCourses(char* depID) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->printCourses();
		}
		temp = nullptr;
	}
}

void University::printGrade(char* depID, char* courseID) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->printGrades(courseID);
		}
		temp = nullptr;
	}
}

int University::getStudentCount(char* depID, char* courseID) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			return depList[i]->getStudentCount(courseID);
		}
		temp = nullptr;
	}
	return NULL;
}

void University::newMarks(char* depID, char* courseID) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->newMarks(courseID);
		}
		temp = nullptr;
	}
}

void University::appendMarks(char* depID, char* courseID) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->appendMarks(courseID);
		}
		temp = nullptr;
	}
}

void University::viewMarks(char* depID, char* courseID) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->viewMarks(courseID);
		}
		temp = nullptr;
	}
}

void University::appointTA(char* depID, char* courseID, TA* obj) {
	for (int i = 0; i < totalDep; i++) {
		char* temp = depList[i]->getID();
		bool found = true;
		for (int i = 0; i < 2; i++) {
			if (depID[i] != temp[i]) {
				found = false;
			}
		}
		if (found == true) {
			depList[i]->appointTA(courseID, obj);
		}
		temp = nullptr;
	}
}

University::~University() {
	delete[]name;
	name = nullptr;
	for (int i = 0; i < totalDep; i++) {
		delete depList[i];
	}
	delete[]depList;
	depList = nullptr;
}