#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Registration {
	char* studentID;
	char* courseID;
	char* courseName;
	int numOfAttend;
	int* attendance ;
	int numOfMarks;
	int* marks;
	char* grade;

public:
	Registration();
	Registration(char* _student, char* _course);
	char* getCourseID();
	char* getStudentID();
	void newAttend();
	void newAttendGraphic(RenderWindow& window, Font& font);
	void appendAttend();
	int* getAttend();
	int getNumOfAttend();
	void newMarks();
	void newMarksGraphic(RenderWindow& window, Font& font, Event& event);
	void appendMarks();
	int* getMarks();
	int getNumOfMarks();
	void print();
	void newGrades();
	void setGradesGraphic(RenderWindow& window, Font& font, Event& event);
	void setAutoGrade();
	char* getGrade();
	void withdraw();
	~Registration();
};