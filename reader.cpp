#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std;

void main() {
    ifstream inFile("inventory.txt");
    if (!inFile) {
        cout << "❌ Cannot open inventory.txt (maybe not created yet).\n";
        return 1;
    }

    cout << "\n📄 Shared Inventory File (via IPC)\n";
    string name;
    int qty;

    while (getline(inFile, name, ',')) {
        inFile >> qty;
        inFile.ignore();
        cout << "Item: " << name << ", Quantity: " << qty << endl;
    }

    inFile.close();
    return 0;
}
int main() {
    while (true) {
        system("cls"); // clear console (Windows only)
        cout << "--- 🕒 Inventory Monitor (updated every 3 sec) ---\n";
        readInventory();

        std::this_thread::sleep_for(std::chrono::seconds(3)); // wait 3 seconds
    }

    return 0;
}
