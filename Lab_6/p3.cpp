#include<iostream>
#include<cstring>

class DynamicString{
    char* str;
    public:
        // default constructor
        DynamicString(){
            str = new char[1];
            str[0] = '\0';
        }
        // parameterised constructor
        DynamicString(const char* s){
            if(s==nullptr){
                str = new char[1];
                str[0] = '\0';
            }else{
                str = new char[std::strlen(s)+1];
                std::strcpy(str,s);
            }
        }
        // copy constructor
        DynamicString(const DynamicString& source){
            str = new char[std::strlen(source.str)+1];
            std::strcpy(str,source.str);
        }
        // destructor
        ~DynamicString(){delete[] str;}

        // concatenation function for dynamic strings
        DynamicString concatenate(const DynamicString& s){
            int total_len = std::strlen(str) + std::strlen(s.str);
            char* temp = new char[total_len+1];
            std::strcpy(temp,str);
            std::strcat(temp,s.str);
            DynamicString result(temp);
            delete[] temp;
            return result;
        }
        void display(void){
            std::cout << str << '\n';
        }
};

int main(){
    DynamicString s1 = DynamicString("Hello ");
    DynamicString s2("World");
    DynamicString s3 = s1.concatenate(s2);
    std::cout << "String 1: ";s1.display();
    std::cout << "String 2: ";s2.display();
    std::cout << "Concatenated strings: ";s3.display();
    std::cout << '\n';
    DynamicString s4("OOT "),s5("Programming "),s6("Lab");
    DynamicString s7 = (s4.concatenate(s5)).concatenate(s6);
    std::cout << "String 1: ";s4.display();
    std::cout << "String 2: ";s5.display();
    std::cout << "String 3: ";s6.display();
    std::cout << "Concatenated strings: ";s7.display();
    return 0;
}