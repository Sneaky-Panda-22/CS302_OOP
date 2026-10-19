#include<iostream>
#include<string>
class Student{
    protected:
        int rollNo;
        std::string name;
        void getStudentDetails(){
            std::string s;int a;
            std::cout << "Enter roll no: ";
            std::cin>>a;rollNo=a;
            std::cout << "Enter name: ";
            std::cin>>s;name=s;
        }
};
class TheoryMarks:virtual public Student{
    protected:
        float sub1;
        float sub2;
        void getMarks(void){
            float a,b;std::cout << "Enter marks of 2 subjects: ";
            std::cin>>a>>b;
            sub1=a;sub2=b;
        }
};
class practicalMarks:virtual public Student{
    protected:
        float prac_marks;
        void getMarks(){
            float a;
            std::cout<<"Enter practical marks: ";
            std::cin>>a;prac_marks = a;
        }
};
class Result:public TheoryMarks,public practicalMarks{
    float total;
    float percent;
    public:
        void getInfo(){
            Student::getStudentDetails();
            TheoryMarks::getMarks();
            practicalMarks::getMarks();
            total = sub1+sub2+prac_marks;
            percent = (total/300.0)*100;
        }
        void display(){
            std::cout<<"Roll no: "<<rollNo<<'\n';
            std::cout<<"name: "<<name<<'\n';
            std::cout<<"sub1 marks: "<<sub1<<'\n';
            std::cout<<"sub2 marks: "<<sub2<<'\n';
            std::cout<<"practical marks: "<<prac_marks<<'\n';
            std::cout<<"Total marks: "<<total<<'\n';
            std::cout<<"Percent: "<<percent<<" %"<<'\n';
            bool flag = (sub1>34&&sub2>34&&prac_marks>34);
            if(flag)std::cout << "Result: PASS\n";
            else std::cout << "Result: FAIL\n";
        }
};
int main(){
    Result r;
    r.getInfo();
    r.display();
    return 0;
}