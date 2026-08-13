#include<iostream>
#include<vector>
#include<climits>

long long find_sum(std::vector<int>&arr, int size){
    long long sum = 0;
    for(int i=0;i<size;i++){
        sum+=arr[i];
    }
    return sum;
}

int find_minimum(std::vector<int>&arr, int size){
    int mn = INT_MAX;
    for(int i=0;i<size;i++){
        if(arr[i]<mn)mn=arr[i];
    }
    return mn;
}

int find_maximum(std::vector<int>&arr, int size){
    int mx = INT_MIN;
    for(int i=0;i<size;i++){
        if(arr[i]>mx)mx=arr[i];
    }
    return mx;
}

int main(){
    int n;
    std::cout << "Enter size of array: ";
    std::cin >> n;
    std::vector<int> arr(n);
    std::cout << "Enter elements: ";
    for(int i=0;i<n;i++){
        std::cin >> arr[i];
    }

    int max_el = find_maximum(arr,n);
    int min_el = find_minimum(arr,n);

    long long sum = find_sum(arr,n);
    float average = (sum*1.0)/n;

    int even_count = 0, odd_count = 0;
    for(int i=0;i<n;i++){
        if(arr[i]%2==0)even_count++;
        else odd_count++;
    }

    std::cout << "Maximum element: " << max_el << '\n';
    std::cout << "Minimum element: " << min_el << '\n';
    std::cout << "Sum of elements: " << sum << '\n';
    std::cout << "Average: " << average << '\n';
    std::cout << "Even frequency: "<< even_count << '\n';
    std::cout << "Odd frequency: "<< odd_count << '\n';

    return 0;    
}