#include <iostream>
#include <fstream>
#include "Person.h"
#include "Student.h"
#include "Registration.h"
using namespace std;

Student::Student() : Person() {
	ID = nullptr;
	numOfCourses = NULL;
	count = NULL;
	courses = nullptr;
}

Student::Student(char* id) {
	count = 0;
	int size = strlen(id);
	ID = new char[size + 1];
	for (int i = 0; i < size; i++) {
		ID[i] = id[i];
	}
	ID[size] = '\0';
	ifstream sFile;
	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = ID[i];
	}
	sFile.open(file);
	char buffer[50];
	sFile.getline(buffer, 50);//Password
	sFile.getline(buffer, 50);//Name
	Person::setName(buffer);
	sFile.getline(buffer, 50);
	numOfCourses = atoi(buffer);
	if (numOfCourses > 0) {
		courses = new Registration * [numOfCourses];
	}
	else {
		courses = nullptr;
	}
}

void Student::addRegistration(Registration* obj) {
	courses[count] = obj;
	count++;
}

Registration** Student::getCourses() {
	return courses;
}

char* Student::getID() {
	return ID;
}

int Student::getNumOfCourses() {
	return numOfCourses;
}

int Student::getNumOfPeople() {
	return Person::getNumOfPeople();
}

void Student::print() {
	cout << "ID: " << ID << endl;
	cout << "Name: " << Person::getName() << endl;
	cout << "Number of courses: " << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		cout << "Course #" << i + 1 << ":" << courses[i]->getCourseID() << endl;
	}
}

Registration* Student::getRegistration(char* regID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courses[i]->getCourseID(), regID) == 0) {
			return courses[i];
		}
	}
	return nullptr;
}

void Student::printRegDetails(char* regID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courses[i]->getCourseID(), regID) == 0) {
			courses[i]->print();
		}
	}
}

void Student::printRegDetails(int num) {
	for (int i = 0; i < numOfCourses; i++) {
		if (i == num) {
			courses[i]->print();
		}
	}
}

bool Student::courseAlreadyRegistered(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		char* temp = courses[i]->getCourseID();
		bool found = true;
		for (int j = 0; j < 5 && found == true; j++){
			if (temp[j] != courseID[j]) {
				found = false;
			}
		}
		if (found == true) {
			return true;
		}
		temp = nullptr;
	}
	return false;
}

bool Student::courseAlreadyRegistered1(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		char* temp = courses[i]->getCourseID();
		bool found = true;
		for (int j = 0; j < 7 && found == true; j++) {
			if (temp[j] != courseID[j]) {
				found = false;
			}
		}
		if (found == true) {
			return true;
		}
		temp = nullptr;
	}
	return false;
}

void Student::registerNewCourse(char* courseID) {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = ID[i];
	}
	char buffer[20];
	ifstream uFile(file);
	uFile.getline(buffer, 50);
	uFile.close();
	ofstream newFile(file);
	newFile << buffer << endl;
	newFile << Person::getName() << endl;
	newFile << numOfCourses + 1 << endl;
	for (int i = 0; i < numOfCourses; i++) {
		newFile << courses[i]->getCourseID() << endl;
		int num = courses[i]->getNumOfAttend();
		newFile << num << endl;
		int* attend = courses[i]->getAttend();
		if (num == 0) {
			newFile << 0 << endl;
		}
		else {
			for (int j = 0; j < num; j++) {
				newFile << attend[j] << ",";
			}
			newFile << endl;
		}
		attend = nullptr;
		num = courses[i]->getNumOfMarks();
		newFile << num << endl;
		int* marks = courses[i]->getMarks();
		if (num == 0) {
			newFile << 0 << endl;
		}
		else {
			for (int j = 0; j < num; j++) {
				newFile << marks[j] << ",";
			}
			newFile << endl;
		}
		marks = nullptr;
		newFile << courses[i]->getGrade() << endl;
	}
	newFile << courseID << endl;
	for (int i = 0; i < 5; i++) {
		newFile << "0" << endl;
	}
	newFile.close();
}

void Student::unregisterCourse(char* courseID) {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = ID[i];
	}
	char buffer[20];
	ifstream uFile(file);
	uFile.getline(buffer, 50);
	uFile.close();
	ofstream newFile(file);
	newFile << buffer << endl;
	newFile << Person::getName() << endl;
	newFile << numOfCourses - 1 << endl;
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courses[i]->getCourseID(), courseID) != 0) {
			newFile << courses[i]->getCourseID() << endl;
			int num = courses[i]->getNumOfAttend();
			newFile << num << endl;
			int* attend = courses[i]->getAttend();
			if (num == 0) {
				newFile << 0 << endl;
			}
			else {
				for (int j = 0; j < num; j++) {
					newFile << attend[j] << ",";
				}
				newFile << endl;
			}
			attend = nullptr;
			num = courses[i]->getNumOfMarks();
			newFile << num << endl;
			int* marks = courses[i]->getMarks();
			if (num == 0) {
				newFile << 0 << endl;
			}
			else {
				for (int j = 0; j < num; j++) {
					newFile << marks[j] << ",";
				}
				newFile << endl;
			}
			marks = nullptr;
			newFile << courses[i]->getGrade() << endl;
		}
	}
	newFile.close();
}

void Student::passwordReset() {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = ID[i];
	}
	ofstream newFile(file);
	newFile << "pass" << endl;
	newFile << Person::getName() << endl;
	newFile << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		newFile << courses[i]->getCourseID() << endl;
		int num = courses[i]->getNumOfAttend();
		newFile << num << endl;
		int* attend = courses[i]->getAttend();
		if (num == 0) {
			newFile << 0 << endl;
		}
		else {
			for (int j = 0; j < num; j++) {
				newFile << attend[j] << ",";
			}
			newFile << endl;
		}
		attend = nullptr;
		num = courses[i]->getNumOfMarks();
		newFile << num << endl;
		int* marks = courses[i]->getMarks();
		if (num == 0) {
			newFile << 0 << endl;
		}
		else {
			for (int j = 0; j < num; j++) {
				newFile << marks[j] << ",";
			}
			newFile << endl;
		}
		marks = nullptr;
		newFile << courses[i]->getGrade() << endl;
	}
	newFile.close();
}

void Student::newPassword(char* tempPass) {
	char file[] = { "      .txt" };
	for (int i = 0; i < 6; i++) {
		file[i] = ID[i];
	}
	ofstream newFile(file);
	newFile << tempPass << endl;
	newFile << Person::getName() << endl;
	newFile << numOfCourses << endl;
	for (int i = 0; i < numOfCourses; i++) {
		newFile << courses[i]->getCourseID() << endl;
		int num = courses[i]->getNumOfAttend();
		newFile << num << endl;
		int* attend = courses[i]->getAttend();
		if (num == 0) {
			newFile << 0 << endl;
		}
		else {
			for (int j = 0; j < num; j++) {
				newFile << attend[j] << ",";
			}
			newFile << endl;
		}
		attend = nullptr;
		num = courses[i]->getNumOfMarks();
		newFile << num << endl;
		int* marks = courses[i]->getMarks();
		if (num == 0) {
			newFile << 0 << endl;
		}
		else {
			for (int j = 0; j < num; j++) {
				newFile << marks[j] << ",";
			}
			newFile << endl;
		}
		marks = nullptr;
		newFile << courses[i]->getGrade() << endl;
	}
	newFile.close();
}

void Student::printCourseIDs() {
	for (int i = 0; i < numOfCourses; i++) {
		cout << "Course #" << i + 1 << ": " << courses[i]->getCourseID() << endl;
	}
}

void Student::viewAttend(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courses[i]->getCourseID(), courseID) == 0) {
			int tempCount = courses[i]->getNumOfAttend();
			if (tempCount != 0) {
				int* temp = courses[i]->getAttend();
				for (int j = 0; j < tempCount; j++) {
					cout << "Day " << j + 1 << ": ";
					if (temp[j] == 0) {
						cout << "Absent" << endl;
					}
					else {
						cout << "Present" << endl;
					}
				}
				temp = nullptr;
			}
			else {
				cout << "No attendance recorded yet." << endl;
			}
		}
	}
}

void Student::viewAttendGraphics(RenderWindow& window, Font& font, char* courseID) {
	Texture backgroundImg;
	backgroundImg.loadFromFile("background.png");
	Sprite background(backgroundImg);
	background.scale((float)0.69, (float)0.69);
	background.setPosition(0, 0);

	window.clear();

	

	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courses[i]->getCourseID(), courseID) == 0) {
			int tempCount = courses[i]->getNumOfAttend();
			window.draw(background);
			Text uniName;
			uniName.setFont(font);
			uniName.setString(courses[i]->getCourseID());
			uniName.setCharacterSize(100);
			uniName.setFillColor(Color::Black);
			uniName.setStyle(Text::Bold);
			FloatRect textRect = uniName.getLocalBounds();
			uniName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			uniName.setPosition(Vector2f(1280 / 2.0f, 100));
			window.draw(uniName);
			if (tempCount != 0) {
				int* temp = courses[i]->getAttend();
				for (int j = 0; j < tempCount; j++) {
					char day[] = { "Day  " };
					char buffer[5];
					_itoa_s(j + 1, buffer, 10);
					day[4] =buffer[0];
					uniName.setFont(font);
					uniName.setString(day);
					uniName.setCharacterSize(50);
					uniName.setFillColor(Color::Black);
					uniName.setStyle(Text::Bold);
					FloatRect textRect = uniName.getLocalBounds();
					uniName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					uniName.setPosition(320, 200 + (j * 75));
					window.draw(uniName);
					if (temp[j] == 0) {
						Text uniName;
						uniName.setFont(font);
						uniName.setString("Absent");
						uniName.setCharacterSize(50);
						uniName.setFillColor(Color::Black);
						uniName.setStyle(Text::Bold);
						FloatRect textRect = uniName.getLocalBounds();
						uniName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
						uniName.setPosition(Vector2f(1280 / 2.0f, 200 + (j * 75)));
						window.draw(uniName);

					}
					else {
						Text uniName;
						uniName.setFont(font);
						uniName.setString("Present");
						uniName.setCharacterSize(50);
						uniName.setFillColor(Color::Black);
						uniName.setStyle(Text::Bold);
						FloatRect textRect = uniName.getLocalBounds();
						uniName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
						uniName.setPosition(Vector2f(1280 / 2.0f, 200 + (j * 75)));
						window.draw(uniName);
					}
				}
				temp = nullptr;
			}
			else {
				cout << "No attendance recorded yet." << endl;
			}
		}
	}
	window.display();
}

void Student::viewMarks(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courses[i]->getCourseID(), courseID) == 0) {
			int* temp = courses[i]->getMarks();
			for (int j = 0; j < courses[i]->getNumOfMarks(); j++) {
				cout << "Evaluation " << j + 1 << ": ";
				cout << temp[j] << endl;
			}
			temp = nullptr;
		}
	}
}

void Student::viewMarksGraphics(RenderWindow& window, Font& font, char* courseID) {
	Texture backgroundImg;
	backgroundImg.loadFromFile("background.png");
	Sprite background(backgroundImg);
	background.scale((float)0.69, (float)0.69);
	background.setPosition(0, 0);

	window.clear();

	

	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courses[i]->getCourseID(), courseID) == 0) {
			window.draw(background);
			Text uniName;
			uniName.setFont(font);
			uniName.setString(courses[i]->getCourseID());
			uniName.setCharacterSize(100);
			uniName.setFillColor(Color::Black);
			uniName.setStyle(Text::Bold);
			FloatRect textRect = uniName.getLocalBounds();
			uniName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			uniName.setPosition(Vector2f(1280 / 2.0f, 100));
			window.draw(uniName);
			int tempCount = courses[i]->getNumOfMarks();
			if (tempCount != 0) {
				int* temp = courses[i]->getMarks();
				for (int j = 0; j < tempCount; j++) {
					char day[] = { "Evaluation  " };
					char buffer[5];
					_itoa_s(j + 1, buffer, 10);
					day[11] = buffer[0];
					uniName.setFont(font);
					uniName.setString(day);
					uniName.setCharacterSize(50);
					uniName.setFillColor(Color::Black);
					uniName.setStyle(Text::Bold);
					FloatRect textRect = uniName.getLocalBounds();
					uniName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					uniName.setPosition(320, 200 + (j * 75));
					window.draw(uniName);

					_itoa_s(temp[j], buffer, 10);

					Text marksText;
					marksText.setFont(font);
					marksText.setString(buffer);
					marksText.setCharacterSize(50);
					marksText.setFillColor(Color::Black);
					marksText.setStyle(Text::Bold);
					textRect = marksText.getLocalBounds();
					marksText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					marksText.setPosition(Vector2f(1280 / 2.0f, 200 + (j * 75)));
					window.draw(marksText);
				}
				temp = nullptr;
			}
			else {
				cout << "No attendance recorded yet." << endl;
			}
		}
	}
	window.display();
}

void Student::withdraw(char* courseID) {
	for (int i = 0; i < numOfCourses; i++) {
		if (strcmp(courses[i]->getCourseID(), courseID) == 0) {
			char* tempGrade = courses[i]->getGrade();
			if (tempGrade[0] != 'W') {
				courses[i]->withdraw();
			}
			tempGrade = nullptr;
		}	
	}
}



Student::~Student() {
	if (ID != nullptr) {
		delete[]ID;
	}
	ID = nullptr;
	if (courses != nullptr) {
		delete[]courses;
	}
	courses = nullptr;
}