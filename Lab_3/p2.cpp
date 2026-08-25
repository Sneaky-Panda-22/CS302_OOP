#include<iostream>
#include<string>
#include<cctype>
#include<algorithm>

int main(){
    std::string s,orig;
    std::cout << "Enter string: ";
    std::cin >> s;
    orig = s;
    std::reverse(s.begin(),s.end());
    std::cout << "Reverse string: " << s << '\n';

    if(orig==s){
        std::cout << "Yes its a palindrome!\n";
    }else{
        std::cout << "Not a palindrome!\n";
    }

    for(int i=0;i<s.length();i++){
        orig[i] = std::tolower(orig[i]);
    }
    std::cout << "Lower case: " << orig << '\n';

    for(int i=0;i<s.length();i++){
        orig[i] = std::toupper(orig[i]);
    }
    std::cout << "Upper case: " << orig << '\n';
    return 0;
}

// can use std::transform as well!
//std::transfor(s.begin(),s.end(),s.begin(),[])