#include<iostream>

class CurrentAccount;

class SavingsAccount{
    int balance;
    int getSavingsBalance()const{
        return balance;
    }
    public:
        void setInitialBalance(int x){
            balance = x;
        }
        void showBalance(void) const {
            std::cout << "Savings Account Balance: " << balance << '\n';
        }
        int getBalance(){
            return getSavingsBalance();
        }
        friend void compareBalance(const CurrentAccount&, const SavingsAccount&);
};

class CurrentAccount{
    int balance;
    int getCurrentBalance()const{
        return balance;
    }
    public:
        void setInitialBalance(int x){
            balance = x;
        }
        void showBalance(void) const {
            std::cout << "Current Account Balance: " << balance << '\n';
        }
        int getBalance(){
            return getCurrentBalance();
        }
        friend void compareBalance(const CurrentAccount&, const SavingsAccount&);
};

void compareBalance(const CurrentAccount& c, const SavingsAccount& s){
    s.showBalance();
    c.showBalance();
    int savingsBalance = s.balance;
    int currentBalance = c.balance;
    if(savingsBalance>currentBalance){
        std::cout << "The Savings Account has higher balance\n";
        std::cout << "Difference: " << savingsBalance - currentBalance << '\n';
    }else if(savingsBalance<currentBalance){
        std::cout << "The Current Account has higher balance\n";
        std::cout << "Difference: " << currentBalance - savingsBalance << '\n';
    }else{
        std::cout << "Both account have equal balance\n";
        std::cout << "Difference: 0\n";
    }
}

int main(){
    CurrentAccount ca;
    SavingsAccount sa;

    ca.setInitialBalance(100000);
    sa.setInitialBalance(2000);

    compareBalance(ca,sa);
    return 0;
}
