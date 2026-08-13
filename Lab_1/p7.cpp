#include <iostream>
using namespace std;
int reverseNumber(int n)
{
    int rev = 0;
    while (n != 0)
    {
        rev = rev * 10 + n % 10;
        n = n / 10;
    }
    return rev;
}
int main()
{
    int n, choice;
    cout << "Enter a number: ";
    cin >> n;
    do
    {
        cout << "\n1. Reverse the number";
        cout << "\n2. Check palindrome";
        cout << "\n3. Count digits";
        cout << "\n4. Sum of digits";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Reverse = " << reverseNumber(n) << endl;
            break;
        case 2:
            if (n == reverseNumber(n))
                cout << "Palindrome Number" << endl;
            else
                cout << "Not a Palindrome Number" << endl;
            break;
        case 3:
        {
            int temp = n, count = 0;
            if (temp == 0)
                count = 1;
            while (temp != 0)
            {
                count++;
                temp = temp / 10;
            }
            cout << "Number of digits = " << count << endl;
            break;
        }
        case 4:
        {
            int temp = n, sum = 0;
            while (temp != 0)
            {
                sum = sum + temp % 10;
                temp = temp / 10;
            }
            cout << "Sum of digits = " << sum << endl;
            break;
        }
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 5);
    return 0;
}