#include<iostream>
class Vehicle{
public:
    virtual void calculateRent() = 0;
    virtual void type() = 0;
};
class Car:public Vehicle{
private:
    int days;
    double cost_per_day = 1000;
public:
    Car(int a):days(a){}
    void calculateRent(){
        double rent;
        rent = cost_per_day * days;
        std::cout<<"Rent for "<<days<<" days: "<<rent<<'\n';
    }
    void type(){
        std::cout<<"Class Car\n";
    }
};
class Bike:public Vehicle{
private:
    int days;
    double cost_per_day = 500;
public:
    Bike(int a):days(a){}
    void calculateRent(){
        double rent;
        rent = cost_per_day * days;
        std::cout<<"Rent for "<<days<<" days: "<<rent<<'\n';
    }
    void type(){
        std::cout<<"Class Bike\n";
    }
};
int main(){
    Car c(10);
    Bike b(6);
    Vehicle* ptr = &c;
    ptr->type();
    ptr->calculateRent();

    std::cout<<'\n';

    ptr = &b;
    ptr->type();
    ptr->calculateRent();
}