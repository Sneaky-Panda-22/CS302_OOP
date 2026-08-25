#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
#include<cmath>

int main(){
    std::cout << "Enter dimensions: ";
    int m,n; std::cin >> m >> n;
    std::vector<std::vector<int>>arr(m,std::vector<int>(n));

    std::vector<std::pair<int,int>> maxm;

    for(int i=0;i<m;i++){
        int curr_max = -1;
        for(int j=0;j<n;j++){
            std::cin >> arr[i][j];
            curr_max = std::max(curr_max, arr[i][j]);
        }
        maxm.push_back({i+1, curr_max});
    }
    std::cout << "Row wise maximums: \n";
    for(auto &it:maxm)std::cout << "Row " << it.first << ": " << it.second << '\n';

    std::sort(maxm.begin(),maxm.end(),[&](const auto a, const auto b){
        return a.second < b.second;
    });

    std::cout << "Sorted maximums: \n";
    for(auto &it:maxm)std::cout << "Row " << it.first << ": " << it.second << '\n';
    return 0;
}