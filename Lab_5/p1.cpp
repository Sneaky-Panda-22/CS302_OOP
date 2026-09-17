#include<iostream>
class Func{
    public:
        void area(int); // func for square
        void area(int,int); // func for rectangle
        void area(double); // func for circle
};
void Func::area(int side){
    std::cout << "Area of square: " << side*side << '\n';
}
void Func::area(int length,int breadth){
    std::cout << "Area of rectangle: " << length*breadth << '\n';
}
void Func::area(double radius){
    std::cout << "Area of circle: " << static_cast<float>(3.14)*radius*radius << '\n';
}

int main(){
    Func o1;
    o1.area(5);
    o1.area(3,5);
    o1.area(static_cast<double>(1));  
    o1.area(2.0);
    return 0;
}