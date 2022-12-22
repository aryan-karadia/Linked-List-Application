// hydro.cpp

#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

#include "list.h"
#include "hydro.h"

const char *FILENAME = "C:\\Users\\Owner\\Desktop\\Software Portfolio\\Linked-List-Application\\flow.txt";

int main()
{
    FlowList list;
    int result;

    displayHeader();
    pressEnter();

    result = readData(FILENAME, list);
    if (result == 0)
    {
        cout << "Error reading data from file " << FILENAME << endl;
        exit(1);
    }

    int quit = 0;

    while (1)
    {
        switch (menu())
        {
        case 1:
            displayData(list);
            pressEnter();
            break;
        case 2:
            addData(list, result);
            pressEnter();
            break;
        case 3:
            saveData(list);
            pressEnter();
            break;
        case 4:
            removeData(list);
            pressEnter();
            break;
        case 5:
            cout << "Program terminated.\n\n";
            quit = 1;
            break;
        default:
            cout << endl
                 << "Invalid choice. Try again." << endl;
            pressEnter();
        }
        if (quit)
            break;
    }
    return 0;
}

void displayHeader()
{
    cout << "Program: Flow studies - Fall 2022" << endl;
    cout << "Version: 1.0" << endl;
    cout << "Lab section: B01" << endl;
    cout << "Produced By: Aryan Karadia" << endl;
}

void pressEnter()
{
    cout << "\n<<< Press Enter to continue >>>\n";
    cin.ignore(10, '\n');
    cin.get();
}

int readData(const char *filename, FlowList &list)
{
    ifstream fin;
    fin.open(filename);
    if (fin.fail())
    {
        cout << "Error opening file " << filename << endl;
        return 0;
    }
    ListItem item;
    int count = 0;
    while (fin >> item.year >> item.flow)
    {
        list.insert(item);
        count++;
    }
    fin.close();
    return count;
}

int menu()
{
    int choice;
    cout << "Please select from the following options:" << endl;
    cout << "1. Display the flow list, and the average" << endl;
    cout << "2. Add data." << endl;
    cout << "3. Save data to file." << endl;
    cout << "4. Remove data." << endl;
    cout << "5. Quit." << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void displayData(const FlowList &list)
{
    cout << "The flow list is:" << endl;
    list.print();
    cout << "The average flow is: " << averageData(list) << " billions of cubic meter" << endl;
}

void addData(FlowList &list, int count)
{
    int year;
    double flow;
    ListItem item;
    cout << "Enter the year: ";
    cin >> year;
    cout << "Enter the flow: ";
    cin >> flow;
    if (list.find(year) == 1)
    {
        cout << "Error: duplicate data. " << year << " already exists in the list." << endl;
    }
    else
    {
        item.year = year;
        item.flow = flow;
        list.insert(item);
        cout << "The year " << year << " has been added to the list." << endl;
        count++;
    }
}

void removeData(FlowList &list)
{
    int year;
    cout << "Enter the year to be removed: ";
    cin >> year;
    ListItem item;
    item.year = year;
    int success = list.remove(item);
    if (success == 1)
    {
        cout << "The year " << year << " has been removed from the list." << endl;
    }
    else
    {
        cout << "Error: " << year << " does not exist in the list." << endl;
    }
}

int averageData(const FlowList &list)
{
    return list.average();
}

void saveData(const FlowList &list)
{
    list.OutputFile(FILENAME);
    cout << "The data has been saved into the file." << endl;
}