#pragma once

#include "Course.h"
#include "Registration.h"
#include "Teacher.h"
#include "It.h"
#include "Student.h"
#include "TA.h"

class Department {
	char* id;
	char* tempID;
	char* name;
	int numOfCourses;
	Course** courseList;
	int numOfTeachers;
	Teacher** teacherList;
	ItManager* itMan;
	int numOfStudents;
	Student** studentList;

public:
	Department();
	Department(char* departmentID);
	char* getID();
	void addTeacher(int index, Teacher* obj);
	bool hodChecker(Teacher* obj);
	void addIT(ItManager* obj);
	void addStudent(int index, Student* obj);
	void print();
	bool addCourse(char* _section);
	//void assignCourse(Teacher* obj, char* courseID);
	void assignCourse(char* teachID, char* courseID);
	bool courseChecker(char* courseID);
	bool courseAlreadyAssigned(char* courseID);
	bool teacherChecker(char* teachID);
	bool studentChecker(char* userID);
	bool itChecker(ItManager* obj);
	void newTeacher(char* userID);
	void removeTeacher(char* userID);
	void newStudent(char* userID);
	void removeStudent(char* userID);
	void addRegToCourse(char* courseID, Registration* obj);
	void registerNewCourse(char* studentID, char* courseID);
	void unregisterCourse(char* studentID, char* courseID);
	void addTeacherToDep(char* teachID);
	void printCourses();
	void printGrades(char* courseID);
	int getStudentCount(char* courseID);
	void newMarks(char* courseID);
	void appendMarks(char* courseID);
	void viewMarks(char* courseID);
	void appointTA(char* courseID, TA* obj);
	~Department();
};