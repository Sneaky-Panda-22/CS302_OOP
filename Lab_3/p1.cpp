#include<iostream>
#include<vector>
#include<numeric>

int main(){
    int n;
    std::cout << "Enter size: ";
    std::cin >> n;
    std::vector<int>a(n);
    std::cout << "Enter Elements: \n";

    for(int i=0;i<n;i++)std::cin >> a[i];

    long long sum = std::accumulate(a.begin(),a.end(),0);
    std::cout << "Sum: " << sum << '\n';

    double avg = static_cast<double>(sum)/n;
    std::cout << "Average: " << avg << '\n';
    int largest_num = *(std::max_element(a.begin(),a.end()));
    std::cout << "Maximum element: " << largest_num << '\n';

    int smallest_num = *(std::min_element(a.begin(),a.end()));
    std::cout << "Minimum element: " << smallest_num << '\n';
    return 0;
}