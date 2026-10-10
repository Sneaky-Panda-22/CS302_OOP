#include<iostream>
const int size = 5;
class Vector{
    int a[size];
    public:
        Vector();
        Vector(int *arr);
        Vector(Vector&);
        friend Vector operator+(Vector&,Vector&);
        friend Vector operator-(Vector&,Vector&);
        friend void operator*(int,Vector&);
        friend void operator*(Vector&,int);
        friend bool operator==(Vector&,Vector&);
        int operator[](int k);
        friend std::istream& operator>>(std::istream&,Vector&);
        friend std::ostream& operator<<(std::ostream&,Vector&);
};
Vector::Vector(){
    for(int i=0;i<size;i++)a[i] = 0;
}
Vector::Vector(int *arr){
    for(int i=0;i<size;i++)a[i]=arr[i];
}
Vector::Vector(Vector& obj){
    for(int i=0;i<size;i++)a[i]=obj.a[i];
}
Vector operator+(Vector& v1,Vector& v2){
    Vector sum;
    for(int i=0;i<size;i++)sum.a[i]=(v1.a[i]+v2.a[i]);
    return sum;
}
Vector operator-(Vector& v1,Vector& v2){
    Vector diff;
    for(int i=0;i<size;i++)diff.a[i]=(v1.a[i]-v2.a[i]);
    return diff;
}
void operator*(int c,Vector& v){
    for(int i=0;i<size;i++)v.a[i] = c*v.a[i];
}
void operator*(Vector& v,int c){
    for(int i=0;i<size;i++)v.a[i] = c*v.a[i];
}
bool operator==(Vector& v1,Vector& v2){
    for(int i=0;i<size;i++){if(v1.a[i]!=v2.a[i])return false;}
    return true;
}
int Vector::operator[](int k){return a[k];}
std::istream& operator>>(std::istream& din,Vector& v){
    for(int i=0;i<size;i++)din>>v.a[i];
    return (din);
}
std::ostream& operator<<(std::ostream& dout,Vector& v){
    for(int i=0;i<size;i++)dout << v.a[i];
    return (dout);
}

int main(){
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {10,20,30,40,50};
    int arr3[] = {100,100,100,100,100};
    Vector v1(arr1);
    Vector v2(arr2);
    Vector v3(arr3);
    std::cout << "Vector 1: ";
    for(int i=0;i<size;i++)std::cout << v1[i] << " ";
    std::cout << '\n';
    std::cout << "Vector 2: ";
    for(int i=0;i<size;i++)std::cout << v2[i] << " ";
    std::cout << '\n';
    std::cout << "Vector 3: ";
    for(int i=0;i<size;i++)std::cout << v3[i] << " ";
    std::cout << '\n';

    int k = 10;
    v1*k;
    std::cout << "\nAfter multiplying Vector 1 with 10:\nVector 1: ";
    for(int i=0;i<size;i++)std::cout << v1[i] << " ";
    std::cout << '\n';

    Vector v4;
    v4 = v1+v2;
    std::cout << "\nVector 4(sum of v1,v2): ";
    for(int i=0;i<size;i++)std::cout << v4[i] << " ";
    std::cout << '\n';

    if(v1==v2)std::cout << "Vector1 == Vector2\n";

    return 0;
}