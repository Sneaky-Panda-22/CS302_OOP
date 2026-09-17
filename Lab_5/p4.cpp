#include<iostream>
class Time{
    int hour;
    int minutes;
    int seconds;
    public:
        void setTime(int,int,int);
        void addTime(Time,Time);//add two time objects
        void addTime(int,int);//add hours and minutes to a time object
        void addTime(int);//add seconds to a time object
        void showTime(void);
};
void Time::setTime(int h,int m,int s){
    hour = h;
    minutes = m;
    seconds = s;
}
void Time::addTime(Time t1, Time t2){
    hour = (t1.hour + t2.hour + (t1.minutes + t2.minutes)/60)%24;
    minutes = (t1.minutes + t2.minutes + (t1.seconds + t2.seconds)/60)%60;
    seconds = (t1.seconds + t2.seconds)%60;
}
void Time::addTime(int h,int m){
    hour = (hour + h + (minutes + m)/60)%24;
    minutes = (minutes + m)%60;
}
void Time::addTime(int s){
    hour = (hour + minutes/60 + (seconds+s)/3600)%24;
    minutes = (minutes + (seconds + s)/60)%60;
    seconds = (seconds + s)%60;
}
void Time::showTime(void){
    std::cout << hour << ":" << minutes << ":" << seconds << '\n';
}
int main(){
    Time time1,time2,time3;
    time1.setTime(2,45,59);
    time2.setTime(1,20,48);
    time3.addTime(time1,time2);
    time1.showTime();
    time2.showTime();
    time3.showTime();

    time3.addTime(1,59);
    time3.showTime();

    time3.addTime(59);
    time3.showTime();
}