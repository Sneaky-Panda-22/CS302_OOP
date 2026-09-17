#include<iostream>
#include<string>
class Display{
    public:
        void show(int a){ //show integer
            std::cout << a << '\n';
        } 
        void show(double a){//show floating pt value
            std::cout << a << '\n';
        }
        void show(std::string s){ //show a string
            std::cout << s << '\n';
        }
        void show(int a,int b){//show two int ans sum
            std::cout << a << " " << b << "\nSum : " << a+b << '\n';
        }
};

int main(){
    Display display;
    display.show(5);//outputs 5
    display.show(3.14);//outputs 3.14
    display.show("Hello world! this is my string!");//outputs string
    display.show(2,2);// outputs 2 2 sum : 4
    return 0;
}