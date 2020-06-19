#include <iostream>
#include <fstream>
#include "University.h"
#include "Department.h"
#include "Course.h"
#include "Registration.h"
#include "Teacher.h"
#include "It.h"
#include "Student.h"
using namespace std;

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


int main() {
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

	uni.print();
	char temp[] = { "s01801" };
	cout << "Number of poeple in the univeristy: " << objectFinder(temp, stList.getList(), tNumOfSt)->getNumOfPeople() << endl;
	cout << endl << endl;

	char file[] = { "      .txt" };
	char username[7];
	bool cUser = false;

	char* input = new char[50];

	ifstream uFile;
	cout << "Please enter your username: ";
	while (cUser == false) {
		try {
			input = new char[50];
			cin >> input;
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
			}
			else {
				throw false;
			}
			delete[]input;
		}
		catch (int x) {
			cout << "Input size is " << x << "." << endl;
			cout << "Please enter your 6 character ID: ";
		}
		catch (bool) {
			cout << "The username doesn't exist." << endl;
			cout << "Please enter the correct username: ";
		}
	}
	char tempPass[20];
	uFile.getline(tempPass, 20);
	cout << "Please enter your password: ";
	char password[20];
	bool cPass = false;
	while (cPass == false) {
		try {
			cin >> password;
			int size = strlen(password);
			if (size != strlen(tempPass)) {
				throw size;
			}
			for (int i = 0; i < size; i++) {
				if (password[i] != tempPass[i]) {
					throw false;
				}
			}
			cPass = true;
		}
		catch (int) {
			cout << "The Password size doesn't match." << endl;
			cout << "Please enter your password: ";
		}
		catch (bool) {
			cout << "The username doesn't exist." << endl;
			cout << "Please enter the correct username: ";
		}
	}
	
	bool done = false;
	
	else if (username[0] == 'i') {
		cout << "IT Manager LOGGED IN!" << endl << endl;
		ItManager* currentUser = objectFinder(username, itList.getList(), tNumOfIT);
		depID = uni.itDepGetter(currentUser);
		bool done = false;
		while (done == false) {
			cout << "Press 0 to LOG OUT." << endl;
			cout << "Press 1 to create an account for a faculty member." << endl;
			cout << "Press 2 to delete an account for a faculty member." << endl;
			cout << "Press 3 to create an account for a student." << endl;
			cout << "Press 4 to delete an account for a student." << endl;
			cout << "Press 5 to change password for an account." << endl;
			int task = 0;
			cin >> task;
			while ((task < 0) || (task > 5)) {
				cout << "Invalid Input! Please input a valid task number: ";
				cin >> task;
			}
			if (task == 0) {
				done = true;
			}
			else if (task == 1) {
				char userID[7];
				cout << "Please enter the user ID:";
				bool task1 = false;
				while (task1 == false) {
					try {
						input = new char[50];
						cin >> input;
						for (int i = 0; i < 6; i++) {
							userID[i] = input[i];
						}
						userID[6] = '\0';
						int size = strlen(userID);
						if ((size < 6) || (size > 6)) {
							throw size;
						}
						if (userID[0] != 't') {
							throw userID[0];
						}
						for (int i = 0; i < tNumOfTeach; i++) {
							if (strcmp(teachList.getList()[i]->getID(), userID) == 0) {
								throw false;
							}
						}
						delete[]input;
						task1 = true;
					}
					catch (int x) {
						cout << "The size of the user ID you entered is " << x << "." << endl;
						cout << "Please enter the 6 character user ID: ";
					}
					catch (char c) {
						cout << "The username you entered starts with " << c << "." << endl;
						cout << "Please enter a username starting with t: ";
					}
					catch (bool) {
						cout << "The username already exists." << endl;
						cout << "Please enter a new username: ";
					}
				}
				char firstName[20];
				cout << "Please enter the first name of the user:";
				cin >> firstName;
				char lastName[20];
				cout << "Please enter the last name of the user:";
				cin >> lastName;
				uni.newTeacher(depID, userID, firstName, lastName);
			}
			else if (task == 2) {
				char userID[7];
				cout << "Please enter the user ID:";
				bool task2 = false;
				while (task2 == false) {
					try {
						input = new char[50];
						cin >> input;
						for (int i = 0; i < 6; i++) {
							userID[i] = input[i];
						}
						userID[6] = '\0';
						int size = strlen(userID);
						if ((size < 6) || (size > 6)) {
							throw size;
						}
						if (userID[0] != 't') {
							throw userID[0];
						}
						if (uni.depChecker(depID, userID) == false) {
							throw false;
						}
						delete[]input;
						task2 = true;
					}
					catch (int x) {
						cout << "The size of the user ID you entered is " << x << " ." << endl;
						cout << "Please enter the 6 character user ID: ";
					}
					catch (char c) {
						cout << "The username you entered starts with " << c << " ." << endl;
						cout << "Please enter a username starting with t: ";
					}
					catch (bool) {
						cout << "The username doesn't exists in your department." << endl;
						cout << "Please enter a username within your department: ";
					}
				}
				uni.removeTeacher(depID, userID);
			}
			else if (task == 3) {
				char userID[7];
				cout << "Please enter the user ID:";
				bool task3 = false;
				while (task3 == false) {
					try {
						input = new char[50];
						cin >> input;
						for (int i = 0; i < 6; i++) {
							userID[i] = input[i];
						}
						userID[6] = '\0';
						int size = strlen(userID);
						if ((size < 6) || (size > 6)) {
							throw size;
						}
						if (userID[0] != 's') {
							throw userID[0];
						}
						for (int i = 0; i < tNumOfSt; i++) {
							if (strcmp(stList.getList()[i]->getID(), userID) == 0) {
								throw false;
							}
						}
						delete[]input;
						task3 = true;
					}
					catch (int x) {
						cout << "The size of the user ID you entered is " << x << "." << endl;
						cout << "Please enter the 6 character user ID: ";
					}
					catch (char c) {
						cout << "The username you entered starts with " << c << "." << endl;
						cout << "Please enter a username starting with t: ";
					}
					catch (bool) {
						cout << "The username already exists." << endl;
						cout << "Please enter a new username: ";
					}
				}
				char firstName[20];
				cout << "Please enter the first name of the user:";
				cin >> firstName;
				char lastName[20];
				cout << "Please enter the last name of the user:";
				cin >> lastName;
				uni.newStudent(depID, userID, firstName, lastName);
			}
			else if (task == 4) {
				char userID[7];
				cout << "Please enter the user ID:";
				bool task4 = false;
				while (task4 == false) {
					try {
						input = new char[50];
						cin >> input;
						for (int i = 0; i < 6; i++) {
							userID[i] = input[i];
						}
						userID[6] = '\0';
						int size = strlen(userID);
						if ((size < 6) || (size > 6)) {
							throw size;
						}
						if (userID[0] != 's') {
							throw userID[0];
						}
						if (uni.depChecker(depID, userID) == false) {
							throw false;
						}
						delete[]input;
						task4 = true;
					}
					catch (int x) {
						cout << "The size of the user ID you entered is " << x << "." << endl;
						cout << "Please enter the 6 character user ID: ";
					}
					catch (char c) {
						cout << "The username you entered starts with " << c << "." << endl;
						cout << "Please enter a username starting with t: ";
					}
					catch (bool) {
						cout << "The username doesn't exists in your department." << endl;
						cout << "Please enter a username within your department: ";
					}
				}
				uni.removeStudent(depID, userID);
			}
			else if (task == 5) {
				bool task5 = false;
				char userID[7];
				cout << "Please enter the user ID:";
				while (task5 == false) {
					try {
						input = new char[50];
						cin >> input;
						for (int i = 0; i < 6; i++) {
							userID[i] = input[i];
						}
						userID[6] = '\0';
						bool exists;
						int size = strlen(userID);
						if (size != 6) {
							throw size;
						}
						if (userID[0] == 't') {
							exists = uni.depChecker(depID, userID);
						}
						else if (userID[0] == 's') {
							exists = uni.depChecker(depID, userID);
						}
						else {
							throw false;
						}
						if (exists == false) {
							throw false;
						}
						delete[]input;
						task5 = true;
					}
					catch (int x) {
						cout << "The size of the user ID you entered is " << x << "." << endl;
						cout << "Please enter the 6 character user ID: ";
					}
					catch (char*) {
						cout << "You are not the IT Manager of this department." << endl;
						cout << "Please enter a user in your department: ";
					}
					catch (bool) {
						cout << "The user entered doesn't exist in your department." << endl;
						cout << "Please enter a user in your department: ";
					}
				}
				if (userID[0] == 't') {
					Teacher* temp = objectFinder(userID, teachList.getList(), tNumOfTeach);
					temp->passwordReset();
					cout << "Password has been reset!" << endl << endl;
				}
				else {
					Student* temp = objectFinder(userID, stList.getList(), tNumOfSt);
					temp->passwordReset();
					cout << "Password has been reset!" << endl << endl;
				}
				done = true;
			}
		}
	}
	else if (username[0] == 's') {
		TA* currentUser1 = objectFinder(username, TAList, tNumOfTA);
		bool isStudent = false;
		if (currentUser1 == nullptr) {
			isStudent = true;
		}
		else {
			cout << "Press 1 to sign in as student." << endl;
			cout << "Press 2 to sign in as TA." << endl;
			int option;
			cin >> option;
			while ((option != 1) && (option != 2)) {
				cout << endl << "Invalid Input!" << endl;
				cout << "Press 1 to sign in as student." << endl;
				cout << "Press 2 to sign in as TA." << endl;
				cin >> option;
			}
			if (option == 1) {
				isStudent = true;
			}
			else {
				isStudent = false;
			}
		}
		if (isStudent == true) {
			Student* currentUser = objectFinder(username, stList.getList(), tNumOfSt);
			cout << "Student LOGGED IN!" << endl << endl;
			while (done == false) {
				int task = 0;
				cout << "Press 0 to LOG OUT." << endl;
				cout << "Press 1 to register a new course." << endl;
				cout << "Press 2 to unregister a course." << endl;
				cout << "Press 3 to withdraw a course." << endl;
				cout << "Press 4 to view marks of a specific course." << endl;
				cout << "Press 5 to view attendance of a specific course." << endl;
				cout << "Press 6 to change password." << endl;
				cin >> task;
				if (task == 0) {
					done = true;
				}
				else if (task == 1) {
					currentUser->printCourseIDs();
					if (currentUser->getNumOfCourses() != 5) {
						char courseID[8];
						cout << "Please enter the course ID: ";
						bool validCourseID = false;
						while (validCourseID == false) {
							try {
								input = new char[50];
								cin >> input;
								int size = strlen(input);
								if (size != 7) {
									throw size;
								}
								for (int i = 0; i < 7; i++) {
									courseID[i] = input[i];
								}
								courseID[7] = '\0';
								if (currentUser->courseAlreadyRegistered(courseID) == true) {
									throw true;
								}
								char tempID[3];
								tempID[0] = courseID[0];
								tempID[1] = courseID[1];
								tempID[2] = '\0';
								if (uni.getStudentCount(tempID, courseID) >= 50) {
									throw 0.1;
								}
								if (uni.depChecker(tempID, username) == false) {
									throw tempID;
								}
								delete[]input;
								validCourseID = true;
							}
							catch (int x) {
								cout << "The size of the course ID you entered is " << x << endl;
								cout << "Please enter the 7 character course ID: ";
							}
							catch (bool) {
								cout << "The course ID is already registered by you." << endl;
								cout << "Please enter the course ID for the course you are not registered to: ";
							}
							catch (float) {
								cout << "This course already has maximum student capacity." << endl;
								cout << "Please enter the course ID that has capacity: ";
							}
							catch (char* x) {
								cout << "You don't belong in the following department: " << x << endl;
								cout << "Please enter the course ID for your own department: ";
							}
						}
						uni.registerNewCourse(username, courseID);
					}
					else {
						cout << "This student already has maximum workload." << endl;
					}
					done = true;
				}
				else if (task == 2) {
					currentUser->printCourseIDs();
					if (currentUser->getNumOfCourses() > 0) {
						char courseID[8];
						cout << "Please enter the course ID: ";
						bool validCourseID = false;
						while (validCourseID == false) {
							try {
								input = new char[50];
								cin >> input;
								int size = strlen(input);
								if (size != 7) {
									throw size;
								}
								for (int i = 0; i < 7; i++) {
									courseID[i] = input[i];
								}
								courseID[7] = '\0';
								if (currentUser->courseAlreadyRegistered1(courseID) == false) {
									throw false;
								}
								delete[]input;
								validCourseID = true;
							}
							catch (int x) {
								cout << "The size of the course ID you entered is " << x << endl;
								cout << "Please enter the 7 character course ID: ";
							}
							catch (bool) {
								cout << "The course ID isn't registered by you." << endl;
								cout << "Please enter the course ID for the course you are registered to: ";
							}
						}
						currentUser->unregisterCourse(courseID);
					}
					else {
						cout << "This student doesn't have any registered courses." << endl;
					}
					done = true;
				}
				else if (task == 3) {
					currentUser->printCourseIDs();
					if (currentUser->getNumOfCourses() > 0) {
						char courseID[8];
						cout << "Please enter the course ID: ";
						bool validCourseID = false;
						while (validCourseID == false) {
							try {
								input = new char[50];
								cin >> input;
								int size = strlen(input);
								if (size != 7) {
									throw size;
								}
								for (int i = 0; i < 7; i++) {
									courseID[i] = input[i];
								}
								courseID[7] = '\0';
								if (currentUser->courseAlreadyRegistered1(courseID) == false) {
									throw false;
								}
								delete[]input;
								validCourseID = true;
							}
							catch (int x) {
								cout << "The size of the course ID you entered is " << x << endl;
								cout << "Please enter the 7 character course ID: ";
							}
							catch (bool) {
								cout << "The course ID isn't registered by you." << endl;
								cout << "Please enter the course ID for the course you are registered to: ";
							}
						}
						currentUser->withdraw(courseID);
					}
					else {
						cout << "This student doesn't have any registered courses." << endl;
					}
					done = true;
				}
				else if (task == 4) {
					currentUser->printCourseIDs();
					if (currentUser->getNumOfCourses() > 0) {
						char courseID[8];
						cout << "Please enter the course ID: ";
						bool validCourseID = false;
						while (validCourseID == false) {
							try {
								input = new char[50];
								cin >> input;
								int size = strlen(input);
								if (size != 7) {
									throw size;
								}
								for (int i = 0; i < 7; i++) {
									courseID[i] = input[i];
								}
								courseID[7] = '\0';
								if (currentUser->courseAlreadyRegistered1(courseID) == false) {
									throw false;
								}
								delete[]input;
								validCourseID = true;
							}
							catch (int x) {
								cout << "The size of the course ID you entered is " << x << endl;
								cout << "Please enter the 7 character course ID: ";
							}
							catch (bool) {
								cout << "The course ID isn't registered by you." << endl;
								cout << "Please enter the course ID for the course you are registered to: ";
							}
						}
						currentUser->viewMarks(courseID);
					}
					else {
						cout << "This student doesn't have any registered courses." << endl;
					}
					done = true;
				}
				else if (task == 5) {
					currentUser->printCourseIDs();
					if (currentUser->getNumOfCourses() > 0) {
						char courseID[8];
						cout << "Please enter the course ID: ";
						bool validCourseID = false;
						while (validCourseID == false) {
							try {
								input = new char[50];
								cin >> input;
								int size = strlen(input);
								if (size != 7) {
									throw size;
								}
								for (int i = 0; i < 7; i++) {
									courseID[i] = input[i];
								}
								courseID[7] = '\0';
								if (currentUser->courseAlreadyRegistered1(courseID) == false) {
									throw false;
								}
								delete[]input;
								validCourseID = true;
							}
							catch (int x) {
								cout << "The size of the course ID you entered is " << x << endl;
								cout << "Please enter the 7 character course ID: ";
							}
							catch (bool) {
								cout << "The course ID isn't registered by you." << endl;
								cout << "Please enter the course ID for the course you are registered to: ";
							}
						}
						currentUser->viewAttend(courseID);
					}
					else {
						cout << "This student doesn't have any registered courses." << endl;
					}
					done = true;
				}
				else if (task == 6) {
					cout << "Please enter the new password: ";
					char* tempPass = nullptr;
					bool validPass = false;
					while (validPass == false) {
						try {
							input = new char[50];
							cin >> input;
							int size = strlen(input);
							if ((size == 0) || (size > 10)) {
								throw size;
							}
							tempPass = new char[size + 1];
							for (int i = 0; i < size; i++) {
								tempPass[i] = input[i];
							}
							tempPass[size] = '\0';
							validPass = true;
						}
						catch (int x) {
							cout << "The size of the password you entered is " << x << "." << endl;
							cout << "Please enter the password between 1 and 10 characters:";
						}
					}
					currentUser->newPassword(tempPass);
					delete[]tempPass;
					tempPass = nullptr;
					done = true;
				}
			}
		}
		else {
			cout << "Teacher's Assistant LOGGED IN!" << endl << endl;
			while (done == false) {
				int task = 0;
				char* courseID = currentUser1->getTACourse();
				char tempID[3];
				tempID[0] = courseID[0];
				tempID[1] = courseID[1];
				tempID[2] = '\0';
				cout << "Press 0 to LOG OUT." << endl;
				cout << "Press 1 to manage evaluations of students." << endl;
				cout << "Press 2 to view evaluations of the course." << endl;
				cin >> task;
				if (task == 0) {
					done = true;
				}
				else if (task == 1) {
					int option = 0;
					cout << "Press 1 to enter new marks." << endl;
					cout << "Press 2 to manage evaluations." << endl;
					cin >> option;
					while ((option != 1) && (option != 2)) {
						cout << endl;
						cout << "Press 1 to enter new marks." << endl;
						cout << "Press 2 to manage evaluations." << endl;
						cin >> option;
					}
					if (option == 1) {
						uni.newMarks(tempID, courseID);
					}
					else if (option == 2) {
						uni.viewMarks(tempID, courseID);
						uni.appendMarks(tempID, courseID);

					}			
					currentUser1->deleteChar();
					currentUser1 = nullptr;
					done = true;
				}
				else if (task == 2) {
					uni.viewMarks(tempID, courseID);
					currentUser1->deleteChar();
					currentUser1 = nullptr;
					done = true;
				}
			}
		}
	}
	delete[]TAList;
	TAList = nullptr;
	system("pause");
	return 0;
}