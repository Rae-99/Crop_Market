#include <iostream>
#include <string>
using namespace std;

class sell {
public:
    int p, quantity, p50 = 0, p100 = 0, pLast = 0;
    char grade;

    void product_info() {
        cout << "Enter product number: ";
        cin >> p;

        cout << "Enter product grade : \n A: High grade \n B: Average grade \n C: Low grade\n";
        cin >> grade;

        cout << "Enter quantity you want to sell (in kg): ";
        cin >> quantity;
    }

    void price_info() {
        // display price of each range from file system
        cout << "Enter your price for quantity up to 50 kg (in rupees per kg): ";
        cin >> p50;

        if (quantity > 50) {
            cout << "Enter your price for quantity 50-100 kg (in rupees per kg): ";
            cin >> p100;
        }

        if (quantity > 100) {
            cout << "Enter your price for quantity above 100 kg (in rupees per kg): ";
            cin >> pLast;
        }
    }

    void run() {
        int ch;

        do {
            product_info();
            price_info();

            cout << "1. Confirm\n2. Add more products\n0. Exit\n";
            cin >> ch;

        } while (ch == 2);

        if (ch == 0) {
            cout << "Your changes will not be saved.\n";
            cout << "Press 0 to continue.\n";
            return;
        }

        if (ch == 1) {
            cout << "Your changes are saved.\n";
            // add data to file system
        }
    }
};

int main() {
    sell obj;
    obj.run();
    return 0;
}