#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<map>

int main(){
    std::cout << "Enter sentence: ";
    std::string s;
    std::getline(std::cin, s);
    std::map<std::string,int> freq;
    int n = s.length();
    std::vector<std::string> v;
    int first = 0, last= 0;
    while(last<n){
        if(s[last]!=' '){
            last++;
        }
        if(last == n-1 || s[last]==' '){
            std::string temp = "";
            for(int i=first; i<last; i++){
                temp+=s[i];
            }
            if(last==n-1)temp+=s[n-1];
            v.push_back(temp);
            first = last+1;
            last++;
        }
    }
    
    for(std::string s:v){
        freq[s]++;
    }
    for(auto &it: freq){
        std::cout << it.first << ": " << it.second << '\n';
    }
    return 0;
}