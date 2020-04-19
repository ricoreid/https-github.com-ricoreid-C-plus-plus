#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>


using namespace std;

struct Subjects {
	int math = 0;
	int english = 0;
	int IT = 0;
	int pob = 0;
};

struct Student {
	string Name;
	int ID;
	Subjects subj_taken;
};

void report(Student student) {
	// subjects taken
	int counter = 0;
	int subj_counter = 0;

	if (student.subj_taken.math != 0)
			counter++;

	if (student.subj_taken.english != 0)
		counter++;

	if (student.subj_taken.IT != 0)
		counter++;

	if (student.subj_taken.pob != 0)
		counter++;

	cout << "Number of subjects taken: " << counter << endl;

	// subject passed
	if (student.subj_taken.math > 79)
		subj_counter++;

	if (student.subj_taken.english > 79)
		subj_counter++;

	if (student.subj_taken.IT > 79)
		subj_counter++;

	if (student.subj_taken.pob > 79)
		subj_counter++;

	cout << "Number of subjects passed: " << subj_counter << endl;
}

int main() {
	
	srand(time(NULL));

	Student myStudent;
	myStudent.Name = "Ricardo Reid";
	myStudent.ID = 00001;
	myStudent.subj_taken.math = rand() % 100;
	myStudent.subj_taken.english = rand() % 100;
	myStudent.subj_taken.IT = rand() % 100;
	myStudent.subj_taken.pob = rand() % 100;

	report(myStudent);

	system("PAUSE");
}