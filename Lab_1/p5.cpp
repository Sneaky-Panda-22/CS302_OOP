#include <iostream>
using namespace std;
int factorial(int n)
{
    int fact = 1;
    for (int i = 1; i <= n; i++)
        fact = fact * i;
    return fact;
}
int main()
{
    int n, temp, rev = 0, sum = 0;
    int digits = 0;
    cout << "Enter an integer: ";
    cin >> n;
    // Prime Number
    bool prime = true;
    if (n < 2)
        prime = false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            prime = false;
            break;
        }
    }
    if (prime)
        cout << "Prime Number" << endl;
    // Number of digits
    temp = n;
    if (temp == 0)
        digits = 1;
    while (temp != 0)
    {
        digits++;
        temp = temp / 10;
    }
    // Armstrong Number
    temp = n;
    int armstrong = 0;
    while (temp != 0)
    {
        int digit = temp % 10;
        int power = 1;
        for (int i = 1; i <= digits; i++)
            power = power * digit;
        armstrong = armstrong + power;
        temp = temp / 10;
    }
    if (armstrong == n)
        cout << "Armstrong Number" << endl;
    // Palindrome Number
    temp = n;
    while (temp != 0)
    {
        rev = rev * 10 + temp % 10;
        temp = temp / 10;
    }
    if (rev == n)
        cout << "Palindrome Number" << endl;
    // Perfect Number
    for (int i = 1; i <= n / 2; i++)
    {
        if (n % i == 0)
            sum = sum + i;
    }
    if (sum == n && n > 0)
        cout << "Perfect Number" << endl;
    // Strong Number
    temp = n;
    int strong = 0;
    while (temp != 0)
    {
        strong = strong + factorial(temp % 10);
        temp = temp / 10;
    }
    if (strong == n)
        cout << "Strong Number" << endl;
    return 0;
}
