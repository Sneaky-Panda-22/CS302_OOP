#include<iostream>
#include<map>
#include<string>
#include<algorithm>

int main(){
    std::map<int,std::string>database;
    int n;std::cout<<"Enter no. of students: ";
    std::cin>>n;std::cout << "Enter (roll,name)\n";
    for(int i=0;i<n;i++){
        int roll;std::string s;
        std::cin>>roll>>s;
        database[roll] = s;
    }
    std::cout << "Student info: \n";
    for(auto &it:database){
        std::cout << it.first << ": " << it.second << '\n';
    }
    std::cout << '\n';
    int search_roll;std::cout<<"Enter roll no: ";
    std::cin >> search_roll;
    auto it = database.find(search_roll);
    if(it==database.end())std::cout << "Not found\n";
    else std::cout << database[search_roll] << '\n';
    std::cout << "Enter roll to update: ";
    std::cin >> search_roll;
    auto it1 = database.find(search_roll);
    if(it1==database.end())std::cout << "Not found\n";
    else{
        std::string name;std::cout<<"Enter name: ";
        std::cin >> name;
        database[search_roll] = name;
        std::cout<<"Updated: " << search_roll << " " << name << '\n';
    }
    int tkey=-1;//target key
    std::cout << "Enter name to delete :";
    std::string name;std::cin>>name;
    for(auto& i:database){
        if(i.second==name){
            tkey = i.first;
            break;
        }
    }
    if(tkey==-1)std::cout << "Not found!\n";
    else database.erase(database.find(tkey));
    for(auto& i:database)std::cout << i.first << ": " << i.second << '\n';
    std::cout << '\n';
    std::cout << "Size: " << database.size() << '\n';
    return 0;
}