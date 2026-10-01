#include<iostream>
class Rectangle{
    int length;
    int breadth;
    public:
        Rectangle(){
            length = 0;
            breadth = 0;
            std::cout << "Default Constructor called\n";
        }
        Rectangle(int l,int b){
            length = l;
            breadth = b;
            std::cout << "Parameterised Constructor called\n";
        }
        Rectangle(int l){
            length = l;
            breadth = l;
            std::cout << "Square constructor called\n";
        }
        Rectangle(Rectangle& r){
            length = r.length;
            breadth = r.breadth;
            std::cout << "Copy constructor called\n";
        }
        void print_area(void){
            long long area = length*breadth;
            std::cout << area << '\n';
        }
        void print_perimeter(void){
            long long p = 2*(length+breadth);
            std::cout << p << '\n';
        }
};
int main(){
    Rectangle r1;
    r1.print_area();r1.print_perimeter();
    Rectangle r2(4,2);
    r2.print_area();r2.print_perimeter();
    Rectangle r3(10);
    r3.print_area();r3.print_perimeter();
    Rectangle r4(r2);
    r4.print_area();r4.print_perimeter();
    return 0;
}