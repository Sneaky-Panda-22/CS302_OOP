#include<iostream>
#include<string>

class Student{
private:
    std::string rollNo;
    int marks1;
    int marks2;
    int marks3;

    double calculate(int m1, int m2){
        return (m1 + m2) / 2.0;
    }

    double calculate(int m1, int m2, int m3){
        return (m1 + m2 + m3) / 3.0;
    }

    char calculateGrade(){
        double avg = calculate(marks1, marks2, marks3);
        if(avg >= 90) return 'A';
        else if(avg >= 75) return 'B';
        else if(avg >= 50) return 'C';
        else return 'F';
    }

public:
    void input(void);
    void display(void);
};

void Student::input(void){
    std::cout << "Enter Student Roll No: ";
    std::string roll;
    std::cin >> roll;
    rollNo = roll;
    
    int m1, m2, m3;
    std::cout << "Enter marks(mark1,mark2,mark3): ";
    std::cin >> m1 >> m2 >> m3;
    marks1 = m1; 
    marks2 = m2;
    marks3 = m3;
}

void Student::display(void){
    std::cout << "Roll No: " << rollNo << std::endl;
    std::cout << "Marks: " << marks1 << ", " << marks2 << ", " << marks3 << std::endl;
    std::cout << "Grade: " << calculateGrade() << std::endl;
}

int main(){
    Student s;
    s.input();
    s.display();
    return 0;
}