#include<iostream>
#include<set>
#include<algorithm>

int main(){
    std::set<int>my_set;
    std::multiset<int>my_multi_set;
    int n;std::cout << "Enter n: ";std::cin>>n;
    std::cout << "Enter numbers: ";
    for(int i=0;i<n;i++){
        int x;std::cin>>x;
        my_set.insert(x);
        my_multi_set.insert(x);
    }
    std::cout << "Set elements: \n";
    for(auto &it:my_set)std::cout << it << " ";
    std::cout << '\n';
    std::cout << "MultiSet elements: \n";
    for(auto &it:my_multi_set)std::cout << it << " ";
    std::cout << '\n';
    std::cout << "Size of set: " << my_set.size() << '\n';
    std::cout << "MultiSet size: " << my_multi_set.size() << '\n';
    return 0;
}