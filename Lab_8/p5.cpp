#include<iostream>
#include<string>
class Vehicle{
    protected:
        std::string registrationNumber;
        std::string name;
        double rate;
        void getInfo(){
            std::string a,b;double c;
            std::cout<<"Enter registration number: ";std::cin>>a;registrationNumber=a;
            std::cout<<"Enter name: ";std::cin>>b;name=b;
            std::cout<<"Enter rate per day: ";std::cin>>c;rate=c;
        } 
};
class Car:public Vehicle{
    protected:
        int seatingCapacity;
        std::string transitionType;
        void getInfo(){
            Vehicle::getInfo();
            int a;std::string b;
            std::cout<<"Enter seating capacity: ";std::cin>>a;seatingCapacity=a;
            std::cout<<"Enter transition type: ";std::cin>>b;transitionType=b;
        }
};
class RentalDetails:public Car{
    protected:
        int duration;
        std::string customerID;
        void getInfo(){
            Car::getInfo();
            int a;std::string b;
            std::cout<<"Enter duration: ";std::cin>>a;duration=a;
            std::cout<<"Enter customer ID: ";std::cin>>b;customerID=b;
        }
};
class Insurance{
    protected:
        double insuranceCharges;
        std::string coverageType;
        void getinfo(){
            double a;std::string b;
            std::cout<<"Enter insurance charges: ";std::cin>>a;insuranceCharges=a;
            std::cout<<"Coverage type: ";std::cin>>b;coverageType=b;
        }
};
class RentalBill:public RentalDetails,public Insurance{
    double charge;
    double discount=0.1;
    double penalty = 10000;
    public:
        void makeBill(){
            RentalDetails::getInfo();
            Insurance::getinfo();
            
            int returnDate;std::cout<<"Enter return date: ";std::cin>>returnDate;
            charge = insuranceCharges+rate*duration;
            if(returnDate>duration)charge+=penalty;
            if(duration>100)charge=charge*(1-discount);
            std::cout<<"Total :"<<charge<<'\n';
        }
};
int main(){
    RentalBill bill;
    bill.makeBill();
    return 0;
}