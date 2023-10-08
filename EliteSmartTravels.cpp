#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;


class Node {
public:
    string modeName;
    Node* next;
    Node* prev;

    Node(const string& name) : modeName(name), next(nullptr), prev(nullptr) {}
};


class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

   
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        string mode;
        while (getline(inFile, mode)) {
            addMode(mode);
        }
        inFile.close();
    }

    
    void addMode(const string& name) {
        Node* newNode = new Node(name);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Remove a mode of transport from the list
    void removeMode(const string& name) {
        Node* current = head;
        while (current) {
            if (current->modeName == name) {
                if (current == head) {
                    head = current->next;
                    if (head) {
                        head->prev = nullptr;
                    }
                } else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                cout << "Mode of transport '" << name << "' removed successfully." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Mode of transport '" << name << "' not found." << endl;
    }

    // Save modes of transport to a file
    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        Node* current = head;
        while (current) {
            outFile << current->modeName << endl;
            current = current->next;
        }
        outFile.close();
    }

    // Get the head of the linked list
    Node* getHead() const {
        return head;
    }

    // Display all modes of transport
    void displayModes() {
        Node* current = head;
        cout << "\n------ Modes of Transport ------\n" << endl;
        int modeCount = 1;
        while (current) {
            cout << modeCount << ". " << current->modeName << endl;
            current = current->next;
            modeCount++;
        }
    }

    // Count the number of modes of transport
    int countModes() {
        Node* current = head;
        int modeCount = 0;
        while (current) {
            modeCount++;
            current = current->next;
        }
        return modeCount;
    }

    // Get the name of a mode of transport at a specific index
    string getModeName(int index) {
        Node* current = head;
        int currentIndex = 0;
        while (current) {
            if (currentIndex == index) {
                return current->modeName;
            }
            current = current->next;
            currentIndex++;
        }
        return "";
    }

    // Destructor to free memory
    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// User class to manage user details
class User {
public:
    string name, gender, address;
    int age;
    string mobileNo;
    string menuBack;
    static int UID;
    char all[999];

    // Get user details
    void getDetails() {
        ofstream out("Registered_Users.txt", ios::app);
        {
            cout << "\nEnter User ID: ";
            cin >> UID;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Mobile Number: ";
            cin.ignore();
            getline(cin, mobileNo);
            cout << "Address: ";
            cin.ignore();
            getline(cin, address);
            cout << "Gender: ";
            cin >> gender;
        }
        out << "\nUser ID: " << UID << "\nName: " << name << "\nAge: " << age << "\nMobile Number: " << mobileNo << "\nAddress: " << address << "\nGender: " << gender << endl;
        out.close();
        cout << "\nSaved \nNOTE: We save your details record for future purposes.\n" << endl;
    }

    // Show user details
    void showDetails() {
        ifstream in("Registered_Users.txt");
        {
            if (!in) {
                cout << "File Error!" << endl;
            }
            while (!(in.eof())) {
                in.getline(all, 999);
                cout << all << endl;
            }
            in.close();
        }
    }
};

int User::UID;

// Receipt class to manage receipt details
class Receipt {
public:
    string source;
    string destination;
    double fare;

    Receipt() : source(""), destination(""), fare(0.0) {}

    // Set receipt details
    void setDetails(const string& src, const string& dest, double fare) {
        source = src;
        destination = dest;
        this->fare = fare;
    }

    // Save receipt details to a file
    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "Source: " << source << endl;
            outFile << "Destination: " << destination << endl;
            outFile << "Fare: $" << fixed << setprecision(2) << fare << endl;
            outFile.close();
            cout << "Receipt saved successfully." << endl;
        } else {
            cout << "Error saving receipt to file." << endl;
        }
    }

    // Load receipt details from a file
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Error loading receipt from file." << endl;
        }
    }
};

// ManageMenu class to handle user and admin menus
class ManageMenu {
private:
    string userName;
    DoublyLinkedList transportModes;

public:
    ManageMenu() {
        transportModes.loadFromFile("ModesOfTransport.txt");
    }

    // Admin menu
    void adminMenu() {
        int choice1;
        cout << "1. Editing the mode of Transport" << endl;
        cout << "2. Viewing the registered users" << endl;
        cin >> choice1;
        if (choice1 == 1) {
            int choice2;
            cout << "1. Add a mode of Transport" << endl;
            cout << "2. Remove a mode of Transport" << endl;
            cin >> choice2;
            if (choice2 == 1) {
                string modeName;
                cout << "Enter the name of the mode of transport: ";
                cin.ignore();
                getline(cin, modeName);
                transportModes.addMode(modeName);
                transportModes.saveToFile("ModesOfTransport.txt");
                cout << "Mode of transport '" << modeName << "' added successfully." << endl;
                Sleep(1000);
            } else if (choice2 == 2) {
                string modeName;
                cout << "Enter the name of the mode of transport to remove: ";
                cin.ignore();
                getline(cin, modeName);
                transportModes.removeMode(modeName);
                transportModes.saveToFile("ModesOfTransport.txt");
                cout << "Press 1 to return to the main menu, or 0 to exit: ";
                int choice;
                cin >> choice;
                if (choice == 1) {
                    adminMenu();
                }
            } else {
                cout << "Please enter a valid choice" << endl;
                Sleep(1000);
            }
        } else if (choice1 == 2) {
            viewRegisteredUsers();
        }
    }

    // User menu
    void userMenu() {
        User user;
        int mainChoice;
        int inChoice;
        int gotoMenu;
        cout << "\t\t      * Elite Smart Travels *\n" << endl;
        cout << "      -------------------------Main Menu--------------------" << endl;
        cout << "\t _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  " << endl;
        cout << "\t|\t\t\t\t\t        |" << endl;
        cout << "\t|\tAdd Personal Details           -> 1\t|" << endl;
        cout << "\t|\tEnter Source and Destination   -> 2\t|" << endl;
        cout << "\t|\tMode of Transports             -> 3\t|" << endl;
        cout << "\t|\tView Receipt                   -> 4\t|" << endl;
        cout << "\t|\tExit                           -> 5\t|" << endl;
        cout << "\t|\t\t\t\t\t        |" << endl;
        cout << "\t|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|" << endl;
        cout << "\nEnter Choice: ";
        cin >> mainChoice;
        system("CLS");
        if (mainChoice == 1) {
            cout << "------Users------\n" << endl;
            cout << "1. Enter New User" << endl;
            cout << "2. See Old Users" << endl;
            cout << "\nEnter choice: ";
            cin >> inChoice;
            system("CLS");
            if (inChoice == 1) {
                user.getDetails();
            } else if (inChoice == 2) {
                user.showDetails();
            } else {
                cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
                Sleep(100);
                system("CLS");
                userMenu();
            }
            cout << "Press 1 to Redirect Main Menu: ";
            cin >> gotoMenu;
            system("CLS");
            if (gotoMenu == 1) {
                userMenu();
            } else {
                userMenu();
            }
        } else if (mainChoice == 2) {
            int s, d;
            cout << "Enter Source" << endl;
            cout << "1. Pune" << endl;
            cout << "2. Mumbai" << endl;
            cout << "3. Delhi" << endl;
            cin >> s;
            cout << "Enter Destination" << endl;
            cout << "1. Pune" << endl;
            cout << "2. Mumbai" << endl;
            cout << "3. Delhi" << endl;
            cin >> d;

            // Generate receipt
            string source, destination;
            
            // Determine source and destination based on user input
            if (s == 1) {
                source = "Pune";
            } else if (s == 2) {
                source = "Mumbai";
            } else if (s == 3) {
                source = "Delhi";
            }

            if (d == 1) {
                destination = "Pune";
            } else if (d == 2) {
                destination = "Mumbai";
            } else if (d == 3) {
                destination = "Delhi";
            }

            // Calculate fare based on source and destination
            double fare = calculateFare(source, destination);

            // Create a receipt object and set its details
            Receipt receipt;
            receipt.setDetails(source, destination, fare);

            // Save the receipt to a file
            receipt.saveToFile("Receipt.txt");

            // Display the receipt
            receipt.loadFromFile("Receipt.txt");

            cout << "Press 1 to return to the main menu: ";
            int choice;
            cin >> choice;
            if (choice == 1) {
                userMenu();
            }
        } else if (mainChoice == 3) {
            while (true) {
                cout << "Enter the mode of Transport" << endl;
                transportModes.displayModes();
                cout << "Enter 0 to return to the main menu: ";
                int modeChoice;
                cin >> modeChoice;
                if (modeChoice == 0) {
                    break;
                } else if (modeChoice >= 1 && modeChoice <= transportModes.countModes()) {
                    string selectedMode = transportModes.getModeName(modeChoice - 1);
                    cout << "You selected mode: " << selectedMode << endl;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        } else if (mainChoice == 4) {
            // View receipt
            Receipt receipt;
            receipt.loadFromFile("Receipt.txt");
        } else if (mainChoice == 5) {
            cout << "\n\n\t--GOOD-BYE!--" << endl;
            Sleep(1100);
            system("CLS");
        } else {
            cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
            Sleep(1100);
            system("CLS");
            userMenu();
        }
    }

    // View registered users
    void viewRegisteredUsers() {
        ifstream in("Registered_Users.txt");
        if (!in) {
            cout << "File Error: Unable to open Registered_Users.txt" << endl;
        } else {
            cout << "Registered Users:\n" << endl;
            char all[999];
            while (in.getline(all, 999)) {
                cout << all << endl;
            }
            in.close();
        }
    }

    // Calculate fare based on source and destination
    double calculateFare(const string& source, const string& destination) {
        // Implement your fare calculation logic here
        // For now, let's assume a fixed fare of $50
        return 50.0;
    }

    DoublyLinkedList& getTransportModes() {
        return transportModes;
    }
};

int main() {
    int choice;

    do {
        system("CLS");
        cout << "1.Admin Login:" << endl;
        cout << "2.User Login:" << endl;
        cout << "Your Choice(1/2): ";
        cin >> choice;
        system("CLS");
        ManageMenu startObj;

        if (choice == 1) {
            startObj.adminMenu();
        } else if (choice == 2) {
            startObj.userMenu();
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << "Press 1 to continue or 0 to exit: ";
        cin >> choice;
    } while (choice != 0);

    cout << "Goodbye!" << endl;
    return 0;
}
