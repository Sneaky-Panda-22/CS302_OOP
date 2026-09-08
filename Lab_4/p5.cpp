//std::stack<T, Container> Performance & Mechanics

// 1. std::deque (Default)
//    - Layout: Chunks of fixed-size arrays (non-contiguous overall).
//    - Time Complexity: 
//      • Push / Pop: Amortized O(1), Strict O(1) page allocation bounds.
//      • Top: O(1).
//    - Space Complexity: O(N) with minor chunk-map overhead.
//    - Verdict: Best overall balance. No massive array copying on growth.


// 2. std::vector
//    - Layout: Single contiguous array.
//    - Time Complexity:
//      • Push: Amortized O(1) but Worst-Case O(N) when array doubles & copies.
//      • Pop / Top: Strict O(1).
//    - Space Complexity: O(N), but can waste up to 50% extra capacity.
//    - Verdict: Fastest for data iterations & cache hits. Use if you can 
//               pre-allocate or if memory density is critical.


// 3. std::list
//    - Layout: Doubly linked list (scattered heap nodes).
//    - Time Complexity:
//      • Push / Pop / Top: Strict O(1) always (no amortization, no spikes).
//      • Allocation: Every push hits the OS heap allocator.
//    - Space Complexity: O(N), but high overhead (2 pointers per element).
//    - Verdict: Destroys CPU cache. Use only if you need strict real-time
//               latency guarantees (no resize spikes) or track node pointers.

#include <iostream>
#include <stack>
#include <vector>
#include <deque>
#include <list>

int main() {
    std::stack<int, std::vector<int>> v_stack;
    std::stack<int, std::deque<int>> d_stack;
    std::stack<int, std::list<int>> l_stack;
    int items[] = {10, 20, 30, 40};

    for(int x : items) {
        v_stack.push(x);
        d_stack.push(x);
        l_stack.push(x);
    }

    std::cout << "Vector top: " << v_stack.top() << " size: " << v_stack.size() << "\n";
    std::cout << "Deque top: " << d_stack.top() << " size: " << d_stack.size() << "\n";
    std::cout << "List top: " << l_stack.top() << " size: " << l_stack.size() << "\n";

    v_stack.pop();
    d_stack.pop();
    l_stack.pop();
    
    std::cout << "After pop:\n";
    std::cout << "Vector top: " << v_stack.top() << " size: " << v_stack.size() << "\n";
    std::cout << "Deque top: " << d_stack.top() << " size: " << d_stack.size() << "\n";
    std::cout << "List top: " << l_stack.top() << " size: " << l_stack.size() << "\n";
    return 0;
}
