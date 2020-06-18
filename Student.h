#pragma once
#include "Person.h"
#include "Registration.h"

class Student: public Person {
	char* ID;
	int numOfCourses;
	int count;
	Registration** courses;

public:
	Student();
	Student(char* id);
	virtual char* getID();
	int getNumOfCourses();
	int getNumOfPeople();
	void print();
	void addRegistration(Registration* obj);
	Registration** getCourses();
	Registration* getRegistration(char* regID);
	void printRegDetails(char* regID);
	void printRegDetails(int num);
	bool courseAlreadyRegistered(char* courseID);
	bool courseAlreadyRegistered1(char* courseID);
	void registerNewCourse(char* courseID);
	void unregisterCourse(char* courseID);
	void passwordReset();
	void newPassword(char* tempPass);
	void printCourseIDs();
	void viewAttend(char* courseID);
	void viewMarks(char* courseID);
	void withdraw(char* courseID);
	~Student();
};