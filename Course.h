#pragma once

#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Registration.h"
#include "Student.h"
using namespace sf;

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
	void printGradeGraphic(RenderWindow& window, Font& font);
	void addStudent(char* studentID);
	void removeStudent(char* studentID);
	~Course();
};