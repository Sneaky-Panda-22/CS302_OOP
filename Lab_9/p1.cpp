#include<iostream>
class Shape{
    public:
        virtual void area(double a,double b=1.0) = 0;
        virtual void type() = 0;
};
class Rectangle:public Shape{
    public:
        void area(double a,double b) override {
            double ans = a*b;
            std::cout<<"Area of Rectangle: "<<ans<<'\n';
        }
        void type() override {
            std::cout << "class Rectangle\n";
        }
};
class Circle:public Shape{
    public:
        void area(double a,double b = 1.0) override {
            double ans = a*a;
            std::cout<<"Area of Circle: "<<ans<<'\n';
        }
        void type() override {
            std::cout << "class Circle\n";
        }
};
int main(){
    Rectangle r;
    Circle c;
    Shape* ptr = &r;
    ptr->type();
    ptr->area(10,12.5);

    std::cout<<'\n';

    ptr = &c;
    ptr->type();
    ptr->area(1.5);
}