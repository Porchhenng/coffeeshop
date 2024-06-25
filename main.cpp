#include "functions.h"

int main()
{
    bool exit = false;
    int opt;
    while (true)
    {
        mainMenu();
        cin >> opt;
        switch (opt)
        {
        case 1:
            while (!exit)
            {
                ifstream readMenu("menu.csv");
                string line;
                string word;
                int count = 0;
                while (getline(readMenu, line))
                {
                    stringstream s(line);
                    string name, priceStr;
                    getline(s, name, ',');
                    getline(s, priceStr, ',');
                    double price = stod(priceStr);
                    insertDrink(name, price);
                    count++;
                }
                readMenu.close();

                servingMenu();
                cout << "Choice: ";
                int opt;
                cin >> opt;
                if (opt == 0)
                {
                    system("cls");
                    exit = true;
                    break;
                }
                else if (opt > 0 && opt <= count)
                {
                    Drink *chosenDrink = head;
                    for (int i = 1; i < opt; i++)
                    {
                        chosenDrink = chosenDrink->next;
                    }
                    string drinkSize;
                    int qty;

                    cout << "Choose a drink size(S/M/L): ";
                    cin >> drinkSize;
                    cout << "How many drinks?: ";
                    cin >> qty;

                    double totalPrice = chosenDrink->price * sizePrice(drinkSize) * qty;
                    ofstream orderFile("orders.csv", ios::app);
                    orderFile << chosenDrink->name << "," << drinkSize << "," << qty << "," << totalPrice << "\n";
                    orderFile.close();
                    calcChange(totalPrice);
                }
                else
                {
                    defaultCase();
                }
            }
            exit = false;
            break;
        case 2:
            while (!exit)
            {
                string tmp;
                adminMenu();
                cin >> opt;
                switch (opt)
                {
                case 1:
                    servingMenu();
                    cin >> tmp;
                    break;
                case 2:
                    addDrink();
                    cin >> tmp;
                    break;
                case 3:
                    removeDrink();
                    cin >> tmp;
                    break;
                case 4:
                    updateDrink();
                    cin >> tmp;
                    break;
                case 5:
                    reportIncome();
                    cin >> tmp;
                    break;
                case 6:
                    reportTotalIncome();
                    cin >> tmp;
                    break;
                case 0:
                    exit = true;
                    system("cls");
                    break;
                default:
                    defaultCase();
                    break;
                }
            }
            exit = false;
            break;
        case 0:
            powerOff();
            // Save daily income to income report file
            uploadReport();
            return 0;
        default:
            system("cls");
            defaultCase();
            break;
        }
    }
}