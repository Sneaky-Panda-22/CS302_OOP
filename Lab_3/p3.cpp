#include<iostream>
#include<string>
#include<cctype>
#include<algorithm>
#include<vector>

int main(){
    std::string s;
    std::cout << "Enter a sentence: ";
    std::getline(std::cin, s);

    for(int i=0;i<s.length();i++){
        s[i] = std::tolower(s[i]);
    }

    std::vector<int>freq(26,0);
    for(int i=0;i<s.length();i++){
        if(s[i]!=' '){
            freq[s[i]-'a']++;
        }
    }
    for(int i=0;i<26;i++){
        if(freq[i]!=0){
            std::cout << static_cast<char>(i+'a') << ": " << freq[i] << '\n';
        }
    }
    return 0;
}