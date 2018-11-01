/* Juan Garcia
 * Homework 1
 * April 3, 2013
 */

#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct StudentRecord
{
    char name[256];
    char ID[10];
    int scores[5];
    double average;
};

StudentRecord* createStudent();
void printStudent(StudentRecord*);

int main()
{
    char choice[10];

    do
    {
        StudentRecord *stud = NULL;
        stud = createStudent();
        if(stud == NULL)
        {
            cout << "Error..." << endl;
            return 0;
        }
        printStudent(stud);
        delete stud;
        stud = NULL;

        cout << "Do you wish to continue? (yes/no): ";
        cin >> choice;

        for(int i = 0; i < 10; i++)
        {
            choice[i] = tolower(choice[i]);
        }

    }while(!strcmp("yes", choice) || !strcmp("y", choice));

    return 0;
}

void printStudent(StudentRecord *stu)
{
   cout << "=====================================================" << endl;
   cout << stu->name << "  Student ID: " << stu->ID << endl;
   cout << fixed << setprecision(2) << setfill('0') << "Exam Scores: ";
   for(int i = 0; i < 5; i++)
   {
       cout << stu->scores[i] << " ";
   }
   cout << "  Average: " << stu->average << endl;
   cout << "=====================================================" << endl;
}

StudentRecord* createStudent()
{
    int total = 0;

    StudentRecord *studs = NULL;
    try
    {
       studs = new StudentRecord;
    }
    catch(bad_alloc)
    {
        studs = NULL;
    }

    cin.ignore();

    cout << "Enter Student's Name: ";
    cin.getline(studs->name, 256);
    cout << "Enter Student's ID: ";
    cin.getline(studs->ID, 10);
    for(int i = 0; i < 5; i++)
    {
        cout << "Enter Student's Exam Score: ";
        cin >> studs->scores[i];

        total += studs->scores[i];
    }

    studs->average = total / 5;

    return studs;
}
