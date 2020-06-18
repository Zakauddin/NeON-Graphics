#pragma once

#include "Person.h"
#include "Employee.h"
#include "Teacher.h"
#include "Student.h"
#include "Course.h"

class TA: public Student, public Teacher {
	char* courseID;

public:
	TA();
	void taCourse(char* _courseID);
	char* getTACourse();
	char* getID();
	void deleteChar();
	//~TA();
};