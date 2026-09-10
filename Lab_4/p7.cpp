#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

// LAB REPORT ANSWERS:
//
// Q1: Why can't we use sort(s.begin(), s.end()) on a stack?
// std::sort needs "random access iterators" so it can jump straight to any element 
// using indexes. A stack is strictly LIFO (Last-In, First-Out). It doesn't even 
// have .begin() or .end() because you are only allowed to see the top element.
//
// Q2: Which STL containers work with std::sort?
// std::vector and std::deque have the right iterators for it.
//
// Q3: Comparing both ways:
// Task 1 (Vector + sort) is much faster, running in O(N log N) time, but we have to 
// dump everything into a vector first. Task 2 (Min-stack) takes O(N^2) time because 
// of the nested loops shuffling things back and forth, but it uses pure stacks.

// Helper to print the stack. Passed by value so it doesn't empty the main stack.
void printStack(std::stack<int> s) {
    if (s.empty()) {
        std::cout << "Stack is empty.\n";
        return;
    }
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << "\n";
}

// Task 1: Dump to vector, sort it, then push back to a stack.
std::stack<int> sortWithSTL(std::stack<int> input) {
    std::vector<int> buffer;
    buffer.reserve(input.size()); 

    while (!input.empty()) {
        buffer.push_back(input.top());
        input.pop();
    }

    // Sort descending so the smallest value gets pushed last and stays on top
    std::sort(buffer.begin(), buffer.end(), std::greater<int>());

    std::stack<int> sortedStack;
    for (int num : buffer) {
        sortedStack.push(num);
    }

    return sortedStack;
}

// Task 2: Sort using a temporary stack that acts like a min-stack.
std::stack<int> sortWithMinStack(std::stack<int> input) {
    std::stack<int> minStack;

    while (!input.empty()) {
        int current = input.top();
        input.pop();

        // Clear out smaller elements from minStack to keep the lowest values on top
        while (!minStack.empty() && minStack.top() < current) {
            input.push(minStack.top());
            minStack.pop();
        }
        minStack.push(current);
    }

    return minStack;
}

int main() {
    int totalElements;
    std::cout << "Enter the number of elements (N): ";
    if (!(std::cin >> totalElements) || totalElements <= 0) {
        std::cerr << "Error: Invalid stack size.\n";
        return 1;
    }

    std::stack<int> originalStack;
    std::cout << "Enter " << totalElements << " integers: ";
    for (int i = 0; i < totalElements; ++i) {
        int val;
        std::cin >> val;
        originalStack.push(val);
    }

    std::cout << "\nOriginal Stack:\n";
    printStack(originalStack);

    std::cout << "\n--- Task 1: Using sort() ---\n";
    std::stack<int> res1 = sortWithSTL(originalStack);
    std::cout << "Sorted Output:\n";
    printStack(res1);

    std::cout << "\n--- Task 2: Using Min Stack Logic ---\n";
    std::stack<int> res2 = sortWithMinStack(originalStack);
    std::cout << "Sorted Output:\n";
    printStack(res2);

    return 0;
}
