#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int totalOrders = 0;
double dailySales = 0.0;
double dailyDiscount = 0.0;

void customerMenu(); // basically customer menu and apa cust nmpk
void staffMenu(); // staff menu and apa staff nmpk
double calculateUnitPrice(int serviceChoice, int paperChoice, int colourChoice); // ni untuk calculate unit price
double calculateDiscount(double unitPrice, int qty); // ni untuk calculate discount (kita buat discount 10% kalau qty 50 ke atas)
double calculateTotalPrice(double unitPrice, int qty, double discount); // ni untuk calculate total price after discount 
void dailySalesReport(); // nak generate daily sales report

int main() {
    int choice = 0;

    do {
        cout << "====================================================================" << endl;
        cout << "                  FAST2PRINT DESIGN & PRINT SHOP" << endl;
        cout << "           \"Your Ideas, Printed Right - Come Buy With Us!\"" << endl;
        cout << "--------------------------------------------------------------------" << endl;
        cout << "   Services : Banners | Flyers | Posters | Business Cards" << endl;
        cout << "  Perks    : Quality Prints | Affordable Rates | 10% OFF (50+ pcs)" << endl;
        cout << "====================================================================" << endl;
        cout << "MAIN MENU" << endl;
        cout << "1. Customer" << endl;
        cout << "2. Staff" << endl;
        cout << "3. Exit" << endl;
        cout << "CHOOSE YOUR NUMBER: ";
        cin >> choice;

        if (choice == 1) {
            customerMenu();
        }
        else if (choice == 2) {
            staffMenu();
        }
        else if (choice == 3) {
            cout << "Thank you for using Fast2Print!" << endl;
        }
        else {
            cout << "Invalid choice! Please choose 1, 2, or 3." << endl;
        }
    } while (choice != 3);

    return 0;
}

void customerMenu() {
    int choice = 0;
	string serviceName = "None"; //ni biar none sbb nnt user nak pilih order baru, kalau tak nanti dia boleh view summary, modify, confirm, payment, receipt walaupun takde order
    string paperName = "None";
    string colourName = "None";
    int svc = 0; //ni service choice tau
    int ppr = 0; //ni paper choice
    int clr = 0; //ni colour choice
    int qty = 0; //quantity
    double unitPrice = 0.0;
    double discount = 0.0;
    double totalPrice = 0.0;
	double changeDue = 0.0; //utk org calculate berapa baki dia dapat kalau bayar cash
	string payMethod = "None"; //utk simpan payment method, sama ada cash or qr
	bool hasOrder = false; //nak check dah ada order ke belum, kalau belum takleh view summary, modify, confirm, payment, receipt
	bool isPaid = false; //nak check dah bayar ke belum, kalau belum takleh view receipt

    do {
        cout << "\n==========================================" << endl;
        cout << "              CUSTOMER MENU               " << endl;
        cout << "==========================================" << endl;
        cout << "1. Create New Order" << endl;
        cout << "2. View Order Summary" << endl;
        cout << "3. Modify Order" << endl;
        cout << "4. Confirm Order" << endl;
        cout << "5. Payment" << endl;
        cout << "6. View Receipt" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "CHOOSE YOUR NUMBER: ";
        cin >> choice;

        if (choice == 1) {
            do {
                cout << "\n1. Poster (RM 15.00)" << endl; //standardisekan semua format harga utk display as (RM xx.xx)
                cout << "2. Flyer (RM 2.00)" << endl;
                cout << "3. Banner (RM 35.00)" << endl;
                cout << "4. Business Card (RM 1.50)" << endl;
                cout << "Choose service (1-4): ";
                cin >> svc;
                if (svc < 1 || svc > 4) {
                    cout << "Invalid choice! Enter 1 to 4." << endl;
                }
            } while (svc < 1 || svc > 4);

            do {
                cout << "\n1. Standard (+RM 0.00)" << endl;
                cout << "2. Glossy (+RM 2.00)" << endl;
                cout << "Choose paper (1-2): ";
                cin >> ppr;
                if (ppr < 1 || ppr > 2) {
                    cout << "Invalid choice! Enter 1 or 2." << endl;
                }
            } while (ppr < 1 || ppr > 2);

            do {
                cout << "\n1. Black & White (+RM 0.00)" << endl;
                cout << "2. Colour (+RM 3.00)" << endl;
                cout << "Choose colour (1-2): ";
                cin >> clr;
                if (clr < 1 || clr > 2) {
                    cout << "Invalid choice! Enter 1 or 2." << endl;
                }
            } while (clr < 1 || clr > 2);

            do {
                cout << "\nEnter quantity (1 - 1000): ";
                cin >> qty;
                if (qty < 1 || qty > 1000) {
                    cout << "Invalid quantity! Enter 1 to 1000." << endl;
                }
            } while (qty < 1 || qty > 1000);

            if (svc == 1) serviceName = "Poster";
            else if (svc == 2) serviceName = "Flyer";
            else if (svc == 3) serviceName = "Banner";
            else serviceName = "Business Card";

            if (ppr == 1) paperName = "Standard";
            else paperName = "Glossy";

            if (clr == 1) colourName = "Black & White";
            else colourName = "Colour";

            unitPrice = calculateUnitPrice(svc, ppr, clr);
            discount = calculateDiscount(unitPrice, qty);
            totalPrice = calculateTotalPrice(unitPrice, qty, discount);
            hasOrder = true;
            isPaid = false;

            cout << fixed << setprecision(2);
            cout << "\nOrder created! Total: RM " << totalPrice << endl;
        }
        else if (choice == 2) {
            if (!hasOrder) {
                cout << "No order yet. Please choose 1 first." << endl;
            }
            else {
                cout << fixed << setprecision(2);
                cout << "\n--- ORDER SUMMARY ---" << endl;
                cout << "Service  : " << serviceName << endl;
                cout << "Paper    : " << paperName << endl;
                cout << "Colour   : " << colourName << endl;
                cout << "Quantity : " << qty << endl;
                cout << "Discount : RM " << discount << endl;
                cout << "Total    : RM " << totalPrice << endl;
            }
        }
        else if (choice == 3) {
            cout << "Modify Order will be added in M5." << endl;
        }
        else if (choice == 4) {
            if (!hasOrder) {
                cout << "No order to confirm." << endl;
            }
            else {
                cout << "Order confirmed! Please proceed to Payment (5)." << endl;
            }
        }
        else if (choice == 5) {
            if (!hasOrder) {
                cout << "No order to pay! Create an order first." << endl;
            }
            else if (isPaid) {
                cout << "Order is already paid!" << endl;
            }
            else {
                int method = 0;
                double cash = 0.0;

                cout << fixed << setprecision(2);
                cout << "\nTotal to pay: RM " << totalPrice << endl;

                do {
                    cout << "1. Cash" << endl;
                    cout << "2. QR" << endl;
                    cout << "Choose payment method (1-2): ";
                    cin >> method;
                    if (method < 1 || method > 2) {
                        cout << "Invalid choice! Enter 1 or 2." << endl;
                    }
                } while (method < 1 || method > 2);

                if (method == 1) {
                    payMethod = "Cash";
                    do {
                        cout << "Enter cash amount (RM): ";
                        cin >> cash;
                        if (cash < totalPrice) {
                            cout << "Cash must be at least RM " << totalPrice << endl;
                        }
                    } while (cash < totalPrice);
                    changeDue = cash - totalPrice;
                    cout << "Payment done! Change: RM " << changeDue << endl;
                }
                else {
                    payMethod = "QR";
                    changeDue = 0.0;
                    cout << "QR payment done!" << endl;
                }

                isPaid = true;
                totalOrders = totalOrders + 1;
                dailySales = dailySales + totalPrice;
                dailyDiscount = dailyDiscount + discount;
            }
        }
        else if (choice == 6) {
            if (!isPaid) {
                cout << "Please pay first before viewing the receipt." << endl;
            }
            else {
                cout << fixed << setprecision(2);
                cout << "\n==========================================" << endl;
                cout << "       FAST2PRINT DESIGN & PRINT SHOP          " << endl;
                cout << "                 RECEIPT                  " << endl;
                cout << "==========================================" << endl;
                cout << "Service  : " << serviceName << endl;
                cout << "Paper    : " << paperName << endl;
                cout << "Colour   : " << colourName << endl;
                cout << "Quantity : " << qty << endl;
                cout << "Unit RM  : RM " << unitPrice << endl;
                cout << "Discount : RM " << discount << endl;
                cout << "Total    : RM " << totalPrice << endl;
                cout << "Payment  : " << payMethod << endl;
                cout << "Change   : RM " << changeDue << endl;
                cout << "==========================================" << endl;
            }
        }
        else if (choice == 0) {
            cout << "Going back to Main Menu..." << endl;
        }
        else {
            cout << "Invalid choice! Please choose 0 to 6." << endl;
        }
    } while (choice != 0);
}

double calculateUnitPrice(int serviceChoice, int paperChoice, int colourChoice) {
    double base = 0.0;
    double paperCost = 0.0;
    double colourCost = 0.0;

    if (serviceChoice == 1) base = 15.00;
    else if (serviceChoice == 2) base = 2.00;
    else if (serviceChoice == 3) base = 35.00;
    else base = 1.50;

    if (paperChoice == 2) paperCost = 2.00;
    if (colourChoice == 2) colourCost = 3.00;

    return base + paperCost + colourCost;
}

double calculateDiscount(double unitPrice, int qty) {
    double subtotal = unitPrice * qty;
    if (qty >= 50) {
        return subtotal * 0.10;
    }
    return 0.0;
}

double calculateTotalPrice(double unitPrice, int qty, double discount) {
    double subtotal = unitPrice * qty;
    return subtotal - discount;
}

void staffMenu() {
    int choice = 0;

    do {
        cout << "\n==========================================" << endl;
        cout << "                STAFF MENU                " << endl;
        cout << "==========================================" << endl;
        cout << "1. Generate Daily Sales Report" << endl;
        cout << "2. Search Orders" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "CHOOSE YOUR NUMBER: ";
        cin >> choice;

        if (choice == 1) {
            dailySalesReport();
        }
        else if (choice == 2) {
            cout << "Search Orders will be added in M6." << endl;
        }
        else if (choice == 0) {
            cout << "Going back to Main Menu..." << endl;
        }
        else {
            cout << "Invalid choice! Please choose 0, 1, or 2." << endl;
        }
    } while (choice != 0);
}

void dailySalesReport() {
    cout << fixed << setprecision(2);
    cout << "\n==========================================" << endl;
    cout << "            DAILY SALES REPORT            " << endl;
    cout << "==========================================" << endl;
    cout << "Total Orders   : " << totalOrders << endl;
    cout << "Total Discount : RM " << dailyDiscount << endl;
    cout << "Total Sales    : RM " << dailySales << endl;
    cout << "==========================================" << endl;
}