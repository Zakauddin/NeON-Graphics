#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "University.h"
#include "Department.h"
#include "Course.h"
#include "Registration.h"
#include "Teacher.h"
#include "It.h"
#include "Student.h"
using namespace std;
using namespace sf;

void printText(RenderWindow& window, Font& font, int SCRWIDTH, int SCRHEIGHT, char* text) {
	Text  closeProgram;
	closeProgram.setFont(font);
	closeProgram.setString(text);
	closeProgram.setCharacterSize(100);
	closeProgram.setFillColor(Color::Black);
	closeProgram.setStyle(Text::Bold);
	FloatRect textRect = closeProgram.getLocalBounds();
	closeProgram.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	closeProgram.setPosition(Vector2f(SCRWIDTH / 2.0f, SCRHEIGHT / 2.0f));
	window.draw(closeProgram);
}

void invalidPrintText(RenderWindow& window, Font& font, int SCRWIDTH, int SCRHEIGHT) {
	Text invalid;
	invalid.setFont(font);
	invalid.setString("INVALID INPUT!");
	invalid.setCharacterSize(50);
	invalid.setFillColor(Color::Red);
	invalid.setStyle(Text::Bold);
	FloatRect textRect = invalid.getLocalBounds();
	invalid.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	invalid.setPosition(Vector2f(SCRWIDTH / 2.0f, 450));
	window.draw(invalid);
}

void teacherPrintText(RenderWindow& window, Font& font, int SCRWIDTH, int SCRHEIGHT) {
	Text teacherText;
	teacherText.setFont(font);
	teacherText.setString("Teacher ID");
	teacherText.setCharacterSize(80);
	teacherText.setFillColor(Color::Black);
	teacherText.setStyle(Text::Bold);
	FloatRect textRect = teacherText.getLocalBounds();
	teacherText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	teacherText.setPosition(Vector2f(SCRWIDTH / 2.0f, 200));
	window.draw(teacherText);
}

void studentPrintText(RenderWindow& window, Font& font, int SCRWIDTH, int SCRHEIGHT) {
	Text studentText;
	studentText.setFont(font);
	studentText.setString("Student ID");
	studentText.setCharacterSize(80);
	studentText.setFillColor(Color::Black);
	studentText.setStyle(Text::Bold);
	FloatRect textRect = studentText.getLocalBounds();
	studentText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	studentText.setPosition(Vector2f(SCRWIDTH / 2.0f, 200));
	window.draw(studentText);
}

void coursePrintText(RenderWindow& window, Font& font, int SCRWIDTH, int SCRHEIGHT) {
	Text courseText;
	courseText.setFont(font);
	courseText.setString("Course ID");
	courseText.setCharacterSize(80);
	courseText.setFillColor(Color::Black);
	courseText.setStyle(Text::Bold);
	FloatRect textRect = courseText.getLocalBounds();
	courseText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	courseText.setPosition(Vector2f(SCRWIDTH / 2.0f, 200));
	window.draw(courseText);
}

int Person::numOfPeople = 0;

template<class type>
type* objectFinder(char* _id, type** list, int size) {
	for (int i = 0; i < size; i++) {
		char* tempId = list[i]->getID();
		bool found = true;
		int size1 = strlen(tempId);
		for (int j = 0; j < size1; j++) {
			if (tempId[j] != _id[j]) {
				found = false;
			}
		}
		if (found == true) {
			return list[i];
		}
	}
	return nullptr;
}

template <class type>
class Container {
	type** list;
	int totalNum;
	int current;

public:
	Container();
	Container(int n);
	void insert(type* obj);
	type** getList();
	~Container();
};

template <class type>
Container<type>::Container() {
	list = nullptr;
	totalNum = NULL;
	current = NULL;
}

template <class type>
Container<type>::Container(int n) {
	totalNum = n;
	current = 0;
	list = new type * [totalNum];
}

template <class type>
void Container<type>::insert(type* obj) {
	list[current] = obj;
	current++;
}

template <class type>
type** Container<type>::getList() {
	return list;
}

template <class type>
Container<type>::~Container() {
	if (list != nullptr) {
		for (int i = 0; i < totalNum; i++) {
			delete list[i];
		}
		delete[]list;
	}
}

int main()
{
	University uni;

	////////Creating Teacher Ojects.
	ifstream TIFile;
	TIFile.open("TeacherInfo.txt");
	char buffer[50];
	TIFile.getline(buffer, 50);
	int tNumOfTeach = atoi(buffer);
	Container<Teacher> teachList(tNumOfTeach);
	for (int i = 0; i < tNumOfTeach; i++) {
		TIFile.getline(buffer, 50);
		Teacher* tempTeach = new Teacher(buffer);
		teachList.insert(tempTeach);
	}
	TIFile.close();

	////////Creating IT Manager Ojects.
	ifstream ITIFile;
	ITIFile.open("itInfo.txt");
	ITIFile.getline(buffer, 50);
	int tNumOfIT = atoi(buffer);
	Container<ItManager> itList(tNumOfIT);
	for (int i = 0; i < tNumOfIT; i++) {
		ITIFile.getline(buffer, 50);
		ItManager* tempIT = new ItManager(buffer);
		itList.insert(tempIT);
	}
	ITIFile.close();

	////////Creating Student Ojects.
	ifstream StIFile;
	StIFile.open("StudentInfo.txt");
	StIFile.getline(buffer, 50);
	int tNumOfSt = atoi(buffer);
	Container<Student> stList(tNumOfSt);
	for (int i = 0; i < tNumOfSt; i++) {
		StIFile.getline(buffer, 50);
		Student* tempSt = new Student(buffer);
		stList.insert(tempSt);
	}
	StIFile.close();

	////////Creating TA Ojects.
	ifstream TAIFile;
	TAIFile.open("TAInfo.txt");
	TAIFile.getline(buffer, 50);
	int tNumOfTA = atoi(buffer);
	TA** TAList = new TA * [tNumOfTA];
	for (int i = 0; i < tNumOfTA; i++) {
		TAIFile.getline(buffer, 50, ',');
		Student* tempStudent = objectFinder(buffer, stList.getList(), tNumOfSt);
		TA* tempTA = (TA*)tempStudent;
		TAIFile.getline(buffer, 50);
		tempTA->taCourse(buffer);
		char tempID[3];
		tempID[0] = buffer[0];
		tempID[1] = buffer[1];
		tempID[2] = '\0';
		uni.appointTA(tempID, buffer, tempTA);
		TAList[i] = tempTA;
		tempStudent = nullptr;
		tempTA = nullptr;
	}
	TAIFile.close();

	////////Adding Registration Objects to Students.
	Student** students = stList.getList();
	for (int i = 0; i < tNumOfSt; i++) {
		char* currentID = students[i]->getID();
		ifstream sFile;
		char file[] = "      .txt";
		for (int j = 0; j < 6; j++) {
			file[j] = currentID[j];
		}
		sFile.open(file);
		char buffer[50];
		sFile.getline(buffer, 50);//Password
		sFile.getline(buffer, 50);//Name
		sFile.getline(buffer, 50);
		int numOfCourses = atoi(buffer);
		for (int k = 0; k < numOfCourses; k++) {
			sFile.getline(buffer, 50);
			Registration* temp = new Registration(currentID, buffer);
			students[i]->addRegistration(temp);
			for (int j = 0; j < 5; j++) {
				sFile.getline(buffer, 50);
			}
		}
		sFile.close();
	}

	for (int i = 0; i < uni.getNumOfDep(); i++) {
		char* depID = uni.getDepId(i);
		char dfile[] = { "  .txt" };
		for (int i = 0; i < 2; i++) {
			dfile[i] = depID[i];
		}
		ifstream dFile;
		dFile.open(dfile);
		dFile.getline(buffer, 50);//Name
		dFile.getline(buffer, 50);//Number of Courses
		int numOFCour = atoi(buffer);
		for (int j = 0; j < numOFCour; j++) {
			dFile.getline(buffer, 50);
			char courseID[8];
			strcpy_s(courseID, buffer);
			char file1[] = { "       .txt" };
			for (int i = 0; i < 7; i++) {
				file1[i] = buffer[i];
			}
			ifstream cFile(file1);
			cFile.getline(buffer, 50);
			cFile.getline(buffer, 50);
			cFile.getline(buffer, 50);
			int stNum = atoi(buffer);
			for (int j = 0; j < stNum; j++) {
				cFile.getline(buffer, 50);
				Registration* temp = objectFinder(buffer, stList.getList(), tNumOfSt)->getRegistration(courseID);
				uni.addRegToCourse(depID, courseID, temp);
			}
		}
		dFile.getline(buffer, 50);//Number of Teachers
		int numOfTeach = atoi(buffer);
		for (int j = 0; j < numOfTeach; j++) {
			dFile.getline(buffer, 50);
			Teacher* tempTeach = objectFinder(buffer, teachList.getList(), tNumOfTeach);
			if (j == 0) {
				char temp[] = { "Head of Department" };
				tempTeach->setTitle(temp);
			}
			else {
				char temp[] = { "Teacher" };
				tempTeach->setTitle(temp);
			}
			uni.addTeacher(depID, j, tempTeach);
		}
		dFile.getline(buffer, 50);//IT Manager
		ItManager* tempIt = objectFinder(buffer, itList.getList(), tNumOfIT);
		uni.addIT(depID, tempIt);

		dFile.getline(buffer, 50);//Number of Students
		int numOfStud = atoi(buffer);
		for (int j = 0; j < numOfStud; j++) {
			dFile.getline(buffer, 50);
			Student* tempStud = objectFinder(buffer, stList.getList(), tNumOfSt);
			uni.addStudent(depID, j, tempStud);
		}
	}
	uni.addStudentArray(stList.getList(), tNumOfSt);
	uni.addTeacherArray(teachList.getList(), tNumOfTeach);
	uni.addITArray(itList.getList(), tNumOfIT);

	int SCRWIDTH = 1280;
	int SCRHEIGHT = 720;
	
    RenderWindow window(VideoMode(SCRWIDTH, SCRHEIGHT), "NeON");

	Font font;
	font.loadFromFile("arial.ttf");

	Texture backgroundImg;
	backgroundImg.loadFromFile("background.png");
	Sprite background(backgroundImg);
	background.scale((float)0.69, (float)0.69);
	background.setPosition(0, 0);

	RectangleShape rectangle(Vector2f(120, 50));
	rectangle.setSize(Vector2f(200, 110));
	rectangle.setFillColor(Color::Transparent);
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(Color::Transparent);

	bool done = false;

	bool usernameScreen = true;
	bool passwordScreen = false;
	bool cUser = false;
	bool cPass = false;
	bool isHOD = false;
	bool isTeacher = false;
	
	bool taskSelector = false;
	bool task1B = false;
	bool task2B = false;
	bool task3B = false;
	bool task4B = false;
	bool task5B = false;
	bool task6B = false;
	bool attendOption = false;

	bool validCourse = false;
	bool validTeacherID = false;
	bool validStudentID = false;

	int count = 0;
	char input[20] = { ' ' };
	char tempPass[20];
	char* depID = nullptr;

	char username[7];
	char courseID[8];
	char teachID[7];
	char studentID[7];

	Teacher* teacherUser = nullptr;

	uni.print();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);

		Text uniName;
		uniName.setFont(font);
		uniName.setString(uni.getName());
		uniName.setCharacterSize(80);
		uniName.setFillColor(Color::Black);
		uniName.setStyle(Text::Bold);

		FloatRect textRect = uniName.getLocalBounds();
		uniName.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		uniName.setPosition(Vector2f(SCRWIDTH / 2.0f, 80));
		window.draw(uniName);

		ifstream uFile;
		if (usernameScreen == true) {
			Text _username;
			_username.setFont(font);
			_username.setString("USERNAME");
			_username.setCharacterSize(80);
			_username.setFillColor(Color::Black);
			_username.setStyle(Text::Bold);

			FloatRect textRect = _username.getLocalBounds();
			_username.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			_username.setPosition(Vector2f(SCRWIDTH / 2.0f, 250));
			window.draw(_username);

			char file[] = { "      .txt" };
			if (cUser == false) {
				try {
					Sleep(100);
					if (event.type == Event::TextEntered) {
						if (event.text.unicode < 128) {
							if (event.text.unicode == '\r') {
								Sleep(100);
								input[count] = '\0';
								int size = strlen(input);
								if (size != 6) {
									throw size;
								}
								for (int i = 0; i < 6; i++) {
									username[i] = input[i];
								}
								username[6] = '\0';

								for (int i = 0; i < 6; i++) {
									file[i] = username[i];
								}
								uFile.open(file);
								if (uFile.is_open() == true) {
									cUser = true;
									uFile.getline(tempPass, 20);
									uFile.close();
								}
								else {
									throw false;
								}
								usernameScreen = false;
								passwordScreen = true;
								for (int i = 0; i < count; i++) {
									input[i] = ' ';
								}
								count = 0;
							}
							else if (event.text.unicode == '\b') {
								if (count > 0) {
									input[count - 1] = ' ';
									count--;
								}
							}
							else {
								input[count] = static_cast<char>(event.text.unicode);
								count++;
							}
						}
					}
				}
				catch (...) {
					invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
				}
				printText(window, font, SCRWIDTH, SCRHEIGHT, input);
			}
		}
		if (passwordScreen == true) {
			Text _password;
			_password.setFont(font);
			_password.setString("PASSWORD");
			_password.setCharacterSize(80);
			_password.setFillColor(Color::Black);
			_password.setStyle(Text::Bold);

			FloatRect textRect = _password.getLocalBounds();
			_password.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			_password.setPosition(Vector2f(SCRWIDTH / 2.0f, 250));
			window.draw(_password);
			
			if (cPass == false) {
				try {
					Sleep(100);
					if (event.type == Event::TextEntered) {
						if (event.text.unicode < 128) {
							if (event.text.unicode == '\r') {
								input[count] = '\0';
								int size = strlen(input);
								if (size != strlen(tempPass)) {
									throw size;
								}
								if (strcmp(input, tempPass) != 0) {
									throw false;
								}
								cPass = true;
								passwordScreen = false;
								for (int i = 0; i < count; i++) {
									input[i] = ' ';
								}
								count = 0;

								taskSelector = true;

								if (username[0] == 't') {
									teacherUser = objectFinder(username, teachList.getList(), tNumOfTeach);
									isHOD = uni.hodChecker(teacherUser);
									if (isHOD == true) {
										depID = uni.depGetter(teacherUser);
									}
									else {
										isTeacher = true;
									}
								}


							}
							else if (event.text.unicode == '\b') {
								if (count > 0) {
									input[count - 1] = ' ';
									count--;
								}
							}
							else {
								input[count] = static_cast<char>(event.text.unicode);
								count++;
							}
						}

					}
				}
				catch (...) {
					Text invalid;
					invalid.setFont(font);
					invalid.setString("INVALID INPUT!");
					invalid.setCharacterSize(50);
					invalid.setFillColor(Color::Red);
					invalid.setStyle(Text::Bold);

					FloatRect textRect = invalid.getLocalBounds();
					invalid.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					invalid.setPosition(Vector2f(SCRWIDTH / 2.0f, 450));
					window.draw(invalid);
				}
				printText(window, font, SCRWIDTH, SCRHEIGHT, input);
			}			
		}

		if (isHOD == true) {
			if (taskSelector == true) {
				Text task1;
				task1.setFont(font);
				task1.setString("Assign Course");
				task1.setCharacterSize(50);
				task1.setFillColor(Color::Black);
				task1.setStyle(Text::Bold);

				FloatRect textRect = task1.getLocalBounds();
				task1.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task1.setPosition(Vector2f(SCRWIDTH / 2.0f, 200));
				window.draw(task1);

				Text task2;
				task2.setFont(font);
				task2.setString("Register Course");
				task2.setCharacterSize(50);
				task2.setFillColor(Color::Black);
				task2.setStyle(Text::Bold);

				textRect = task2.getLocalBounds();
				task2.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task2.setPosition(Vector2f(SCRWIDTH / 2.0f, 300));
				window.draw(task2);

				Text task3;
				task3.setFont(font);
				task3.setString("Unregister Course");
				task3.setCharacterSize(50);
				task3.setFillColor(Color::Black);
				task3.setStyle(Text::Bold);

				textRect = task3.getLocalBounds();
				task3.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task3.setPosition(Vector2f(SCRWIDTH / 2.0f, 400));
				window.draw(task3);

				Text task4;
				task4.setFont(font);
				task4.setString("View Grades");
				task4.setCharacterSize(50);
				task4.setFillColor(Color::Black);
				task4.setStyle(Text::Bold);

				textRect = task4.getLocalBounds();
				task4.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task4.setPosition(Vector2f(SCRWIDTH / 2.0f, 500));
				window.draw(task4);

				Text task5;
				task5.setFont(font);
				task5.setString("Add Teacher");
				task5.setCharacterSize(50);
				task5.setFillColor(Color::Black);
				task5.setStyle(Text::Bold);

				textRect = task5.getLocalBounds();
				task5.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task5.setPosition(Vector2f(SCRWIDTH / 2.0f, 600));
				window.draw(task5);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
					auto translated_pos = window.mapPixelToCoords(mouse_pos);
					Sleep(500);
					if (task1.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task1B = true;
						validCourse = true;
					}
					if (task2.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task2B = true;
						validStudentID = true;
					}
					if (task3.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task3B = true;
						validStudentID = true;
					}
					if (task4.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task4B = true;
						validCourse = true;
					}
					if (task5.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task5B = true;
						validTeacherID = true;
					}
				}
			}
			if (task1B == true) {
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if ((size < 7) || (size > 7)) {
										throw 0.1;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									char tempDepId[3];
									tempDepId[0] = courseID[0];
									tempDepId[1] = courseID[1];
									tempDepId[2] = '\0';
									if ((tempDepId[0] != depID[0]) && (tempDepId[1] != depID[1])) {
										throw tempDepId;
									}
									if (uni.courseChecker(depID, courseID) == false) {
										throw false;
									}
									if (uni.courseAlreadyAssigned(depID, courseID) == true) {
										throw 1;
									}
									validCourse = false;
									validTeacherID = true;
									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}

						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);

				}
				if (validTeacherID == true) {
					teacherPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									for (int i = 0; i < 6; i++) {
										teachID[i] = input[i];
									}
									teachID[6] = '\0';
									if (teachID[0] != 't') {
										throw true;
									}
									if (uni.teacherDepChecker(depID, teachID) == false) {
										throw 1;
									}

									validTeacherID = false;
									done = true;
									isHOD = false;
									uni.assignCourse(depID, teachID, courseID);

									validTeacherID = false;
									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}

						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
			}
			if (task2B == true) {
				if (validStudentID == true) {
					studentPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if ((size < 6) || (size > 6)) {
										throw size;
									}
									for (int i = 0; i < 6; i++) {
										studentID[i] = input[i];
									}
									studentID[6] = '\0';
									if (uni.studentDepChecker(depID, studentID) == false) {
										// "The below function is a bypass function if HOD has confirmed that a student from another department can pick a course in the department."
										//if(studentChecker(studentID) == false){    
										throw false;
									}

									objectFinder(studentID, stList.getList(), tNumOfSt)->print();
									int numOFCourse = objectFinder(studentID, stList.getList(), tNumOfSt)->getNumOfCourses();
									
									if (numOFCourse < 5) {
										validCourse = true;
									}
									else {
										done = true;
									}

									validStudentID = false;

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}

						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if ((size < 6) || (size > 6)) {
										throw 0.1;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									char tempDepId[3];
									tempDepId[0] = courseID[0];
									tempDepId[1] = courseID[1];
									tempDepId[2] = '\0';
									if ((tempDepId[0] != depID[0]) && (tempDepId[1] != depID[1])) {
										throw tempDepId;
									}
									if (uni.courseChecker(depID, courseID) == false) {
										throw false;
									}
									if (uni.courseAlreadyRegistered(studentID, courseID) == true) {
										throw 1;
									}

									validCourse = false;
									done = true;
									isHOD = false;

									uni.registerNewCourse(studentID, courseID);

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}

						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
			}
			if (task3B == true) {
				if (validStudentID == true) {
					studentPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if ((size < 7) || (size > 7)) {
										throw 0.1;
									}
									for (int i = 0; i < 6; i++) {
										studentID[i] = input[i];
									}
									studentID[6] = '\0';
									if (uni.studentDepChecker(depID, studentID) == false) {
										// "The below function is a bypass function if HOD has confirmed that a student from another department can pick a course in the department."
										//if(studentChecker(studentID) == false){    
										throw false;
									}

									objectFinder(studentID, stList.getList(), tNumOfSt)->print();
									int numOFCourse = objectFinder(studentID, stList.getList(), tNumOfSt)->getNumOfCourses();

									if (numOFCourse > 0) {
										validCourse = true;
									}
									else {
										done = true;
									}

									validStudentID = false;

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}

						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';
									int size = strlen(input);
									if ((size < 7) || (size > 7)) {
										throw 0.1;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									char tempDepId[3];
									tempDepId[0] = courseID[0];
									tempDepId[1] = courseID[1];
									tempDepId[2] = '\0';
									if ((tempDepId[0] != depID[0]) && (tempDepId[1] != depID[1])) {
										throw tempDepId;
									}
									if (uni.courseChecker(depID, courseID) == false) {
										throw false;
									}
									if (uni.courseAlreadyRegistered1(studentID, courseID) == false) {
										throw 1;
									}

									validCourse = false;
									done = true;
									isHOD = false;

									uni.unregisterCourse(studentID, courseID);

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}

						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
			}
			if (task4B == true) {
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if ((size < 7) || (size > 7)) {
										throw 0.1;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									char tempDepId[3];
									tempDepId[0] = courseID[0];
									tempDepId[1] = courseID[1];
									tempDepId[2] = '\0';
									if ((tempDepId[0] != depID[0]) && (tempDepId[1] != depID[1])) {
										throw tempDepId;
									}
									if (uni.courseChecker(depID, courseID) == false) {
										throw false;
									}

									validCourse = false;
									done = true;
									isHOD = false;

									uni.printGradeGraphic(window, font, depID, courseID);
									window.display();
									Sleep(5000);

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}

						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
			}
			if (task5B == true) {
				if (validTeacherID == true) {
					teacherPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									for (int i = 0; i < 6; i++) {
										teachID[i] = input[i];
									}
									teachID[6] = '\0';
									if (teachID[0] != 't') {
										throw true;
									}
									if (uni.teacherChecker(teachID) == false) {
										throw 1;
									}

									validTeacherID = false;
									done = true;
									isHOD = false;
									uni.addTeacherToDep(depID, teachID);

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}
						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
			}
		}

		if (isTeacher == true) {
			if (taskSelector == true) {
				Text task1;
				task1.setFont(font);
				task1.setString("Manage Attendance");
				task1.setCharacterSize(50);
				task1.setFillColor(Color::Black);
				task1.setStyle(Text::Bold);
				FloatRect textRect = task1.getLocalBounds();
				task1.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task1.setPosition(Vector2f(SCRWIDTH / 2.0f, 200));
				window.draw(task1);

				Text task2;
				task2.setFont(font);
				task2.setString("View Attendance");
				task2.setCharacterSize(50);
				task2.setFillColor(Color::Black);
				task2.setStyle(Text::Bold);
				textRect = task2.getLocalBounds();
				task2.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task2.setPosition(Vector2f(SCRWIDTH / 2.0f, 300));
				window.draw(task2);

				Text task3;
				task3.setFont(font);
				task3.setString("Manage Evaluations");
				task3.setCharacterSize(50);
				task3.setFillColor(Color::Black);
				task3.setStyle(Text::Bold);
				textRect = task3.getLocalBounds();
				task3.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task3.setPosition(Vector2f(SCRWIDTH / 2.0f, 400));
				window.draw(task3);

				Text task4;
				task4.setFont(font);
				task4.setString("View Evaluations");
				task4.setCharacterSize(50);
				task4.setFillColor(Color::Black);
				task4.setStyle(Text::Bold);
				textRect = task4.getLocalBounds();
				task4.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task4.setPosition(Vector2f(SCRWIDTH / 2.0f, 500));
				window.draw(task4);

				Text task5;
				task5.setFont(font);
				task5.setString("Assign Grades");
				task5.setCharacterSize(50);
				task5.setFillColor(Color::Black);
				task5.setStyle(Text::Bold);
				textRect = task5.getLocalBounds();
				task5.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task5.setPosition(Vector2f(SCRWIDTH / 2.0f, 600));
				window.draw(task5);

				Text task6;
				task6.setFont(font);
				task6.setString("Change Password");
				task6.setCharacterSize(50);
				task6.setFillColor(Color::Black);
				task6.setStyle(Text::Bold);
				textRect = task6.getLocalBounds();
				task6.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				task6.setPosition(Vector2f(SCRWIDTH / 2.0f, 690));
				window.draw(task6);

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
					auto translated_pos = window.mapPixelToCoords(mouse_pos);
					Sleep(500);
					if (task1.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task1B = true;
						validCourse = true;
					}
					if (task2.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task2B = true;
						validCourse = true;
					}
					if (task3.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task3B = true;
						validCourse = true;
					}
					if (task4.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task4B = true;
						validCourse = true;
					}
					if (task5.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task5B = true;
						validCourse = true;
					}
					if (task6.getGlobalBounds().contains(translated_pos)) {
						taskSelector = false;
						task6B = true;
						validCourse = true;
					}
				}
			}
			if (task1B == true) {
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if (size != 7) {
										throw size;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									if (teacherUser->courseAlreadyAssigned(courseID) == false) {
										throw false;
									}

									validCourse = false;
									attendOption = true;

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}
						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
				if (attendOption == true) {
					Text newAttend;
					newAttend.setFont(font);
					newAttend.setString("New Attendance");
					newAttend.setCharacterSize(80);
					newAttend.setFillColor(Color::Black);
					newAttend.setStyle(Text::Bold);
					textRect = newAttend.getLocalBounds();
					newAttend.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					newAttend.setPosition(Vector2f(SCRWIDTH / 2.0f, 350));
					window.draw(newAttend);

					Text manageAttend;
					manageAttend.setFont(font);
					manageAttend.setString("Manage Attendance");
					manageAttend.setCharacterSize(80);
					manageAttend.setFillColor(Color::Black);
					manageAttend.setStyle(Text::Bold);
					textRect = manageAttend.getLocalBounds();
					manageAttend.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					manageAttend.setPosition(Vector2f(SCRWIDTH / 2.0f, 550));
					window.draw(manageAttend);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Sleep(500);
						if (newAttend.getGlobalBounds().contains(translated_pos)) {
							teacherUser->newAttendGraphic(window, font, courseID);
							isTeacher = false;
							done = true;
						}
						if (manageAttend.getGlobalBounds().contains(translated_pos)) {

							isTeacher = false;
							done = true;
						}
					}
				}
			}
			if (task2B == true) {
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if (size != 7) {
										throw size;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									if (teacherUser->courseAlreadyAssigned(courseID) == false) {
										throw false;
									}
									window.clear();
									teacherUser->viewAttendGraphic(window, font, courseID);
									Sleep(5000);

									validCourse = false;
									attendOption = true;
									done = true;

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}
						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
			}
			if (task3B == true) {
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if (size != 7) {
										throw size;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									if (teacherUser->courseAlreadyAssigned(courseID) == false) {
										throw false;
									}

									validCourse = false;
									attendOption = true;

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}
						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
				if (attendOption == true) {
					Text newAttend;
					newAttend.setFont(font);
					newAttend.setString("New Marks");
					newAttend.setCharacterSize(80);
					newAttend.setFillColor(Color::Black);
					newAttend.setStyle(Text::Bold);
					textRect = newAttend.getLocalBounds();
					newAttend.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					newAttend.setPosition(Vector2f(SCRWIDTH / 2.0f, 350));
					window.draw(newAttend);

					Text manageAttend;
					manageAttend.setFont(font);
					manageAttend.setString("Manage Marks");
					manageAttend.setCharacterSize(80);
					manageAttend.setFillColor(Color::Black);
					manageAttend.setStyle(Text::Bold);
					textRect = manageAttend.getLocalBounds();
					manageAttend.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					manageAttend.setPosition(Vector2f(SCRWIDTH / 2.0f, 550));
					window.draw(manageAttend);

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
						auto translated_pos = window.mapPixelToCoords(mouse_pos);
						Sleep(500);
						if (newAttend.getGlobalBounds().contains(translated_pos)) {
							teacherUser->newMarksGraphic(window, font, event, courseID);
							isTeacher = false;
							done = true;
						}
						if (manageAttend.getGlobalBounds().contains(translated_pos)) {

							isTeacher = false;
							done = true;
						}
					}
				}
			}
			if (task4B == true) {
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if (size != 7) {
										throw size;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									if (teacherUser->courseAlreadyAssigned(courseID) == false) {
										throw false;
									}
									window.clear();
									teacherUser->viewMarksGraphic(window, font, courseID);
									Sleep(5000);

									validCourse = false;
									attendOption = true;
									done = true;

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}
						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
			}
			if (task5B == true) {
				if (validCourse == true) {
					coursePrintText(window, font, SCRWIDTH, SCRHEIGHT);
					try {
						Sleep(100);
						if (event.type == Event::TextEntered) {
							if (event.text.unicode < 128) {
								if (event.text.unicode == '\r') {
									input[count] = '\0';

									int size = strlen(input);
									if (size != 7) {
										throw size;
									}
									for (int i = 0; i < 7; i++) {
										courseID[i] = input[i];
									}
									courseID[7] = '\0';
									if (teacherUser->courseAlreadyAssigned(courseID) == false) {
										throw false;
									}
									window.clear();
									teacherUser->setGradesGraphic(window, font, event, courseID);
									Sleep(5000);

									validCourse = false;
									attendOption = true;
									done = true;

									for (int i = 0; i < count; i++) {
										input[i] = ' ';
									}
									count = 0;
								}
								else if (event.text.unicode == '\b') {
									if (count > 0) {
										input[count - 1] = ' ';
										count--;
									}
								}
								else {
									input[count] = static_cast<char>(event.text.unicode);
									count++;
								}
							}
						}
					}
					catch (...) {
						invalidPrintText(window, font, SCRWIDTH, SCRHEIGHT);
					}
					printText(window, font, SCRWIDTH, SCRHEIGHT, input);
				}
			}
		}

		if (done == true) {
			char doneText[] = { "Task Done!" };
			printText(window, font, SCRWIDTH, SCRHEIGHT, doneText);

		}

        window.display();
    }

    return 0;
}