#include<iostream>
#include<deque>

void print_queue(std::deque<int>&deq){
    for(auto &it:deq)std::cout << it << " ";
    std::cout << '\n';
}

int main(){
    int n;
    std::cout << "Enter size: ";
    std::cin >> n;
    std::deque<int>deq;
    std::cout << "Enter elements: ";
    for(int i=0;i<n;i++){
        int x;std::cin>>x;
        deq.push_back(x);
    }
    print_queue(deq);
    deq.pop_back();deq.pop_front();//remove the first and last element;
    deq.push_back(100);deq.push_front(0);//append 0 in begining and 100 at the end
    deq.pop_front();//pop the front element ie. 0
    std::cout << "Front: " << deq.front() << '\n';
    std::cout << "Rear: " << deq.back() << '\n';

    std::cout << "Final deque: ";print_queue(deq);
}