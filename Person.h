#pragma once

class Person {
	char* name;
	static int numOfPeople;
public:
	Person();
	static int getNumOfPeople();
	void setName(char* _name);
	char* getName();
	virtual void print();
	virtual ~Person();
};