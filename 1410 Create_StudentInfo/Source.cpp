/**
Write a C++ program that calculate student’s GPA after calculating courses final grade.
The program should allow the user to create student, add up to 5 courses,
and add assignments/homework/exams/quizzes for each course.
Use the following grading criteria:
1.	Assignments: 40%
2.	Exams: 30%
3.	Homework: 20%
4.	Quizzes: 10%
You may only add COSC courses. Each course may have 2 exams or 1 exam.
Each course may have maximum of 4 assignments and minimum of 2 assignments.
Each course may have maximum of 5 homework and at least 2 homework.
Each course may have exactly 2 quizzes.
You also need to display the final letter grade after calculating the
GPA using University of Houston grading system!
A=4, A-=3.6, B+=3.33, B=3, B-=2.6, C+=2.33, C=2, C-=1.6, D+=1.33, D=1, D-=.6, F = 0
94-100: A, 90-93: A-, 87-89: B+, 83-86: B, 80-83: B-, 77-79: C+,
73-76: C, 70-72: C-, 67-69: D+, 60-66: D, 0-59: F
********************************************************************************************** ONLY DO THIS PART**********************************************************************************************************************************
Needed student info:
1.	PeopleSoft ID
2.	Letter representing F for Female and M for Male
3.	Full Name
4.	Date of Birth in the following format: MM/DD/YYYY  (ASSUME THE USER ENTER INTEGERS ALWAYS)

*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Defining variables for Student
const int _PEOPLE_SOFT_LENGTH = 7; //setting the length of the peoplesoft ID
const string _PEOPLE_SOFT_MESSAGE = "PeopleSoftID";
const string _FIRST_NAME_MESSAGE = "First Name";
const string _LAST_NAME_MESSAGE = "Last Name";
const string _GENDER_MESSAGE = "Gender";
const string _DOB_MESSAGE = "Date Of Birth";
const string _COURSES_MESSAGE = "Courses";
const string _ASSIGNMENT_MESSAGE = "Assignments";
const string _EXAMS_MESSAGE = "Exams";
const string _HOMEWORK_MESSAGE = "Homework";
const string _QUIZ_MESSAGE = "Quizzes";

string _peopleSoftID;
string _firstName;
string _lastName;
string _courses;
char gender;
int month;
int day;
int year;
int assignment;
int exam;
int homework;
int quizzes;
int countCourse;			//add up to 5 courses
int countAssignments;		//min 2, max 4
int countExams;				//min 1, max 2
int countHomework;			//min 2, max 5
int countQuiz;				//exactly 2

char select;
int aTotal;
int eTotal;
int hTotal;
int qTotal;
int cGrade;
float letterGP;
float TGPA;
float total = 0.0;
fstream transcript;

//Define method that reads peopleSoft ID from user and validate it
string getPeopleSoftIDFromUser();
bool isStringNumeric(string name, string message);
bool isStringSize(string name, int length, string message);
bool isPeopleSoftIDValid(string peopleSoftID);

//Define method that reads _firstName from user and validate it
string getFirstnameFromUser();
bool isStringAlphabetic(string name, string message);
bool isfirstNameValid(string firstName);

//Define method that reads _lastName from user and validate it
string getLastnameFromUser();
//bool isStringAlphabetic(string name, string message); used from first name
bool isLastnameValid(string lastName);

//Define method that reads gender from user and validate it
char getGenderFromUser();
bool genderChoices(char name, string messsage);
bool isGenderValid(char Gender);

//Define method that reads DOB from user and validate it
void getDOBFromUser();
bool isValidDate(int month, int day, int year, string message);
bool isDOBValid(int month, int day, int year);

//Define method that reads _courses from user and validate it
string getCoursesFromUser();
bool isCOSCValid(string course, string message);
bool isCourseValid(string course);

//Define method that reads assignment from user and validate it
int getAssignmentsFromUser();
bool isGradeValid(int grade, string message);
bool isAssignmentValid(int assignment);

//Define method that reads exams from user and validate it
int getExamsFromUser();
//bool isGradeValid(int grade, string message); used for finding grade range
bool isExamValid(int exam);

// Define method that reads exams from user and validate it
int getHomeworkFromUser();
//bool isGradeValid(int grade, string message); used for finding grade range
bool isHomeworkValid(int homework);

// Define method that reads exams from user and validate it
int getQuizFromUser();
//bool isGradeValid(int grade, string message); used for finding grade range
bool isQuizValid(int quiz);

bool assignmentCont(char select);
bool examCont(char select);
bool homeworkCont(char select);
bool quizCont(char select);
bool courseCont(char select);

int asssignmentTotal(int assignmentGrade);
int examTotal(int examGrade);
int homeworkTotal(int homeworkGrade);
int quizTotal(int quizGrade);
int courseGrade(int aTotal, int eTotal, int hTotal, int qTotal, int countAssignments, int countExams, int countHomework, int countQuiz);
float letterGrade(int cGrade);
float GPA(float letterGP, int countCourse);

//Define method that reads _
int main() {

	transcript.open("Transcript.txt", ios::out);
	//giving an error if the file fails or has an error
	if (transcript.fail()) {
		cerr << "Error opening file...";
		exit(1);
	}

	//Initialize
	_peopleSoftID = "";
	_firstName = "";
	_lastName = "";
	gender = ' ';
	_courses = "";
	month = 1;
	day = 1;
	year = 1000;
	assignment = 0;
	exam = 0;
	homework = 0;
	quizzes = 0;
	select = ' ';
	countCourse = 0;			//max 5
	TGPA = 0;
	letterGP = 0.0;

	/*Assign variables to the value that the method return to it*/
	_peopleSoftID = getPeopleSoftIDFromUser();
	_firstName = getFirstnameFromUser();
	_lastName = getLastnameFromUser();
	gender = getGenderFromUser();
	getDOBFromUser();
	transcript << "PEOPLESOFT ID\tLAST NAME\tFIRST NAME\tGENDER\tDOB\n";
	transcript << _peopleSoftID << "\t\t\t" << _lastName << "\t\t" << _firstName << "\t\t" << gender << "\t\t"
		<< month << "/" << day << "/" << year << endl << endl;
	transcript << "COURSES\t\t\tCOURSE GRADE\n";
	do 
	{
		
		countAssignments = 0;		//min 2, max 4
		countExams = 0;				//min 1, max 2
		countHomework = 0;			//min 2, max 5
		countQuiz = 0;				//exactly 2

		aTotal = 0;
		eTotal = 0;
		hTotal = 0;
		qTotal = 0;
		cGrade = 0;

		_courses = getCoursesFromUser();
		assignment = getAssignmentsFromUser();
		exam = getExamsFromUser();
		homework = getHomeworkFromUser();
		quizzes = getQuizFromUser();

		courseGrade(aTotal, eTotal, hTotal, qTotal, countAssignments, countExams, countHomework, countQuiz);
		letterGrade(cGrade);
		GPA(letterGP, countCourse);
		transcript << _courses << "\t\t\t\t" << cGrade << endl << endl;

		//cout << endl << letterGP << endl << total << endl << TGPA << endl << countCourse << endl;

	} while (courseCont(select) == true);

	transcript << "Your GPA for this semester is: " << TGPA << "/4.0" << endl << endl;

	system("pause");
	return 0;
}

string getPeopleSoftIDFromUser()
{
	//Define & Initialize
	string peopleSoftID = "";
	bool isNumeric = true;

	//Keep asking the user to enter peopleSoft ID until he/she gets right
	do
	{
		cout << "\n\tPlease enter your PeopleSoft ID (MUST BE AT LEAST 7 DIGITS!): ";
		cin >> peopleSoftID;

		/* Stay in the loop as long as PeopleSoft ID is NOT
		valid.
		Pay attention to !
		(!isPeopleSoftIDValid(peopleSoftID)) is equivalent to
		(isPeopleSoftIDValid(peopleSoftID) == false)*/
	} while (!isPeopleSoftIDValid(peopleSoftID));

	//We return valid peopleSoft ID!
	return peopleSoftID;
}
string getFirstnameFromUser() {
	//Define & Initialize
	string firstName = "";
	//bool isNumeric = true;

	//Keep asking the user to enter First Name until he/she gets right
	do
	{
		cout << "\n\tPlease enter your First Name: ";
		cin >> firstName;

		/* Stay in the loop as long as First Name is NOT
		valid.
		Pay attention to !
		(!isfirstNameValid(firstName)) is equivalent to
		(isfirstNameValid(firstName) == false)*/
	} while (!isfirstNameValid(firstName));

	//We return valid First Name!
	return firstName;
}
string getLastnameFromUser() {
	//Define & Initialize
	string lastName = "";
	//bool isNumeric = true;

	//Keep asking the user to enter Last Name until he/she gets right
	do
	{
		cout << "\n\tPlease enter your Last Name: ";
		cin >> lastName;

		/* Stay in the loop as long as Last Name is NOT
		valid.
		Pay attention to !
		(!isLastnameValid(lastName)) is equivalent to
		(isLastnameValid(lastname) == false)*/
	} while (!isLastnameValid(lastName));

	//We return valid Last Name!
	return lastName;
}
char getGenderFromUser()
{
	//Define & Initialize
	char gender = ' ';
	bool isValid = true;
	//Keep asking the user to enter Gender until he/she gets right
	do
	{
		cout << "\n\tPlease enter your Gender ((M)ale, (F)emale, (O)ther): ";
		cin >> gender;

		/* Stay in the loop as long as Gender is NOT
		valid.
		Pay attention to !
		(!isGenderValid(gender)) is equivalent to
		(isGenderValid(gender) == false)*/
	} while (!isGenderValid(gender));

	//We return valid Gender!
	return gender;
}
void getDOBFromUser()
{
	//Define & Initialize
	//int month = 0;
	//int day = 0;
	//int year = 0;
	bool isDateValid = true;
	//Keep asking the user to enter DOB until he/she gets right
	do
	{
		cout << "\n\tPlease enter your Date of Birth (MM/DD/YYYY). VALID INTEGERS ONLY!\n ";
		cout << "\n\tPlease enter the Month (MM): ";
		cin >> month;
		cout << "\n\tPlease enter the Day (DD): ";
		cin >> day;
		cout << "\n\tPlease enter the Year (YYYY): ";
		cin >> year;

		/* Stay in the loop as long as DOB is NOT valid.
		Pay attention to !
		(!isDOBValid(month,day,year)) is equivalent to
		(isDOBValid(month,day,year) == false)*/
	} while (!isDOBValid(month,day,year));

	//cout << "\n\t" << month << "/" << day << "/" << year;
}
string getCoursesFromUser()
{
	//Define & Initialize
	string course = "";

	//Keep asking the user to enter a course until he/she gets right
	do
	{
		cout << "\n\tPlease enter your COSC course with no spaces!! (EX:12COSC): ";
		cin >> course;

		/* Stay in the loop as long as course is NOT valid.
		Pay attention to !
		(!isCOSCValid(course)) is equivalent to
		(isCOSCValid(course) == false)*/
	} while (!isCourseValid(course));
	countCourse++;
	//We return valid course!
	return course;
}
int getAssignmentsFromUser()
{
	//Define & Initialize
	int assignmentG = 0;

	//Keep asking the user to enter a assignment until he/she gets right
	do
	{
		cout << "\n\tPlease enter your Assignment Grade(Max 4, Min 2) from 0 to 100: ";
		cin >> assignmentG;

		/* Stay in the loop as long as assignment is NOT valid.
		Pay attention to !
		(!isAssignmentValid(assignmentG)) is equivalent to
		(isAssignmentValid(assignmentG) == false)*/
	} while (!isAssignmentValid(assignmentG));
	asssignmentTotal(assignmentG);
	countAssignments++;

	assignmentCont(select);
	//We return valid grade!
	return assignmentG;
}
int getExamsFromUser()
{
	//Define & Initialize
	int examG = 0;

	//Keep asking the user to enter an exam until he/she gets right
	do
	{
		cout << "\n\tPlease enter your Exam Grade(Max 2) from 0 to 100: ";
		cin >> examG;

		/* Stay in the loop as long as exam is NOT valid.
		Pay attention to !
		(!isExamValid(examG)) is equivalent to
		(isExamValid(examG) == false)*/
	} while (!isExamValid(examG));
	examTotal(examG);
	countExams++;

	examCont(select);
	//We return valid grade!
	return examG;
}
int getHomeworkFromUser()
{
	//Define & Initialize
	int homeworkG = 0;

	//Keep asking the user to enter a homework until he/she gets right
	do
	{
		cout << "\n\tPlease enter your Homework Grade(Max 5, Min 2) from 0 to 100: ";
		cin >> homeworkG;

		/* Stay in the loop as long as homework is NOT valid.
		Pay attention to !
		(!isHomeworkValid(homeworkG)) is equivalent to
		(isHomeworkValid(homeworkG) == false)*/
	} while (!isHomeworkValid(homeworkG));
	homeworkTotal(homeworkG);
	countHomework++;

	homeworkCont(select);
	//We return valid grade!
	return homeworkG;
}
int getQuizFromUser()
{
	//Define & Initialize
	int quizG = 0;

	//Keep asking the user to enter a quiz until he/she gets right
	do
	{
		cout << "\n\tPlease enter your Quiz Grade(Exactly 2) from 0 to 100: ";
		cin >> quizG;

		/* Stay in the loop as long as quiz is NOT valid.
		Pay attention to !
		(!isQuizValid(quizG)) is equivalent to
		(isQuizValid(quizG) == false)*/
	} while (!isQuizValid(quizG));
	quizTotal(quizG);
	countQuiz++;

	quizCont(select);
	//We return valid grade!
	return quizG;
}
/*General method to check if name of type string is numeric
the 2nd parameter (message) is to personalize the error message*/
bool isStringNumeric(string name, string message)
{
	/* Check if string is numeric or NOT*/
	for (int iteration = 0; iteration < name.length(); iteration++)
	{
		/*We assume that the string is numeric until we
		find character that is NOT numeric, then we quit the
		loop by using the return statement and dispaly error
		message*/
		if (!isdigit(name[iteration]))
		{
			cout << "\n\t***Error: " << message << " must be ONLY NUMERIC!\n";

			return false;
		}
	}

	/*If we did NOT find invalid character in the loop above,
	the we say that the string is numeric by return true*/
	return true;
}
/*General method to check if name of type string is alphabetic
the 2nd parameter (message) is to personalize the error message*/
bool isStringAlphabetic(string name, string message)
{
	/* Check if string is alphabetic or NOT*/
	for (int iteration = 0; iteration < name.length(); iteration++)
	{
		/*We assume that the string is alphabetic until we
		find character that is NOT alphabetic, then we quit the
		loop by using the return statement and dispaly error
		message*/
		if (!isalpha(name[iteration]))
		{
			cout << "\n\t***Error: " << message << " must be ONLY AlPHABETIC!\n";

			return false;
		}
	}

	/*If we did NOT find invalid character in the loop above,
	the we say that the string is alphabetic by return true*/
	return true;
}
/*General method that checks if the string length is the desired
length (variable length) and 3rd parameter (message) is used to
personalize the error message if needed*/
bool isStringSize(string name, int length, string message)
{
	//if length is NOT correct, display error
	if (name.length() != length)
	{
		cout << "\n\t*** Error: " << message << " must be " << length << " digits!\n";
		return false;
	}

	//if length is correct, then we assume it is correct by returning true
	return true;
}
/*General method to check if name of type char is valid
the 2nd parameter (message) is to personalize the error message*/
bool genderChoices(char name, string message)
{
	//if character is correct, then we assume it is correct by returning true
	if (name == 'M' || name == 'F' || name == 'f' || name == 'm' || name == 'O' || name == 'O')
	{
		return true;
	}

	//if character is NOT correct, display error
	cout << "\n\t*** Error: " << message << " must be a VALID OPTION (M/F/O)!\n";
	return false;
}
/*General method to check if the DOB is valid
the 2nd parameter (message) is to personalize the error message*/
bool isValidDate(int month, int day, int year, string message)
{
	if (month > 0 && month < 13 && day > 0 && day < 31 && year > 1900 && year < 2019)
	{
		return true;
	}

	//if character is NOT correct, display error
	cout << "\n\t*** Error: " << message << " must be a VALID DATE!\n";
	return false;
}
/*General method to check if the COSC course is valid
the 2nd parameter (message) is to personalize the error message*/
bool isCOSCValid(string course, string message)
{
	string found = "COSC";
	int pos;

	/* Check if string is a COSC course or NOT*/
	for (int iteration = 0;(pos=course.find(found)) != -1; iteration++)
	{
		return true;
	}

	/*If we did NOT find the COSC cource in the loop above,
	the we say that the cource entered is not VALID by returning false*/
	cout << "\n\t*** Error: " << message << " must be a VALID COSC course!\n";
	return false;
}
/*General method to check if the grade is valid
the 2nd parameter (message) is to personalize the error message*/
bool isGradeValid(int grade, string message)
{
	if (grade >= 0 && grade <= 100)
	{
		return true;
	}

	//if grade is NOT correct, display error
	cout << "\n\t*** Error: " << message << " must be a VALID GRADE RANGE FROM 0 TO 100!\n";
	return false;
}

/*Method that calls all the necessary validations for
PeopleSoft ID and decide if PeopleSoft ID is valid or NOT*/
bool isPeopleSoftIDValid(string peopleSoftID)
{
	bool isLengthSeven = isStringSize(peopleSoftID, _PEOPLE_SOFT_LENGTH, _PEOPLE_SOFT_MESSAGE);
	bool isNumeric = isStringNumeric(peopleSoftID, _PEOPLE_SOFT_MESSAGE);

	return (isLengthSeven && isNumeric);
}
bool isfirstNameValid(string firstName)
{
	bool isAlphabetic = isStringAlphabetic(firstName, _FIRST_NAME_MESSAGE);

	return (isAlphabetic);
}
bool isLastnameValid(string lastName)
{
	bool isAlphabetic = isStringAlphabetic(lastName, _LAST_NAME_MESSAGE);

	return (isAlphabetic);
}
bool isGenderValid(char Gender)
{
	bool genderValid = genderChoices(Gender, _GENDER_MESSAGE);

	return (genderValid);
}
bool isDOBValid(int month, int day, int year)
{
	bool DOBValid = isValidDate(month, day, year, _DOB_MESSAGE);

	return (DOBValid);
}
bool isCourseValid(string course)
{
	bool courseValid = isCOSCValid(course, _COURSES_MESSAGE);

	return (courseValid);
}
bool isAssignmentValid(int grade)
{
	bool assignmentValid = isGradeValid(grade, _ASSIGNMENT_MESSAGE);

	return (assignmentValid);
}
bool isExamValid(int grade)
{
	bool examValid = isGradeValid(grade, _EXAMS_MESSAGE);

	return(examValid);
}
bool isHomeworkValid(int grade)
{
	bool homeworkValid = isGradeValid(grade, _HOMEWORK_MESSAGE);
	
	return (homeworkValid);
}
bool isQuizValid(int grade)
{
	bool quizValid = isGradeValid(grade, _QUIZ_MESSAGE);
	
	return (quizValid);
}

bool assignmentCont(char select)
{
	if (countAssignments < 2)
	{
		getAssignmentsFromUser();
	}
	else if (countAssignments == 4) 
	{
		cout << "\n\tTHE MAX NUM OF ASSIGNMENTS IS 4 PER COURSE!!\n";
		return false;
	}
	else if (countAssignments >= 2) 
	{
		cout << "\nWould you like to continue (y or n)? ";
		cin >> select;
		if (select == 'y')
		{
			getAssignmentsFromUser();
			return true;
		}

		else
		{
			return false;
		}
	}
}

bool examCont(char select)
{
	if (countExams == 2)
	{
		cout << "\n\tTHE MAX NUM OF EXAMS IS 2 PER COURSE!!\n";
		return false;
	}

	cout << "\nWould you like to continue (y or n)? ";
	cin >> select;

	if (select == 'y')
	{
		getExamsFromUser();
		return true;
	}
	else
	{
		return false;
	}
}

bool homeworkCont(char select)
{
	if (countHomework < 2)
	{
		getHomeworkFromUser();
	}
	else if (countHomework == 5) 
	{
		cout << "\n\tTHE MAX NUM OF HOMEWORK IS 5 PER COURSE!!\n";
		return false;
	}
	else if (countHomework >= 2) 
	{
		cout << "Would you like to continue (y or n)? ";
		cin >> select;

		if (select == 'y') 
		{
			getHomeworkFromUser();
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool quizCont(char select)
{
	if (countQuiz == 2)
	{
		cout << "\n\tTHE MAX NUM OF QUIZZES IS 2 PER COURSE!!\n";
		return false;
	}
	else if (countQuiz < 2) 
	{
		getQuizFromUser();
	}
	else
	{
		return false;
	}
}

bool courseCont(char select)
{
	if (countCourse == 5)
	{
		cout << "\n\tTHE MAX NUM OF COURSES IS 5!!\n";
		return false;
	}
	else if (countCourse < 5)
	{
		cout << "Would you like to continue (y or n)? ";
		cin >> select;

		if (select == 'y')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int asssignmentTotal(int assignmentG)
{
	aTotal += assignmentG;
	//cout << aTotal << endl;
	return aTotal;

}

int examTotal(int examG)
{
	eTotal += examG;
	//cout << eTotal << endl;
	return eTotal;


}

int homeworkTotal(int homeworkG)
{
	hTotal += homeworkG;
	//cout << hTotal << endl;
	return hTotal;

}

int quizTotal(int quizG)
{
	qTotal += quizG;
	//cout << qTotal << endl;
	return qTotal;
}

int courseGrade(int aTotal, int eTotal, int hTotal, int qTotal, int countAssignments, int countExams, int countHomework, int countQuiz)
{
	cGrade = ((aTotal / countAssignments)*(.4)) + ((eTotal / countExams)*(.3)) + ((hTotal / countHomework)*(.2)) + ((qTotal / countQuiz)*(.1));

	return cGrade;
}

float letterGrade(int cGrade)
{
	if (cGrade > 94 && cGrade <= 100) {
		cout << "\t\n Your letter grade is A\n";
		letterGP = 4;
		return letterGP;
	}
	else if (cGrade > 90 && cGrade <= 93) {
		cout << "\t\n Your letter grade is A-\n";
		letterGP = 3.6;
		return letterGP;
	}
	else if (cGrade > 87 && cGrade <= 89) {
		cout << "\t\n Your letter grade is B+\n";
		letterGP = 3.33;
		return letterGP;
	}
	else if (cGrade > 83 && cGrade <= 86) {
		cout << "\t\n Your letter grade is B\n";
		letterGP = 3;
		return letterGP;
	}
	else if (cGrade > 80 && cGrade <= 82) {
		cout << "\t\n Your letter grade is B-\n";
		letterGP = 2.6;
		return letterGP;
	}
	else if (cGrade > 77 && cGrade <= 79) {
		cout << "\t\n Your letter grade is C+\n";
		letterGP = 2.33;
		return letterGP;
	}
	else if (cGrade > 73 && cGrade <= 76) {
		cout << "\t\n Your letter grade is C\n";
		letterGP = 2;
		return letterGP;
	}
	else if (cGrade > 70 && cGrade <= 72) {
		cout << "\t\n Your letter grade is C-\n";
		letterGP = 1.6;
		return letterGP;
	}
	else if (cGrade > 67 && cGrade <= 69) {
		cout << "\t\n Your letter grade is D+\n";
		letterGP = 1.33;
		return letterGP;
	}
	else if (cGrade > 60 && cGrade <= 66) {
		cout << "\t\n Your letter grade is D\n";
		letterGP = 1;
		return letterGP;
	}
	else if (cGrade < 60) {
		cout << "\t\n Your letter grade is F\n";
		letterGP = 0;
		return letterGP;
	}
}

float GPA(float letterGP, int countCourse)
{
	total += letterGP;
	TGPA = (total / countCourse);
	return TGPA;
}

