#include <iostream>
#include <fstream>
#include "Registration.h"
using namespace std;

int reader(char tempData[][50], char* studentID, char* courseID) {
	ifstream rFile;
	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = studentID[i];
	}
	rFile.open(file);
	char buffer[50];
	int count = 0;
	rFile.getline(buffer, 50);
	strcpy_s(tempData[count], buffer);
	count++;
	rFile.getline(buffer, 50);
	while (strcmp(buffer, courseID) != 0) {
		strcpy_s(tempData[count], buffer);
		count++;
		rFile.getline(buffer, 50);
	}
	for (int i = 0; i < 5; i++) {
		rFile.getline(buffer, 50);
	}
	while (rFile.getline(buffer, 50)) {
		strcpy_s(tempData[count], buffer);
		count++;
	}
	rFile.close();
	return count;
}

inline int calcAvg(int* arr, int size) {
	int avg = 0;
	for (int i = 0; i < size; i++) {
		avg += arr[i];
	}
	return avg / size;
}

Registration::Registration() {
	studentID = nullptr;
	courseID = nullptr;
	courseName = nullptr;
	numOfAttend = NULL;
	attendance  = nullptr;
	numOfMarks = NULL;
	marks = nullptr;
	grade = nullptr;
}

Registration::Registration(char* _student, char* _course) {
	int size = strlen(_student);
	studentID = new char[size + 1];
	for (int i = 0; i < size; i++) {
		studentID[i] = _student[i];
	}
	studentID[size] = '\0';

	size = strlen(_course);
	courseID = new char[size + 1];
	for (int i = 0; i < size; i++) {
		courseID[i] = _course[i];
	}
	courseID[size] = '\0';

	ifstream rFile;
	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = _student[i];
	}
	rFile.open(file);
	char buffer[50];
	rFile.getline(buffer, 50);
	
	while (strcmp(buffer, _course) != 0) {
		rFile.getline(buffer, 50);
	}

	char file1[] = "       .txt";
	for (int i = 0; i < 7; i++) {
		file1[i] = courseID[i];
	}
	ifstream cFile(file1);
	cFile.getline(buffer, 50);
	size = strlen(buffer);
	courseName = new char[size + 1];
	for (int i = 0; i < size; i++) {
		courseName[i] = buffer[i];
	}
	courseName[size] = '\0';
	cFile.close();

	rFile.getline(buffer, 50);
	numOfAttend = atoi(buffer);
	attendance  = new int[numOfAttend];
	for (int i = 0; i < numOfAttend; i++) {
		rFile.getline(buffer, 200, ',');
		attendance [i] = atoi(buffer);
	}
	rFile.getline(buffer, 200);
	rFile.getline(buffer, 200);
	numOfMarks = atoi(buffer);
	marks = new int[numOfMarks];
	for (int i = 0; i < numOfMarks; i++) {
		rFile.getline(buffer, 200, ',');
		marks[i] = atoi(buffer);
	}
	rFile.getline(buffer, 200);
	rFile.getline(buffer, 200);
	size = strlen(buffer);
	grade = new char[size + 1];
	for (int i = 0; i < size; i++) {
		grade[i] = buffer[i];
	}
	grade[size] = '\0';
	rFile.close();	
}

char* Registration::getCourseID() {
	return courseID;
}

char* Registration::getStudentID() {
	return studentID;
}

void Registration::newAttend() {
	char tempData[33][50];
	int count = reader(tempData, studentID, courseID);
	cout << "Please press 1 for present or press 0 for absent: " << endl;
	cout << studentID << ": ";
	int attend;
	cin >> attend;
	while ((attend != 0) && (attend != 1)) {
		cout << "Wrong Input. Please press 1 for present or press 0 for absent: ";
		cin >> attend;
	}
	numOfAttend++;
	int* temp = new int[numOfAttend];
	for (int i = 0; i < numOfAttend - 1; i++) {
		temp[i] = attendance [i];
	}
	temp[numOfAttend - 1] = attend;
	if (attendance  != nullptr) {
		delete[]attendance ;
	}
	attendance  = temp;
	temp = nullptr;

	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = studentID[i];
	}
	ofstream newFile(file);
	for (int i = 0; i < count; i++) {
		newFile << tempData[i] << endl;
	}
	newFile<< courseID << endl;
	newFile << numOfAttend << endl;
	for (int i = 0; i < numOfAttend; i++) {
		newFile << attendance [i] << ',';
	}
	newFile << endl;
	newFile << numOfMarks << endl;
	for (int i = 0; i < numOfMarks; i++) {
		newFile << marks[i] << ',';
	}
	newFile << endl;
	newFile << grade << endl;
	newFile.close();
}

void Registration::appendAttend() {
	cout << "Please enter the day you want to edit: ";
	int day;
	cin >> day;
	while ((day < 1) || (day > numOfAttend)) {
		cout << endl << "Invalid day!" << endl;
		cout << "Please enter the day you want to edit: ";
		cin >> day;
	}
	cout << "Please press 1 for present or press 0 for absent: " << endl;
	int attend;
	cin >> attend;
	while ((attend != 0) && (attend != 1)) {
		cout << "Wrong Input. Please press 1 for present or press 0 for absent: ";
		cin >> attend;
	}
	attendance[day - 1] = attend;
	char tempData[33][50];
	int count = reader(tempData, studentID, courseID);
	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = studentID[i];
	}
	ofstream newFile(file);
	for (int i = 0; i < count; i++) {
		newFile << tempData[i] << endl;
	}
	newFile << courseID << endl;
	newFile << numOfAttend << endl;
	for (int i = 0; i < numOfAttend; i++) {
		newFile << attendance[i] << ',';
	}
	newFile << endl;
	newFile << numOfMarks << endl;
	for (int i = 0; i < numOfMarks; i++) {
		newFile << marks[i] << ',';
	}
	newFile << endl;
	newFile << grade << endl;
	newFile.close();
}

int* Registration::getAttend() {
	return attendance ;
}

int Registration::getNumOfAttend() {
	return numOfAttend;
}

void Registration::newMarks() {
	cout << "Please enter the percentage (Number between 0 and 100): " << endl;
	cout << studentID << ": ";
	int marksInput;
	cin >> marksInput;
	while ((marksInput < 0) || (marksInput > 100)) {
		cout << "Please enter the percentage (Number between 0 and 100): ";
		cin >> marksInput;
	}
	numOfMarks++;
	int* temp = new int[numOfMarks];
	for (int i = 0; i < numOfMarks - 1; i++) {
		temp[i] = marks[i];
	}
	temp[numOfMarks - 1] = marksInput;
	if (marks != nullptr) {
		delete[]marks;
	}
	marks = temp;
	temp = nullptr;
	char tempData[33][50];
	int count = reader(tempData, studentID, courseID);
	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = studentID[i];
	}
	ofstream newFile(file);
	for (int i = 0; i < count; i++) {
		newFile << tempData[i] << endl;
	}
	newFile << courseID << endl;
	newFile << numOfAttend << endl;
	for (int i = 0; i < numOfAttend; i++) {
		newFile << attendance[i] << ',';
	}
	newFile << endl;
	newFile << numOfMarks << endl;
	for (int i = 0; i < numOfMarks; i++) {
		newFile << marks[i] << ',';
	}
	newFile << endl;
	newFile << grade << endl;
	newFile.close();
}

void Registration::appendMarks() {
	cout << "Please enter the evaluation you want to edit: ";
	int eval;
	cin >> eval;
	while ((eval < 1) || (eval > numOfMarks)) {
		cout << endl << "Invalid evaluation!" << endl;
		cout << "Please enter the evaluation you want to edit: ";
		cin >> eval;
	}
	cout << "Please enter the percentage (Number between 0 and 100): " << endl;
	int marksInput;
	cin >> marksInput;
	while ((marksInput < 0) || (marksInput > 100)) {
		cout << "Please enter the percentage (Number between 0 and 100): ";
		cin >> marksInput;
	}
	marks[eval - 1] = marksInput;
	char tempData[33][50];
	int count = reader(tempData, studentID, courseID);
	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = studentID[i];
	}
	ofstream newFile(file);
	for (int i = 0; i < count; i++) {
		newFile << tempData[i] << endl;
	}
	newFile << courseID << endl;
	newFile << numOfAttend << endl;
	for (int i = 0; i < numOfAttend; i++) {
		newFile << attendance[i] << ',';
	}
	newFile << endl;
	newFile << numOfMarks << endl;
	for (int i = 0; i < numOfMarks; i++) {
		newFile << marks[i] << ',';
	}
	newFile << endl;
	newFile << grade << endl;
	newFile.close();
}

int* Registration::getMarks() {
	return marks;
}

int Registration::getNumOfMarks() {
	return numOfMarks;
}

void Registration::print() {
	cout << courseName << endl;
	cout << "attendance : " << endl;
	for (int i = 0; i < numOfAttend; i++) {
		cout << "Day " << i + 1 << ":";
		if (attendance [i] == 0) {
			cout << "Absent." << endl;
		}
		else {
			cout << "Present." << endl;
		}
	}
	cout << "Marks: " << endl;
	for (int i = 0; i < numOfMarks; i++) {
		cout << "Evaluation " << i + 1 << ":" << marks[i] << endl;
	}
}

void Registration::setAutoGrade() {
	int avg = calcAvg(marks, numOfMarks);
	if (avg >= 90) {
		grade = new char[3];
		grade[0] = 'A';
		grade[1] = '+';
		grade[1] = '\0';
	}
	else if (avg >= 80) {
		grade = new char[2];
		grade[0] = 'A';
		grade[1] = '\0';
	}
	else if (avg >= 70) {
		grade = new char[2];
		grade[0] = 'B';
		grade[1] = '\0';
	}
	else if (avg >= 60) {
		grade = new char[2];
		grade[0] = 'C';
		grade[1] = '\0';
	}
	else if (avg >= 50) {
		grade = new char[2];
		grade[0] = 'D';
		grade[1] = '\0';
	}
	else if (avg < 50) {
		grade = new char[2];
		grade[0] = 'F';
		grade[1] = '\0';
	}
}

void Registration::newGrades() {
	cout << "Please enter the grade for the Student: " << endl;
	cout << studentID << ": ";
	char gradeInput[5];
	cin >> gradeInput;
	while ((strcmp(gradeInput, "A+") != 0) && (strcmp(gradeInput, "A") != 0) && (strcmp(gradeInput, "B") != 0) && (strcmp(gradeInput, "C") != 0) && (strcmp(gradeInput, "D") != 0) && (strcmp(gradeInput, "F") != 0)) {
		cout << "Please enter a valid Grade: ";
		cin >> gradeInput;
	}
	int size = strlen(gradeInput);
	grade = new char[size + 1];
	for (int i = 0; i < size; i++) {
		grade[i] = gradeInput[i];
	}
	grade[size] = '\0';
	char tempData[33][50];
	int count = reader(tempData, studentID, courseID);
	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = studentID[i];
	}
	ofstream newFile(file);
	for (int i = 0; i < count; i++) {
		newFile << tempData[i] << endl;
	}
	newFile << courseID << endl;
	newFile << numOfAttend << endl;
	for (int i = 0; i < numOfAttend; i++) {
		newFile << attendance[i] << ',';
	}
	newFile << endl;
	newFile << numOfMarks << endl;
	for (int i = 0; i < numOfMarks; i++) {
		newFile << marks[i] << ',';
	}
	newFile << endl;
	newFile << grade << endl;
	newFile.close();
}

char* Registration::getGrade() {
	if (grade == nullptr) {
		return nullptr;
	}
	else {
		return grade;
	}
}

void Registration::Registration::withdraw() {
	char tempData[33][50];
	int count = reader(tempData, studentID, courseID);
	char file[] = "      .txt";
	for (int i = 0; i < 6; i++) {
		file[i] = studentID[i];
	}	
	ofstream newFile(file);
	for (int i = 0; i < count; i++) {
		newFile << tempData[i] << endl;
	}
	newFile << courseID << endl;
	newFile << numOfAttend << endl;
	for (int i = 0; i < numOfAttend; i++) {
		newFile << attendance[i] << ',';
	}
	newFile << endl;
	newFile << numOfMarks << endl;
	for (int i = 0; i < numOfMarks; i++) {
		newFile << marks[i] << ',';
	}
	newFile << endl;
	newFile << "W" << endl;
	newFile.close();
}

Registration::~Registration() {
	if (studentID != nullptr) {
		delete[]studentID;
	}
	studentID = nullptr;
	if (courseID != nullptr) {
		delete[]courseID;
	}
	courseID = nullptr;
	if (courseName != nullptr) {
		delete[]courseName;
	}
	courseName = nullptr;
	if (courseID != nullptr) {
		delete[]courseID;
	}
	courseID = nullptr;
	if (attendance != nullptr) {
		delete[]attendance;
	}
	attendance = nullptr;
	if (marks != nullptr) {
		delete[]marks;
	}
	marks = nullptr;
	if (grade != nullptr) {
		delete[]grade;
	}
	grade = nullptr;
}