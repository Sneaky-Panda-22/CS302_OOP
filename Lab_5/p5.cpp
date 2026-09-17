#include<iostream>
#include<string>
class ShoppingCart{
    std::string product_name;
    double price;
    int quantity;
    double discount;
    double tax;
    double total_amount;
    //private helper functions
    double computeDiscount(double base_amount)const{
        return base_amount * (discount/100.0);
    }
    double computeTax(double base_amount)const{
        return base_amount * (tax/100.0);
    }
    double finalAmount(double base_amount,double disc_amount,double tax_amount)const{
        return base_amount+tax_amount-disc_amount;
    }
    public:
        void setItem();// provide product name, discount, tax, price, quantity
        void calculateBill();// calculates bill using price and quantity only
        void calculateBill(bool);// for applying discount only. pass true to apply discount
        void calculateBill(bool,bool); // discount and tax. true to apply and false to not apply
        void printBill();
};
void ShoppingCart::setItem(){
    std::string name;
    double p,d,t;//price,discount,tax
    int qty;//quantity
    std::cout << "Enter prodect name: ";
    std::cin >> name;
    product_name = name;
    std::cout << "Enter price of product: ";
    std::cin >> p;
    price = p;
    std::cout << "Enter quantity: ";
    std::cin >> qty;
    quantity = qty;
    std::cout << "Enter Discount: ";
    std::cin >> d;
    discount = d;
    std::cout << "Enter tax: ";
    std::cin >> t;
    tax = t;
}
void ShoppingCart::calculateBill(){
    total_amount = price*quantity;
}
void ShoppingCart::calculateBill(bool disc){
    double base_amount = price*quantity;
    if(!disc){
        total_amount = base_amount;
    }else{
        double disc_amount = computeDiscount(base_amount);
        total_amount = base_amount - disc_amount;
    }
}
void ShoppingCart::calculateBill(bool disc,bool tax){
    double baseAmount = price * quantity;
    double discAmount = disc ? computeDiscount(baseAmount) : 0.0;
    double discountedAmount = baseAmount - discAmount;
    double taxAmount = tax ? computeTax(discountedAmount) : 0.0;

    total_amount = finalAmount(baseAmount, discAmount, taxAmount);
}
void ShoppingCart::printBill(){
    std::cout << "\n--INVOICE--\n";
    std::cout << "Name: " << product_name << '\n';
    std::cout << "Price(per piece): " << price << '\n';
    std::cout << "Quantity: " << quantity << '\n';
    std::cout << "Tax: " << tax << '\n';
    std::cout << "Discount: " << discount << '\n';
    std::cout << "TOTAL AMOUNT: " << total_amount << "\n\n";
}

int main(){
    ShoppingCart shopping_cart;
    shopping_cart.setItem();
    shopping_cart.printBill();
    return 0;
}