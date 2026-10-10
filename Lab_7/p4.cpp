#include<iostream>
class Time{
    int hr;
    int min;
    public:
        Time(int h={},int m={}):hr(h),min(m){};
        void show(void){std::cout << hr << " hours & " << min << "mins\n";}
        int gethr(void){return hr;}
        int getmin(void){return min;}
};
class Minutes{
    int min;
    public:
        Minutes(int m={}):min(m){};
        Minutes(Time& t){
            min = t.gethr()*60 + t.getmin();
        }
        void show(void){std::cout << min << "mins\n";}
};
int main(){
    Time t1(5,20);
    std::cout << "T1: ";t1.show();
    Minutes m1(100);
    std::cout << "M1: ";m1.show();
    Minutes new_time(t1);
    std::cout << "T1 converted to mins: ";new_time.show();
    return 0;
}