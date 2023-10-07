
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
    DoublyLinkedList() : head(nullptr), tail(nullptr) {
        
        loadFromFile("ModesOfTransport.txt");
    }

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

    void saveToFile() {
        ofstream outFile("ModesOfTransport.txt");
        Node* current = head;
        while (current) {
            outFile << current->modeName << endl;
            current = current->next;
        }
        outFile.close();
    }

    Node* getHead() const {
        return head;
    }

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

    int countModes() {
        Node* current = head;
        int modeCount = 0;
        while (current) {
            modeCount++;
            current = current->next;
        }
        return modeCount;
    }

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

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class User {
public:
    string name, gender, address;
    string age, mobileNo, menuBack;
    static int UID;
    char all[999];

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
        cout << "\nSaved \nNOTE: We save your details record for future purposes.\n"
             << endl;
    }

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


class ManageMenu;


void menu(ManageMenu& manageMenu);

class ManageMenu {
private:
    string userName;
    DoublyLinkedList transportModes;

public:
    ManageMenu();

    ~ManageMenu() {}

    DoublyLinkedList& getTransportModes() {
        return transportModes;
    }
};


void menu(ManageMenu& manageMenu) {
    int mainChoice;
    int inChoice;
    int gotoMenu;
    cout << "\t\t      * Elite Smart Travels *\n"
         << endl;
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

    User a2;
    if (mainChoice == 1) {
        cout << "------Users------\n" << endl;
        cout << "1. Enter New User" << endl;
        cout << "2. See Old Users" << endl;

        cout << "\nEnter choice: ";
        cin >> inChoice;

        system("CLS");
        if (inChoice == 1) {
            a2.getDetails();
        } else if (inChoice == 2) {
            a2.showDetails();
        } else {
            cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
            Sleep(100);
            system("CLS");
            menu(manageMenu);
        }
        cout << "Press 1 to Redirect Main Menu: ";
        cin >> gotoMenu;
        system("CLS");
        if (gotoMenu == 1) {
            menu(manageMenu);
        } else {
            menu(manageMenu);
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
    } else if (mainChoice == 3) {
        while (true) {
            
            cout << "Enter the mode of Transport" << endl;
            manageMenu.getTransportModes().displayModes();
            cout << "Enter 0 to return to the main menu: ";

            int modeChoice;
            cin >> modeChoice;

            if (modeChoice == 0) {
                break; 
            } else if (modeChoice >= 1 && modeChoice <= manageMenu.getTransportModes().countModes()) {
                
                string selectedMode = manageMenu.getTransportModes().getModeName(modeChoice - 1);
                cout << "You selected mode: " << selectedMode << endl;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    } else if (mainChoice == 4) {
        
    } else if (mainChoice == 5) {
        cout << "\n\n\t--GOOD-BYE!--" << endl;
        Sleep(1100);
        system("CLS");
        ManageMenu();
    } else {
        cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
        Sleep(1100);
        system("CLS");
        menu(manageMenu);
    }
}



ManageMenu::ManageMenu() {
    system("color 0A");
    while (true) {
        int choice;
        cout << "\t\t\t 1.Admin Login: " << endl;
        cout << "\t\t\t 2.User Login: " << endl;
        cout << "Your Choice(1/2): " << endl;
        cin >> choice;

        if (choice == 1) {
            int choice1;
            cout << "1. Editing the mode of Transport" << endl;
            cout << "2. Viewing the registered users" << endl;
            cin >> choice1;
            if (choice1 == 1) {
                int choice2;
                cout << "1. Add a mode of Transport" << endl;
                cout << "2. Remove a mode of Transport" << endl;
                cout << "Enter your choice(1/2):" << endl;
                cin >> choice2;
                if (choice2 == 1) {
                    string modeName;
                    cout << "Enter the name of the mode of transport: ";
                    cin.ignore();
                    getline(cin, modeName);
                    transportModes.addMode(modeName);
                    transportModes.saveToFile(); 
                    cout << "Mode of transport '" << modeName << "' added successfully." << endl;
                    Sleep(1000);  
                } else if (choice2 == 2) {
                    string modeName;
                    cout << "Enter the name of the mode of transport to remove: ";
                    cin.ignore();
                    getline(cin, modeName);
                    transportModes.removeMode(modeName);
                    transportModes.saveToFile(); 
                } else {
                    cout << "Please enter a valid choice" << endl;
                    Sleep(1000);  
                }
            } else if (choice1 == 2) {
                User a2;
                a2.showDetails();
            }
        } else if (choice == 2) {
            system("CLS");
            menu(*this); 
        } else {
            cout << "Please Enter A Valid Input !!" << endl;
            Sleep(1000);
        }

        
        system("CLS");
    }
}



int main() {
    ManageMenu startObj;
    return 0;
}