#pragma once

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
	void appendAttend();
	int* getAttend();
	int getNumOfAttend();
	void newMarks();
	void appendMarks();
	int* getMarks();
	int getNumOfMarks();
	void print();
	void newGrades();
	void setAutoGrade();
	char* getGrade();
	void withdraw();
	~Registration();
};