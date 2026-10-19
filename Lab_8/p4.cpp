#include <iostream>
#include <string>

using namespace std;

class Product {
protected:
    int id;
    string name;
    double price;
    int stock;

public:
    void acceptDetails() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Stock: ";
        cin >> stock;
    }

    bool purchase(int quantity) {
        if (quantity <= stock) {
            stock -= quantity;
            return true;
        }
        return false;
    }

    void displayRemainingStock() {
        cout << "Remaining stock: " << stock << endl;
    }

    int getStock() { return stock; }
};

class Electronics : public Product {
private:
    int warrantyMonths;
    double installationCharges;

public:
    void acceptDetails() {
        Product::acceptDetails();
        cout << "Enter Warranty (months): ";
        cin >> warrantyMonths;
        cout << "Enter Installation Charges: ";
        cin >> installationCharges;
    }

    double calculateFinalPrice() {
        double discount = price * 0.05;
        double tax = (price - discount) * 0.18;
        return (price - discount) + tax + installationCharges;
    }

    void displayInvoice(int qty) {
        double total = calculateFinalPrice() * qty;
        cout << "\n--- Electronics Invoice ---\n";
        cout << "Product ID: " << id << endl;
        cout << "Product Name: " << name << endl;
        cout << "Warranty: " << warrantyMonths << " months" << endl;
        cout << "Quantity: " << qty << endl;
        cout << "Total Amount: " << total << endl;
    }
};

class Clothing : public Product {
private:
    string size;
    string fabricType;
    int returnDays;

public:
    void acceptDetails() {
        Product::acceptDetails();
        cout << "Enter Size: ";
        cin >> size;
        cin.ignore();
        cout << "Enter Fabric Type: ";
        getline(cin, fabricType);
        cout << "Enter Return Period (days): ";
        cin >> returnDays;
    }

    double calculateFinalPrice() {
        double discount = price * 0.10;
        double tax = (price - discount) * 0.05;
        return (price - discount) + tax;
    }

    void displayInvoice(int qty) {
        double total = calculateFinalPrice() * qty;
        cout << "\n--- Clothing Invoice ---\n";
        cout << "Product ID: " << id << endl;
        cout << "Product Name: " << name << endl;
        cout << "Size: " << size << " | Fabric: " << fabricType << endl;
        cout << "Quantity: " << qty << endl;
        cout << "Total Amount: " << total << endl;
    }
};

int main() {
    int choice;
    int qtyOrdered;

    cout << "1. Electronics\n2. Clothing\nChoose category: ";
    cin >> choice;

    if (choice == 1) {
        Electronics elecObj;
        elecObj.acceptDetails();

        cout << "\nCurrent Stock: " << elecObj.getStock() << endl;
        cout << "Enter quantity to buy: ";
        cin >> qtyOrdered;

        if (elecObj.purchase(qtyOrdered)) {
            cout << "\nPurchase successful!";
            elecObj.displayInvoice(qtyOrdered);
        } else {
            cout << "\nInsufficient stock available." << endl;
        }
        elecObj.displayRemainingStock();

    } else if (choice == 2) {
        Clothing clothObj;
        clothObj.acceptDetails();

        cout << "\nCurrent Stock: " << clothObj.getStock() << endl;
        cout << "Enter quantity to buy: ";
        cin >> qtyOrdered;

        if (clothObj.purchase(qtyOrdered)) {
            cout << "\nPurchase successful!";
            clothObj.displayInvoice(qtyOrdered);
        } else {
            cout << "\nInsufficient stock available." << endl;
        }
        clothObj.displayRemainingStock();

    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
