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
	void newAttendGraphic(RenderWindow& window, Font& font);
	void appendAttend();
	void printAttendance();
	void viewAttendGraphic(RenderWindow& window, Font& font);
	void newMarks();
	void newMarksGraphic(RenderWindow& window, Font& font, Event& event);
	void appendMarks();
	void printMarks();
	void viewMarksGraphic(RenderWindow& window, Font& font);
	void newGrades();
	void setGradesGraphic(RenderWindow& window, Font& font, Event& event);
	void printGrades();
	void printGradeGraphic(RenderWindow& window, Font& font);
	void addStudent(char* studentID);
	void removeStudent(char* studentID);
	~Course();
};