#pragma once
#include "Department.h"
#include "Course.h"
#include "Registration.h"
#include "Teacher.h"
#include "It.h"
#include "Student.h"

class University {
	char* name;
	int totalDep;
	Department** depList;
	int teacherCount;
	Teacher** teachList;
	int itCount;
	ItManager** itList;
	int studentCount;
	Student** stList;

public:
	University();
	char* getName();
	void setName(char* _name);
	int getNumOfDep();
	void setNumOfDep(int _num);
	void addTeacherArray(Teacher** point, int size);
	void addITArray(ItManager** point, int size);
	void addStudentArray(Student** point, int size);
	void addTeacher(char* depID, int index, Teacher* obj);
	void addIT(char* depID, ItManager* obj);
	void addStudent(char* depID, int index, Student* obj);
	char* getDepId(int index);
	void print();
	bool addCourse(char* dep, char* _section);
	bool hodChecker(Teacher* obj);
	char* depGetter(Teacher* obj);
	bool courseChecker(char* depId, char* courseID);
	//bool courseAlreadyAssigned(char* courseID);
	bool courseAlreadyAssigned(char* depID, char* courseID);
	bool teacherChecker(char* teachID);
	bool studentChecker(char* studentID);
	bool teacherDepChecker(char* depID, char* teachID);
	bool studentDepChecker(char* depID, char* studentID);
	/*void assignCourse(char* teachID, char* courseID);*/
	void assignCourse(char* depID, char* teachID, char* courseID);
	char* itDepGetter(ItManager* obj);
	bool depChecker(char* depID, char* userID);
	void newTeacher(char* depID, char* userID, char* fName, char* lName);
	void removeTeacher(char* depID, char* userID);
	void newStudent(char* depID, char* userID, char* fName, char* lName);
	void removeStudent(char* depID, char* userID);
	void addRegToCourse(char* depID, char* courseID, Registration* obj);
	bool courseAlreadyRegistered(char* studentID, char* courseID);
	bool courseAlreadyRegistered1(char* studentID, char* courseID);
	void registerNewCourse(char* studentID, char* courseID);
	void unregisterCourse(char* studentID, char* courseID);
	void addTeacherToDep(char* depID, char* teachID);
	void printCourses(char* depID);
	void printGrade(char* depID, char* courseID);
	int getStudentCount(char* depID, char* courseID);
	void newMarks(char* depID, char* courseID);
	void appendMarks(char* depID, char* courseID);
	void viewMarks(char* depID, char* courseID);
	void appointTA(char* depID, char* courseID, TA* obj);
	~University();
};