#include<iostream>
#include<vector>
#include<set>

int main(){
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    std::vector<int>a(n),ans;
    std::cout << "Enter elements: ";
    for(int i=0;i<n;i++) std::cin >> a[i];
    std::set<int> s;
    for(int i=0;i<n;i++){
        if(s.find(a[i])==s.end()){
            ans.push_back(a[i]);
            s.insert(a[i]);
        }
    }
    for(int v:ans) std::cout << v << " ";
    std::cout << '\n';
    return 0;
}
