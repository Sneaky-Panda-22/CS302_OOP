#include<iostream>
class Complex{
    double real;
    double img;
    public:
        Complex(int r={},int i={}):real(r),img(i){}
        Complex(Complex& obj){real=obj.real;img=obj.img;}
        friend void operator-(Complex& obj){obj.real=-obj.real;obj.img=-obj.img;}
        friend Complex operator+(Complex& c1,Complex& c2){
            Complex temp(c1.real+c2.real,c1.img+c2.img);
            return temp;
        }
        void dispaly(){
            std::cout << real << " " << img << "j" << '\n';
        }
};

int main(){
    Complex c1(10,20),c2(-1,-2);
    std::cout << "C1:";c1.dispaly();
    std::cout << "C2:";c2.dispaly();
    -c2;
    std::cout << "\n-C2:";c2.dispaly();
    Complex c3;
    c3 = c1+c2;
    std::cout << "\nC3=C1+C2:";c3.dispaly();
    return 0;
}