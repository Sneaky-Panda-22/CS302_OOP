#include<iostream>
#include<stack>
#include<algorithm>
int main(){
    int n;
    std::cout << "Enter no of elements: ";
    std::cin>>n;
    std::stack<int> my_stack;
    std::cout << "Enter elements: ";
    for(int i=0;i<n;i++){
        int x;
        std::cin>>x;
        my_stack.push(x);
    }
    while(!my_stack.empty()){
        std::cout << my_stack.top() << '\n';
        my_stack.pop();
    }
}