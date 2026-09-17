#include<iostream>
#include<string>
class BankAccount{
    int account_no;
    std::string account_holder_name;
    double balance;
    public:
        void set_account_data(int,std::string);//used for initial setup of account
        void get_account_data();//used to fetch info
        void deposit(double);//deposit money
        void deposit(double,double);//deposit money with bonus
        void withdraw(double);//withdraw money
        void calculate_intrest(double);//find daily intrest
        //default intrest rate = 2.5%
};
void BankAccount::set_account_data(int no,std::string name){
    account_no = no;
    account_holder_name = name;
    balance = 0;//new account
}
void BankAccount::get_account_data(){
    std::cout << "Account number: " << account_no << "\nHolder name: " << account_holder_name << "\nBalance: " << balance << "\n\n";
}
void BankAccount::deposit(double amount){
    balance+=amount;
    std::cout << "Deposited " << amount << '\n';
    std::cout << "Updated balance: " << balance << "\n\n";
}
void BankAccount::deposit(double amount, double bonus){
    balance+=(amount+bonus);
    std::cout << "Deposited amount: " << amount+bonus << '\n';
    std::cout << "Updated balance: " << balance << "\n\n";
}
void BankAccount::withdraw(double amount){
    if(balance < amount){
        std::cout << "NOT enough balance!\n\n";
    }else{
        balance-=amount;
        std::cout << "Withdrawn amount: " << amount << '\n';
        std::cout << "Updated balance: " << balance << "\n\n";
    }
}
void BankAccount::calculate_intrest(double intrest=static_cast<double>(0.025)){
    double intrest_amount = balance * (intrest);
    std::cout << "Intrest: " << intrest_amount << "\n\n";
}

int main(){
    BankAccount account;
    account.set_account_data(100,"USER");
    account.get_account_data();
    account.withdraw(10);//cant withdraw! balance = 0
    account.deposit(100);
    account.deposit(100,100);
    account.get_account_data();
    account.calculate_intrest();//uses 2.5%
    account.calculate_intrest(0.03);//uses 3%
    return 0;
}