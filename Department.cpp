#include <iostream>
#include <fstream>
#include "Department.h"
#include "Course.h"
#include "Registration.h"
#include "Teacher.h"
#include "It.h"
#include "Student.h"
#include "TA.h"
using namespace std;

void objPrint(Person* obj) {
	obj->print();
}

Department::Department() {
	id = new char[3];
	for (int i = 0; i < 3; i++) {
		id[i] = NULL;
	}
	id[2] = '\0';
	tempID = nullptr;
	name = nullptr;
	numOfCourses = NULL;
	courseList = nullptr;
	numOfTeachers = NULL;
	teacherList = nullptr;
	itMan = nullptr;
	numOfStudents = NULL;
	studentList = nullptr;
}

Department::Department(char* departmentID): tempID(departmentID) {
	id = new char[3];
	for (int i = 0; i < 2; i++) {
		id[i] = tempID[i];
	}
	id[2] = '\0';
	tempID = nullptr;
	ifstream dFile;
	char file[] = "  .txt";
	for (int i = 0; i < 2; i++) {
		file[i] = id[i];
	}
	dFile.open(file);
	char buffer[50];
	dFile.getline(buffer, 50);
	int size = strlen(buffer);
	name = new char[size + 1];
	for (int i = 0; i < size; i++) {
		name[i] = buffer[i];
	}
	name[size] = '\0';
	dFile.getline(buffer, 50);
	numOfCourses = atoi(buffer);
	courseList = new Course * [numOfCourses];
	for (int i = 0; i < numOfCourses; i++) {
		dFile.getline(buffer, 50);
		Course* tempC = new Course(buffer);
		courseList[i] = tempC;
		/*char file1[] = { "       .txt" };
		int size = strlen(buffer);
		for (int i = 0; i < size; i++) {
			file1[i] = buffer[i];
		}
		ifstream cFile(file1);
		cFile.getline(buffer, 50);
		if (size != 0) {
			cFile.getline(buffer, 50);
			for (int j = 0; j < numOfStudents; j++) {
				if (strcmp(studentList[j]->getID(), buffer) == 0) {
					TA* temp = (TA*)courseList[i];
					courseList[i]->appointTA(temp);
					temp = nullptr;
				}
			}
		}
		cFile.close();*/
	}
	dFile.getline(buffer, 50);
	numOfTeachers = atoi(buffer);
	teacherList = new Teacher * [numOfTeachers];
	for (int i = 0; i < numOfTeachers; i++) {
		dFile.getline(buffer, 50);
	}
	dFile.getline(buffer, 50);
	itMan = nullptr;
	dFile.getline(buffer, 50);
	numOfStudents = atoi(buffer);
	studentList = new Student * [numOfStudents];
}

char* Department::getID() {
	return id;
}

void Department::addTeacher(int index, Teacher* obj) {
	teacherList[index] = obj;
	for (int i = 0; i < obj->getNumOfCourse(); i++) {
		char* temp = obj->getCourseID(i);
		for (int j = 0; j < numOfCourses; j++) {
			char* temp1 = courseList[j]->getSection();
			bool found = true;
			int size = strlen(temp);
			for (int k = 0; k < size; k++) {
				if (temp[k] != temp1[k]) {
					found = false;
				}
			}
			if (found == true) {
				obj->addCourse(i, courseList[j]);
			}
			temp1 = nullptr;
		}
		temp = nullptr;
	}
}

bool Department::hodChecker(Teacher* obj) {
	if (obj == teacherList[0]) {
		return true;
	}
	return false;
}

void Department::addIT(ItManager* obj) {
	itMan = obj;
}

void Department::addStudent(int index, Student* obj) {
	studentList[index] = obj;
}

void Department::print() {
	cout << "Department ID: " << id << endl;
	cout << "Department Name: " << name << endl;
	cout << "Number of courses: " << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		cout << "Course #" << i + 1 << ": ";
		courseList[i]->print();
		cout << endl;
	}
	cout << endl;
	cout << "Number of Teacher: " << numOfTeachers << endl;
	for (int i = 0; i < numOfTeachers; i++) {
		cout << "Teacher #" << i + 1 << ": ";
		objPrint(teacherList[i]);
		cout << endl;
	}
	cout << endl;
	cout << "IT Manager: ";
	objPrint(itMan);
	cout << endl;
	cout << "Number of Students: " << numOfStudents << endl;
	for (int i = 0; i < numOfStudents; i++) {
		cout << "Student #" << i + 1 << ": ";
		objPrint(studentList[i]);
		cout << endl;
	}
}

bool Department::addCourse(char* _section) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), _section) != 0) {
			return false;
		}
	}
	numOfCourses++;

	ofstream cFile;
	char newFile[] = { "       .txt" };
	int size = strlen(_section);
	for (int i = 0; i < size; i++) {
		newFile[i] = _section[i];
	}
	cFile.open(newFile);
	cFile << endl;
	cFile << "0" << endl;
	cFile.close();

	Course** temp = new Course * [numOfCourses];
	for (int i = 0; i < numOfCourses - 1; i++) {
		temp[i] = courseList[i];
	}
	Course* temp1 = new Course(_section);
	temp[numOfCourses - 1] = temp1;
	courseList = temp;
	delete[]temp;
	temp = nullptr;

	char file[] = { "  .txt" };
	for (int i = 0; i < 2; i++) {
		file[i] = id[i];
	}
	ofstream dFile;
	dFile.open(file);
	dFile << name << endl;
	dFile << numOfCourses << endl;
	for (int i = 0; i < numOfCourses-1; i++) {
		dFile << courseList[i]->getSection() << endl;
	}
	dFile << _section << endl;
	dFile << numOfTeachers << endl;
	for (int i = 0; i < numOfTeachers; i++) {
		dFile << teacherList[i]->getID() << endl;
	}
	dFile << itMan->getID() << endl;
	dFile << numOfStudents << endl;
	for (int i = 0; i < numOfStudents; i++) {
		dFile << studentList[i]->getID() << endl;
	}
	return true;
}

//void Department::assignCourse(Teacher* obj, char* courseID) {
//	for (int j = 0; j < numOfCourses; j++) {
//		if (strcmp(courseList[j]->getSection(), courseID) == 0) {
//			obj->addNewCourse(courseList[j]);
//		}
//	}
//}

void Department::assignCourse(char* teachID, char* courseID) {
	for (int i = 0; i < numOfTeachers; i++) {
		if (strcmp(teacherList[i]->getID(), teachID) == 0) {
			for (int j = 0; j < numOfCourses; j++) {
				if (strcmp(courseList[j]->getSection(), courseID) == 0) {
					teacherList[i]->addNewCourse(courseList[j]);
				}
			}
		}
	}
}

bool Department::courseChecker(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseID, courseList[i]->getSection()) == 0) {
			return true;
		}
	}
	return false;
}

bool Department::courseAlreadyAssigned(char* courseID) {
	bool assigned = false;
	for (int i = 0; i < numOfTeachers && assigned == false; i++) {
		assigned = teacherList[i]->courseAlreadyAssigned(courseID);
	}
	return assigned;
}

bool Department::teacherChecker(char* teachID) {
	bool teacherFound = false;
	for (int i = 1; i < numOfTeachers && teacherFound == false; i++) {
		if (strcmp(teacherList[i]->getID(), teachID) == 0) {
			teacherFound = true;
		}
	}
	return teacherFound;
}

bool Department::studentChecker(char* userID) {
	bool studentFound = false;
	for (int i = 0; i < numOfStudents && studentFound == false; i++) {
		if (strcmp(studentList[i]->getID(), userID) == 0) {
			studentFound = true;
		}
	}
	return studentFound;
}

bool Department::itChecker(ItManager* obj) {
	if (obj == itMan) {
		return true;
	}
	return false;
}

void Department::newTeacher(char* userID) {
	ofstream dFile;
	char file[] = "  .txt";
	for (int i = 0; i < 2; i++) {
		file[i] = id[i];
	}
	dFile.open(file);
	dFile << name << endl;
	dFile << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		dFile << courseList[i]->getSection() << endl;
	}
	dFile << numOfTeachers + 1 << endl;
	for (int i = 0; i < numOfTeachers; i++) {
		dFile << teacherList[i]->getID() << endl;
	}
	dFile << userID << endl;
	dFile << itMan->getID() << endl;
	dFile << numOfStudents << endl;
	for (int i = 0; i < numOfStudents; i++) {
		dFile << studentList[i]->getID() << endl;
	}
	dFile.close();
}

void Department::removeTeacher(char* userID) {
	ofstream dFile;
	char file[] = "  .txt";
	for (int i = 0; i < 2; i++) {
		file[i] = id[i];
	}
	dFile.open(file);
	dFile << name << endl;
	dFile << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		dFile << courseList[i]->getSection() << endl;
	}
	dFile << numOfTeachers - 1 << endl;
	for (int i = 0; i < numOfTeachers; i++) {
		if (strcmp(teacherList[i]->getID(), userID) != 0) {
			dFile << teacherList[i]->getID() << endl;
		}
	}
	dFile << itMan->getID() << endl;
	dFile << numOfStudents << endl;
	for (int i = 0; i < numOfStudents; i++) {
		dFile << studentList[i]->getID() << endl;
	}
	dFile.close();
}

void Department::newStudent(char* userID) {
	ofstream dFile;
	char file[] = "  .txt";
	for (int i = 0; i < 2; i++) {
		file[i] = id[i];
	}
	dFile.open(file);
	dFile << name << endl;
	dFile << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		dFile << courseList[i]->getSection() << endl;
	}
	dFile << numOfTeachers << endl;
	for (int i = 0; i < numOfTeachers; i++) {
		dFile << teacherList[i]->getID() << endl;
	}
	dFile << itMan->getID() << endl;
	dFile << numOfStudents + 1<< endl;
	for (int i = 0; i < numOfStudents; i++) {
		dFile << studentList[i]->getID() << endl;
	}
	dFile << userID << endl;
	dFile.close();
}

void Department::removeStudent(char* userID) {
	ofstream dFile;
	char file[] = "  .txt";
	for (int i = 0; i < 2; i++) {
		file[i] = id[i];
	}
	dFile.open(file);
	dFile << name << endl;
	dFile << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		dFile << courseList[i]->getSection() << endl;
	}
	dFile << numOfTeachers << endl;
	for (int i = 0; i < numOfTeachers; i++) {
		dFile << teacherList[i]->getID() << endl;
	}
	dFile << itMan->getID() << endl;
	numOfStudents--;
	dFile << numOfStudents << endl;
	for (int i = 0; i < numOfStudents + 1; i++) {
		if (strcmp(studentList[i]->getID(), userID) != 0) {
			dFile << studentList[i]->getID() << endl;
		}
	}
	dFile.close();
}

void Department::addRegToCourse(char* courseID, Registration* obj) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			courseList[i]->addCurrentReg(obj);
		}
	}
}

void Department::registerNewCourse(char* studentID, char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			if (courseList[i]->getNumOfStudents() < 50) {
				courseList[i]->addStudent(studentID);
			}
			else {
				cout << "Maximum student Capacity already reached!" << endl;
			}
		}
	}
}

void Department::unregisterCourse(char* studentID, char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			courseList[i]->removeStudent(studentID);
		}
	}
}

void Department::addTeacherToDep(char* teachID) {
	char file[] = "  .txt";
	for (int i = 0; i < 2; i++) {
		file[i] = id[i];
	}
	ofstream dFile(file);
	dFile << name << endl;
	dFile << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		dFile << courseList[i]->getSection() << endl;
	}
	dFile << numOfTeachers + 1 << endl;
	for (int i = 0; i < numOfTeachers; i++) {
		dFile << teacherList[i]->getID() << endl;
	}
	dFile << teachID << endl;
	dFile << itMan->getID() << endl;
	dFile << numOfStudents << endl;
	for (int i = 0; i < numOfStudents; i++) {
		dFile << studentList[i]->getID() << endl;
	}
	dFile.close();
}

void Department::printCourses() {
	for (int i = 0; i < numOfCourses; i++) {
		cout << courseList[i]->getSection() << endl;
	}
}

void Department::printGrades(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			courseList[i]->printGrades();
		}
	}
}

int Department::getStudentCount(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			return courseList[i]->getNumOfStudents();
		}
	}
	return NULL;
}

void Department::newMarks(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			courseList[i]->newMarks();
		}
	}
}

void Department::appendMarks(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			courseList[i]->appendMarks();
		}
	}
}

void Department::viewMarks(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			courseList[i]->printMarks();
		}
	}
}

void Department::appointTA(char* courseID, TA* obj) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courseList[i]->getSection(), courseID) == 0) {
			courseList[i]->appointTA(obj);
		}
	}
}

Department::~Department() {
	if (id != nullptr) {
		delete[]id;
	}
	id = nullptr;
	if (tempID != nullptr) {
		delete[]tempID;
	}
	tempID = nullptr;
	if (name != nullptr) {
		delete[]name;
	}
	name = nullptr;
	for (int i = 0; i < numOfCourses; i++) {
		delete courseList[i];
	}
	courseList = nullptr;
	teacherList = nullptr;
	itMan = nullptr;
	studentList = nullptr;
}