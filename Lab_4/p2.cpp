#include<iostream>
#include<list>
#include<iterator>
#include<algorithm>

void print_list(std::list<int>& lst){
    for(auto &it:lst) std::cout << it << " ";
    std::cout << '\n';
}

int main(){
    int n;
    std::cout << "Enter size: ";
    std::cin >> n;
    std::list<int> my_list;
    std::cout << "Enter elements: ";
    for(int i=0; i<n; i++){
        int x; std::cin >> x;
        my_list.push_back(x);
    }
    print_list(my_list);
    my_list.push_front(0); //append 0 in beginning
    my_list.push_front(-1); //append -1 in beginning
    my_list.push_back(100); //append 100 in end
    std::cout << "First element: " << my_list.front() << '\n'; //output -1
    std::cout << "Last element: " << my_list.back() << '\n'; //output 100
    my_list.pop_back(); //pops 100 from end
    my_list.pop_front(); //pops -1 from front
    std::cout << "New list after push and pop: "; print_list(my_list);
    std::cout << "New size: " << my_list.size() << '\n'; //output size as n+1
    
    auto it = my_list.begin();
    std::advance(it, 2); //moves it to the 2nd index element
    it = my_list.erase(it); //removes element and updates it to next valid position

    std::cout << "Enter element to insert at pos: ";
    int val, target;
    std::cin >> val;
    my_list.insert(it, val); //inserts val right before the updated iterator
    std::cout << "Updated list: "; print_list(my_list);

    std::cout << "Enter element to remove :";
    std::cin >> target;
    auto it1 = std::find(my_list.begin(), my_list.end(), target); //iterator for target
    if(it1 == my_list.end()) std::cout << "Target not found!\n";
    else {
        std::cout << "Removed " << target << '\n';
        my_list.erase(it1); //deletes the target element from list
    }
    my_list.sort(); //sorts the list in ascending order
    std::cout << "Sorted list: "; print_list(my_list);
    
    my_list.sort([](const auto& a, const auto &b){
        return a > b; //sorting rule for descending order
    });
    std::cout << "Reverse: "; print_list(my_list);
    my_list.unique(); //removes adjacent duplicate elements
    std::cout << "final list: "; print_list(my_list);
    return 0;
}
