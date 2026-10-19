#include<iostream>
#include<string>

class BankAccount {
protected:
    int accountNumber;
    std::string name;
    float balance;
    BankAccount(int acno = 1, std::string n = "def", float amount = 0.0)
        : accountNumber(acno), name(n), balance(amount) {}
    void withdraw_amount(float amount) {
        if (balance >= amount) {
            balance -= amount;
            std::cout << "withdrawn " << amount << " Rs.\n";
        } else {
            std::cout << "Insufficient balance\n";
        }
    }
    void deposit_amount(float amount) {
        balance += amount;
        std::cout << "Deposited " << amount << " Rs.\n";
    }
    void update_balance(float amount) { balance = amount; }
    void display_details(void) {
        std::cout << "Account Number: " << accountNumber << '\n';
        std::cout << "Holder Name: " << name << '\n';
        std::cout << "Balance: " << balance << '\n';
    }
};
class SavingsAccount : public BankAccount {
private:
    float annual_intrest_rate = 0.25;
    float minimumAmount = 5000.0;

public:
    SavingsAccount(int acno, std::string n, float a) : BankAccount(acno, n, a) {
        while (balance < minimumAmount) {
            std::cout << "Minimum account balance must be atleast 5000!\nEnter balance: ";
            std::cin >> balance; 
            std::cout << '\n';
        }
    }
    void deposit_money(float amount) { BankAccount::deposit_amount(amount); }
    void withdraw_money(float amount) {
        if (balance - amount < minimumAmount) {
            std::cout << "can't withdraw! minimum account balance:5000Rs\n";
        } else {
            BankAccount::withdraw_amount(amount);
        }
    }
    void calculate_intrest(void) {
        float intrest = balance * annual_intrest_rate;
        std::cout << "Intrest: " << intrest << '\n';
    }
    void display(void) { BankAccount::display_details(); }
};

int main() {
    SavingsAccount s(1234, "Person_1", 4000);
    s.display();
    s.deposit_money(1);
    s.withdraw_money(10000);
    s.withdraw_money(100);
    s.calculate_intrest();
    s.display();
    return 0;
}
