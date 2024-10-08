#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Base class: Person
class Person {
protected:
    string name;
    string email;

public:
    Person(string name = "Unknown", string email = "None") : name(name), email(email) {}

    string getName() const { return name; }
    string getEmail() const { return email; }
};

// Derived class: User (Single Inheritance from Person)
class User : public Person {
protected:
    string username, password;

public:
    static int totalUsers;

    User(string username, string password, string name, string email)
        : Person(name, email), username(username), password(password) {
        totalUsers++;
    }

    virtual ~User() {
        cout << "User \"" << username << "\" is destroyed!" << endl;
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }

    static int getTotalUsers() {
        return totalUsers;
    }

    virtual void displayPrivileges() const {
        cout << "Privileges: Can login, view personal information.\n";
    }
};

int User::totalUsers = 0;

// Derived class: Admin (Inheritance from User)
class Admin : public User {
public:
    Admin(string username, string password, string name, string email)
        : User(username, password, name, email) {}

    void displayPrivileges() const override {
        cout << "Privileges: Can manage users, view logs, and perform administrative tasks.\n";
    }

    void viewUsers(const vector<User>& users) {
        cout << "Total users: " << User::getTotalUsers() << endl;
        for (const auto& user : users) {
            cout << "User: " << user.getUsername() << ", Name: " << user.getName()
                 << ", Email: " << user.getEmail() << endl;
        }
    }
};

// Derived class: GuestUser (Hierarchical Inheritance from Person)
class GuestUser : public Person {
public:
    GuestUser(string name, string email) : Person(name, email) {}

    void displayPrivileges() const {
        cout << "Privileges: Can browse without registration.\n";
    }
};

// Class to manage Users
class UserManager {
private:
    vector<User> users;
    Admin admin;  // Admin user with special privileges

public:
    UserManager()
        : admin("admin", "admin123", "Admin", "admin@admin.com") {
        users.push_back(admin);
        cout << "Admin account created: Username - " << admin.getUsername() << endl;
    }

    void registerUser() {
        string username, password, name, email;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cin.ignore();  // Ignore newline before getline for name input
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter email: ";
        cin >> email;

        User newUser(username, password, name, email);
        users.push_back(newUser);

        cout << "Registration successful for user \"" << username << "\".\n";
        userLogoutMenu();  // Directly show logout menu after signup
    }

    void userLogoutMenu() {
        int choice;
        cout << "1. Logout\n";
        while (true) {
            cout << "Enter your choice: ";
            cin >> choice;
            if (cin.fail() || choice != 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter 1 to logout." << endl;
            } else {
                cout << "User logged out successfully.\n";
                break;
            }
        }
    }

    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (const auto& user : users) {
            if (user.getUsername() == username && user.getPassword() == password) {
                if (username == "admin") {
                    adminMenu();
                } else {
                    cout << "Login successful! Welcome " << user.getName() << ".\n";
                    userLogoutMenu();
                }
                return;
            }
        }
        cout << "Login failed, incorrect username or password.\n";
    }

    void adminMenu() {
        int choice;
        cout << "Admin Login successful! Welcome, Admin.\n";
        while (true) {
            cout << "1. View Users\n2. Logout\nEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                admin.viewUsers(users);
            } else if (choice == 2) {
                cout << "Admin logged out successfully.\n";
                break;
            } else {
                cout << "Invalid choice! Please enter 1 or 2.\n";
            }
        }
    }

    void guestLogin() {
        GuestUser guest("Guest", "guest@noemail.com");
        cout << "Welcome, Guest.\n";
        guest.displayPrivileges();
        guestLogoutMenu();
    }

    void guestLogoutMenu() {
        int choice;
        cout << "1. Logout\n";
        while (true) {
            cout << "Enter your choice: ";
            cin >> choice;
            if (cin.fail() || choice != 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter 1 to logout." << endl;
            } else {
                cout << "Guest logged out successfully.\n";
                break;
            }
        }
    }
};

// Class to handle the Menu options
class Menu {
public:
    void displayMenu() {
        cout << "1. Signup\n2. Login\n3. Guest\n";
    }

    int getUserChoice() {
        int choice;
        while (true) {
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 3) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            } else {
                return choice;
            }
        }
    }
};

int main() {
    UserManager* userManager = new UserManager();
    Menu* menu = new Menu();
    int choice;

    while (true) {
        menu->displayMenu();
        choice = menu->getUserChoice();

        switch (choice) {
            case 1:
                userManager->registerUser();
                break;
            case 2:
                userManager->login();
                break;
            case 3:
                userManager->guestLogin();
                break;
        }
    }

    delete userManager;
    delete menu;

    return 0;
}
