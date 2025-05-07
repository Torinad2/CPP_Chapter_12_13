/*************************************************************
 * Inventory Management Program                              *
 *                                                           *
 * This program allows the user to:                          *
 * 1. Add new inventory records to a file                    *
 * 2. Display any record from the file                       *
 *                                                           *
 * Each record contains:                                     *
 * - Item Description                                        *
 * - Quantity on Hand                                        *
 * - Wholesale Cost                                          *
 * - Retail Cost                                             *
 *                                                           *
 * Developed by: Nikita Baiborodov                           *
 *************************************************************/

#include <iostream>  // For standard I/O operations
#include <fstream>   // For file stream operations
#include <iomanip>   // For controlling output formatting
#include <string>    // For using the string class

using namespace std;

/*************************************************************
 * Structure Definition                                      *
 * Holds the data for an inventory item                      *
 *************************************************************/
struct InventoryItem {
    string itemDescription;     // Description of the item
    int    quantityOnHand;      // Number of items currently in stock
    double wholesaleCost;       // Cost to purchase the item wholesale
    double retailCost;          // Cost to sell the item to customers
};

/*************************************************************
 * Function Prototypes                                       *
 *************************************************************/
void addRecord(fstream&);     // Adds a new record to the file
void displayRecord(fstream&); // Displays a record from the file

/*************************************************************
 * Main Function                                             *
 * Handles user interface and menu processing                *
 *************************************************************/
int main() {

    /*************************************************************
     * Open file for input and output, append mode to add records*
     *************************************************************/
    fstream file("inventory.txt", ios::in | ios::out | ios::app);

    if (!file) {
        cout << "\nError: File could not be opened.\n";
        return 1; // Exit program if file could not be opened
    }

    int choice = 0; // Variable to store user menu choice

    /*************************************************************
     * Display menu and process choices                          *
     *************************************************************/
    do {
        // Display menu options
        cout << "\nInventory Management Menu\n";
        cout << "1. Add new records\n";
        cout << "2. Display a record\n";
        cout << "3. Quit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice; // Read user's choice

        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(1000, '\n'); // Discard invalid input
            cout << "Error: Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        switch (choice) {
        case 1:
            addRecord(file);                 // Add a new inventory record
            break;
        case 2:
            displayRecord(file);             // Display a specific record
            break;
        case 3:
            cout << "Exiting program...\n";  // Exit message
            break;
        default:
            cout << "Error: Please select a valid option (1-3).\n";
        }

    } while (choice != 3);

    /*************************************************************
     * Close the file and exit program                           *
     *************************************************************/
    file.close();

    /*************************************************************
     * Developer Signature                                       *
     *************************************************************/
    cout << "-------------------------------\n";
    cout << "Developed by: Nikita Baiborodov" << endl;
    cout << "-------------------------------\n";

    return 0;
}

/*************************************************************
 * addRecord                                                 *
 * This function prompts the user for item details, validates*
 * the input, and writes it to the file.                     *
 *************************************************************/
void addRecord(fstream& file) {

    InventoryItem item; // Temporary variable to store new item info

    /*************************************************************
     * Prompt user for item details                              *
     *************************************************************/
    cout << "\nEnter item description (Text): ";
    cin.ignore();                       // Clear leftover newline
    getline(cin, item.itemDescription); // Read full line for description

    // Validate quantity input (must be non-negative)
    do {
        cout << "Enter quantity on hand (Int): ";
        cin >> item.quantityOnHand;

        if (cin.fail() || item.quantityOnHand < 0) {
            cin.clear(); // Clear error flag
            cin.ignore(1000, '\n'); // Discard bad input
            cout << "Error: Quantity must be a non-negative integer.\n";
        }
    } while (item.quantityOnHand < 0);

    // Validate wholesale cost input (must be non-negative)
    do {
        cout << "Enter wholesale cost (Double): ";
        cin >> item.wholesaleCost;

        if (cin.fail() || item.wholesaleCost < 0) {
            cin.clear(); // Clear error flag
            cin.ignore(1000, '\n'); // Discard bad input
            cout << "Error: Wholesale cost must be a non-negative value.\n";
        }
    } while (item.wholesaleCost < 0);

    // Validate retail cost input (must be non-negative)
    do {
        cout << "Enter retail cost (Double): ";
        cin >> item.retailCost;

        if (cin.fail() || item.retailCost < 0) {
            cin.clear(); // Clear error flag
            cin.ignore(1000, '\n'); // Discard bad input
            cout << "Error: Retail cost must be a non-negative value.\n";
        }
    } while (item.retailCost < 0);

    /*************************************************************
     * Write the record to the file                              *
     *************************************************************/
    file.clear();  // Clear any error flags
    file << item.itemDescription << '\n'
        << item.quantityOnHand << '\n'
        << item.wholesaleCost << '\n'
        << item.retailCost << '\n';

    cout << "\nRecord added successfully.\n";
}

/*************************************************************
 * displayRecord                                             *
 * This function reads through the file line by line and     *
 * displays the selected record.                             *
 *************************************************************/
void displayRecord(fstream& file) {

    InventoryItem item;    // Temporary variable to store each record
    int recordNumber;      // User's desired record number to display

    cout << "\nEnter record number to display: ";
    cin >> recordNumber;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error: Invalid input. Please enter a valid record number.\n";
        return;
    }

    file.clear();
    file.seekg(0, ios::beg); // Go back to the beginning of the file

    int currentRecord = 1; // Counter for current record position

    /*************************************************************
     * Loop through file records and display the selected one    *
     *************************************************************/
    while (currentRecord <= recordNumber &&
        getline(file, item.itemDescription) &&   // Read item description
        file >> item.quantityOnHand &&           // Read quantity on hand
        file >> item.wholesaleCost &&            // Read wholesale cost
        file >> item.retailCost) {               // Read retail cost

        file.ignore(); // Consume newline character

        if (currentRecord == recordNumber) {
            cout << fixed << showpoint << setprecision(2);
            cout << "\nRecord #" << recordNumber << ":\n";
            cout << "Item Description: " << item.itemDescription << endl;
            cout << "Quantity on hand: " << item.quantityOnHand << endl;
            cout << "Wholesale cost  : $" << item.wholesaleCost << endl;
            cout << "Retail cost     : $" << item.retailCost << endl;
            return;
        }
        currentRecord++;
    }

    cout << "\nError: Record not found.\n";
}
