#pragma once

#include "Registration.h"
#include "Student.h"

class TA;

class Course {
	char* section;
	char* name;
	int count;
	TA* ta;
	char* taID;
	int numOfStudents;
	Registration** studentList;

public:
	Course();
	Course(char* ID);
	char* getSection();
	char* getTaID();
	int getNumOfStudents();
	void addCurrentReg(Registration* obj);
	void appointTA(TA* obj);
	void print();
	void newAttend();
	void appendAttend();
	void printAttendance();
	void newMarks();
	void appendMarks();
	void printMarks();
	void newGrades();
	void printGrades();
	void addStudent(char* studentID);
	void removeStudent(char* studentID);
	~Course();
};