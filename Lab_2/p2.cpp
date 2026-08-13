#include<iostream>
#include<vector>
#include<algorithm>

void consecutive_longest(std::vector<int>&arr,int n){
    int curr = 1;
    int longest = 1;
    int end_idx = 0;
    for(int i=1;i<n;i++){
        if(arr[i]-arr[i-1]==1){
            curr++;
        }else{
            longest = std::max(longest, curr);
            curr = 1;
            end_idx = i-1;
        }
    }
    if(curr>longest){
        longest = curr;
        end_idx = n-1;
    }
    int start_idx = end_idx - longest + 1;
    std::cout << "Longest Sequence: ";
    for(int i=start_idx;i<=end_idx;i++){
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
    std::cout << "Length: " << longest << '\n';
}

int main(){
    int n;
    std::cout << "Enter size: ";
    std::cin >> n;
    std::vector<int>arr(n);
    std::cout << "Elements: "<<'\n';
    for(int i=0;i<n;i++){
        std::cin >> arr[i];
    }

    consecutive_longest(arr,n);

    return 0;
}