#pragma once

#include <SFML/Graphics.hpp>
#include "Person.h"
#include "Employee.h"
#include "Course.h"

class Teacher: virtual public Employee {
	char* ID;
	int numOfCourses;
	Course **coursesList;
	char** courseID;

public:
	Teacher();
	Teacher(char* id);
	virtual char* getID();
	char* getName();
	void print();
	void printCourses();
	int getNumOfCourse();
	char* getCourseID(int index);
	void addCourse(int index, Course* obj);
	void addNewCourse(Course* obj);
	void setTitle(char* _title);
	bool courseAlreadyAssigned(char* courseID);
	void passwordReset();
	void newPassword(char* tempPass);
	void viewAttend(char* courseID);
	void viewAttendGraphic(RenderWindow& window, Font& font, char* courseID);
	void newAttend(char* courseID);
	void newAttendGraphic(RenderWindow& window, Font& font, char* courseID);
	void appendAttend(char* courseID);
	void newMarks(char* courseID);
	void newMarksGraphic(RenderWindow& window, Font& font, Event& event, char* courseID);
	void appendMarks(char* courseID);
	void viewMarks(char* courseID);
	void viewMarksGraphic(RenderWindow& window, Font& font, char* courseID);
	void setGrades(char* courseID);
	void setGradesGraphic(RenderWindow& window, Font& font, Event& event, char* courseID);
	~Teacher();
};