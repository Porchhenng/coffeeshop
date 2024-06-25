#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <strings.h>
#include <cstring>

using namespace std;

struct Drink
{
    string name;
    double price;
    Drink *next;

    Drink() {}

    Drink(string name, double price)
    {
        this->name = name;
        this->price = price;
    }

    void addDrink(string name, double price)
    {
        this->name = name;
        this->price = price;
    }
};

Drink* head = NULL;

void insertDrink(string name, double price) {
    Drink* newDrink = new Drink;
    newDrink->name = name;
    newDrink->price = price;
    newDrink->next = NULL;

    if (head == NULL) {
        head = newDrink;
    } else {
        Drink* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newDrink;
    }
}

void defaultCase()
{
    cout << "Invalid option, please choose another option!\n";
}

void mainMenu()
{
    cout << "===== Main Menu =====\n";
    cout << "(1) Serving Menu\n";
    cout << "(2) Administration Menu\n";
    cout << "(0) Power Off\n";
    cout << "Choose an option: ";
}

void servingMenu()
{
    system("cls");
    ifstream readMenu("menu.csv");
    string line;
    string name;
    string price;
    int i = 1;
    cout << "===== Serving Menu =====\n";
    while (getline(readMenu, line))
    {
        stringstream s(line);
        getline(s, name, ',');
        getline(s, price, ',');
        cout << "(" << i << ") ";
        cout << name << " [ $" << price << " ]" << endl;
        i++;
    }
    cout << "(0) Exit\n";

    readMenu.close();
}

float sizePrice(string size)
{
    if (size == "s" || size == "small")
    {
        return 1.00; // Default price for small
    }
    else if (size == "m" || size == "medium")
    {
        return 1.10; // 10% Increase for medium
    }
    else if (size == "l" || size == "large")
    {
        return 1.20; // 20% Increase for large
    }
    else
        return 1.00; // Default price
}

void calcChange(double total)
{
    string tmp;
    double received;
    cout << "Total: $" << total << endl;
    cout << "Received: ";
    cin >> received;

    while (received < total)
    {
        cout << "Received amount is lower than the total.\n";
        cout << "Please re-enter the received amount: ";
        cin >> received;
    }

    double change = received - total;

    cout << "Change: $" << change << endl;
    cout << "Enter any key to exit: ";
    cin >> tmp;
}

string checkSize(string size)
{
    if (size == "s" || size == "small")
    {
        return "Small";
    }
    else if (size == "m" || size == "medium")
    {
        return "Medium";
    }
    else if (size == "l" || size == "large")
    {
        return "Large";
    }
    else
        return "Medium";
}

void adminMenu()
{
    system("cls");
    cout << "===== Administration Menu =====\n";
    cout << "(1) Display Drinks Menu\n";
    cout << "(2) Add Drinks\n";
    cout << "(3) Remove Drinks\n";
    cout << "(4) Update Drinks\n";
    cout << "(5) Report Today's Income\n";
    cout << "(6) Report Total Income Report\n";
    cout << "(0) Exit\n";
    cout << "Choose an option: ";
}

void addDrink()
{
    system("cls");
    string name;
    double price;
    cout << "===== Add Drinks =====\n";
    cout << "Enter the name of the drink: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter the price of the drink: ";
    cin >> price;

    ofstream writeMenu("menu.csv", ios::app);
    writeMenu << name << "," << price << endl;
    writeMenu.close();
    cout << "Enter any key to exit: ";
}

void removeDrink()
{
    system("cls");
    bool found = false;
    string drinkName;
    cout << "===== Remove Drink =====\n";
    cout << "Enter the name of the drink to remove: ";
    cin.ignore();
    getline(cin, drinkName);

    ifstream readMenu("menu.csv");
    ofstream tempFile("temp.csv");

    string line;

    while (getline(readMenu, line))
    {
        stringstream s(line);
        string name, price, type;
        getline(s, name, ',');

        if (strcasecmp(name.c_str(), drinkName.c_str()) != 0)
        {
            tempFile << line << endl;
        }
        else
        {
            found = true;
        }
    }

    readMenu.close();
    tempFile.close();

    remove("menu.csv");
    rename("temp.csv", "menu.csv");

    if (found)
    {
        cout << "Drink has been successfully removed.\n";
    }
    else
    {
        cout << "Failed to remove as drink does not seem to exist in the menu.\n";
    }
    cout << "Enter any key to exit: ";
}

void updateDrink()
{
    system("cls");
    ifstream readMenu("menu.csv");
    ofstream tempFile("temp.csv");
    string line;
    string drinkName, newName, newType;
    double newPrice;
    bool found = false;

    cout << "Enter the name of the drink to update: ";
    cin.ignore();
    getline(cin, drinkName);

    while (getline(readMenu, line))
    {
        stringstream s(line);
        string name;
        string price;
        getline(s, name, ',');

        if (strcasecmp(name.c_str(), drinkName.c_str()) == 0)
        {
            cout << "Enter the new name for the drink: ";
            getline(cin, newName);
            cout << "Enter the new price for the drink: ";
            cin >> newPrice;

            tempFile << newName << "," << newPrice << endl;
            found = true;
            cout << "Successfully updated!\n";
        }
        else
        {
            tempFile << line << endl;
        }
    }

    if (!found)
    {
        cout << "Drink could not be found.\n";
    }

    readMenu.close();
    tempFile.close();

    remove("menu.csv");
    rename("temp.csv", "menu.csv");

    cout << "Enter any key to exit: ";
}

void reportIncome()
{
    system("cls");
    ifstream readMenu("orders.csv");
    string line;
    string name, size, qty, total;
    double totalIncome = 0;
    int i = 1;
    cout << "===== Today's Income =====\n";
    while (getline(readMenu, line))
    {
        stringstream s(line);
        getline(s, name, ',');
        getline(s, size, ',');
        getline(s, qty, ',');
        getline(s, total, ',');
        cout << "Order ID: #" << i << ": ";
        cout << "(Drink: " << name << ") (Size:" << size << ") (Qty: " << qty << ") (Total: $" << total << ")\n";
        i++;
        totalIncome += stod(total);
    }
    cout << endl
         << "Today's Total Income: $" << totalIncome << endl;
    cout << "Enter any key to exit: ";

    readMenu.close();
}

void reportTotalIncome(){
    system("cls");
    ifstream readMenu("income.csv");
    string line;
    string drinks, income;
    int day = 1;
    cout << "===== Income Report =====\n";
    while (getline(readMenu, line))
    {
        stringstream s(line);
        getline(s, drinks, ',');
        getline(s, income, ',');
        cout << "Day #" << day << " // Drinks Served: " << drinks << " // ";
        cout << "Total Income: $" << income << endl;
        day++;
    }
    cout << endl;
    cout << "Enter any key to exit: ";

    readMenu.close();
}

void uploadReport(){
    string line;
    string drink;
    string size;
    string qty;
    string income;
    double total = 0;
    int n = 0;
    ifstream readReport("orders.csv");
    ofstream writeReport("income.csv", ios::app);
    while(getline(readReport, line)){
        stringstream s(line);
        getline(s, drink, ',');
        getline(s, size, ',');
        getline(s, qty, ',');
        getline(s, income, ',');

        total += stod(income);
        n++;
    }
    writeReport << n << "," << total << endl;;
    readReport.close();
    writeReport.close();

    ofstream ofs;
    ofs.open("orders.csv", ofstream::out | ofstream::trunc);
    ofs.close();
}

void powerOff()
{
    system("cls");
    cout << "\nPowering off.";
    Sleep(500);
    system("cls");
    cout << "\nPowering off..";
    Sleep(500);
    system("cls");
    cout << "\nPowering off...";
    Sleep(1000);
    system("cls");
}