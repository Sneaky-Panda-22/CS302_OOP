#include <iostream>
using namespace std;
int main()
{
    int marks[5], total = 0;
    float percentage;
    char grade;
    bool pass = true;
    cout << "Enter marks of five subjects:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cin >> marks[i];
        total = total + marks[i];
        if (marks[i] < 35)
            pass = false;
    }
    percentage = total / 5.0;
    if (percentage >= 90)
        grade = 'A';
    else if (percentage >= 80)
        grade = 'B';
    else if (percentage >= 70)
        grade = 'C';
    else if (percentage >= 60)
        grade = 'D';
    else
        grade = 'F';
    cout << "Total Marks = " << total << endl;
    cout << "Percentage = " << percentage << "%" << endl;
    cout << "Grade = " << grade << endl;
    if (pass)
        cout << "Result = Passed" << endl;
    else
        cout << "Result = Failed" << endl;
    return 0;
}