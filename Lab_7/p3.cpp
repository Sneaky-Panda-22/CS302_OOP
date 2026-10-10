#include<iostream>
class Student{
    int rollNo;
    int marks;
public:
    Student(int r=0,int m=0):rollNo(r),marks(m){};
    void display(void){
        std::cout << "Roll no: " << rollNo << "\nMarks: " << marks << '\n';
    }
    Student operator++(){
        marks++;
        return *this;
    }
    Student operator++(int){
        Student temp = *this;
        marks++;
        return temp;
    }
};
int main(){
    int r,m;
    std::cout << "Enter rollno,marks: ";
    std::cin >> r >> m;
    Student s1(r,m);
    Student s2=s1++;
    s1.display();
    s2.display();
    Student s3=++s1;
    s1.display();
    s3.display();
}
