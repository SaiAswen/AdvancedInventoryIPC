#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class InventoryItem {
    string name;
    int quantity;

public:
    InventoryItem(string itemName, int qty) {
        name = itemName;
        quantity = qty;
    }

    void display() const {
        cout << "Item: " << name << ", Quantity: " << quantity << endl;
    }

    string getName() const { return name; }
    int getQuantity() const { return quantity; }
};

// Save inventory to file
void saveToFile(const vector<InventoryItem>& inventory) {
    ofstream outFile("inventory.txt");
    if (!outFile) {
        cout << "❌ Error: Could not write to file.\n";
        return;
    }

    for (const auto& item : inventory) {
        outFile << item.getName() << "," << item.getQuantity() << endl;
    }

    outFile.close();
}

// Load inventory from file
void loadFromFile(vector<InventoryItem>& inventory) {
    ifstream inFile("inventory.txt");
    if (!inFile) return;

    string name;
    int qty;

    while (getline(inFile, name, ',')) {
        inFile >> qty;
        inFile.ignore(); // skip newline
        inventory.push_back(InventoryItem(name, qty));
    }

    inFile.close();
}

int main() {
    vector<InventoryItem> inventory;
    int choice;

    loadFromFile(inventory); // Load existing data

    do {
        cout << "\n--- Inventory Management Menu ---\n";
        cout << "1. Add Item\n";
        cout << "2. View All Items\n";
        cout << "3. Exit\n";
        cout << "4. Delete Item\n";
        cout << "5. Search Item\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name;
            int qty;

            cout << "Enter item name: ";
            getline(cin, name);
            cout << "Enter quantity: ";
            cin >> qty;
            cin.ignore();

            inventory.push_back(InventoryItem(name, qty));
            cout << "Item added successfully!\n";

        } else if (choice == 2) {
            if (inventory.empty()) {
                cout << "Inventory is empty.\n";
            } else {
                cout << "\n--- Inventory List ---\n";
                for (const auto& item : inventory) {
                    item.display();
                }
            }

        } else if (choice == 4) {
            if (inventory.empty()) {
                cout << "Inventory is empty.\n";
            } else {
                string nameToDelete;
                cout << "Enter the name of the item to delete: ";
                getline(cin, nameToDelete);

                bool found = false;
                for (auto it = inventory.begin(); it != inventory.end(); ++it) {
                    if (it->getName() == nameToDelete) {
                        inventory.erase(it);
                        cout << "Item '" << nameToDelete << "' deleted.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Item not found.\n";
                }
            }

        } else if (choice == 5) {
            if (inventory.empty()) {
                cout << "Inventory is empty.\n";
            } else {
                string nameToSearch;
                cout << "Enter the item name to search: ";
                getline(cin, nameToSearch);

                bool found = false;
                for (const auto& item : inventory) {
                    if (item.getName() == nameToSearch) {
                        cout << "Found: ";
                        item.display();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Item '" << nameToSearch << "' not found.\n";
                }
            }

        } else if (choice == 3) {
            saveToFile(inventory);
            cout << "Inventory saved. Exiting...\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
