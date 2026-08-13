#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Enter an integer: ";
    cin >> n;
    if (n % 2 == 0)
        cout << "Even" << endl;
    else
        cout << "Odd" << endl;
    if (n > 0)
        cout << "Positive" << endl;
    else if (n < 0)
        cout << "Negative" << endl;
    else
        cout << "Zero" << endl;
    if (n % 5 == 0 && n % 11 == 0)
        cout << "Divisible by both 5 and 11" << endl;
    return 0;
}