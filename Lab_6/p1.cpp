#include<iostream>
class Time{
    int hours;
    int minutes;
    int seconds;
    public:
        //default constructor
        Time(){
            hours = 0;
            minutes = 0;
            seconds = 0;
            std::cout << "DEFAULT constructor called\n";
        }
        //paramaterised constructor
        Time(int h,int m,int s){
            hours = h;
            minutes = m;
            seconds = s;
            std::cout << "PARAMETERISED constructor called\n";
        }
        // constructor with def. args
        Time(int h,int m = 0){
            hours = h;
            minutes = m;
            seconds = 0;
            std::cout << "def args. constructor called\n";
        }
        Time(Time& t){
            hours = t.hours;
            minutes = t.minutes;
            seconds = t.seconds;
            std::cout << "COPY constructor called\n";
        }
        void showtime(void){
            std::cout << hours << ":" << minutes << ":" << seconds << '\n';
        }
};
int main(){
    Time t1;
    Time t2(10,20,30);
    Time t3(20);
    t1.showtime();
    t2.showtime();
    t3.showtime();
    return 0;
}