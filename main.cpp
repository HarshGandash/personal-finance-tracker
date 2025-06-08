#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Expense {
    float amount;
    string category;
    string description;
    
    void display() const {
        cout << "Rs:" << amount << " - " << category << " - " << description << endl;
    }
};

void addExpense() {
    Expense e;
    cout << "Enter amount: ";
    cin >> e.amount;
    cout << "Enter category: ";
    cin >> e.category;
    cout << "Enter description: ";
    cin >> e.description;
    
    // Save to file
    ofstream file("expenses.txt", ios::app);
    file << e.amount << "," << e.category << "," << e.description << "\n";
    file.close();
    
    cout << "Expense saved!\n";
}

vector<Expense> loadExpenses() {
    vector<Expense> expenses;
    ifstream file("expenses.txt");
    string line;
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        Expense e;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        
        e.amount = stof(line.substr(0, pos1));
        e.category = line.substr(pos1 + 1, pos2 - pos1 - 1);
        e.description = line.substr(pos2 + 1);
        
        expenses.push_back(e);
    }
    file.close();
    return expenses;
}

void viewAllExpenses() {
    vector<Expense> expenses = loadExpenses();
    
    if (expenses.empty()) {
        cout << "No expenses found.\n";
        return;
    }
    
    cout << "\n--- All Expenses ---\n";
    for (const auto& e : expenses) {
        e.display();
    }
}

void viewSummary() {
    vector<Expense> expenses = loadExpenses();
    map<string, float> totals;
    
    for (const auto& e : expenses) {
        totals[e.category] += e.amount;
    }
    
    cout << "\n--- Summary by Category ---\n";
    for (const auto& pair : totals) {
        cout << pair.first << ": ₹" << pair.second << endl;
    }
}

int main() {
    int choice;
    
    while (true) {
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. View Summary\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewAllExpenses();
                break;
            case 3:
                viewSummary();
                break;
            case 4:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}