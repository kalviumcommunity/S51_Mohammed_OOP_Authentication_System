#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Base class: Person
class Person {
protected:
    string name;
    string contactInfo;

public:
    Person(string name = "Unknown", string contactInfo = "None") : name(name), contactInfo(contactInfo) {}

    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }
};

// Derived class: User (Single Inheritance from Person)
class User : public Person {
protected:
    string username, password;

public:
    static int totalUsers;

    User(string username, string password, string name, string contactInfo)
        : Person(name, contactInfo), username(username), password(password) {
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
    Admin(string username, string password, string name, string contactInfo)
        : User(username, password, name, contactInfo) {}

    void displayPrivileges() const override {
        cout << "Privileges: Can manage users, view logs, and perform administrative tasks.\n";
    }

    void removeUser(vector<User>& users, const string& usernameToRemove) {
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].getUsername() == usernameToRemove) {
                users.erase(users.begin() + i);
                cout << "User \"" << usernameToRemove << "\" has been removed by Admin.\n";
                return;
            }
        }
        cout << "User not found!\n";
    }
};

// Derived class: GuestUser (Hierarchical Inheritance from Person)
class GuestUser : public Person {
public:
    GuestUser(string name, string contactInfo) : Person(name, contactInfo) {}

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

    void Register() {
        string username, password, name, contactInfo;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter contact information: ";
        cin >> contactInfo;

        User newUser(username, password, name, contactInfo);
        users.push_back(newUser);

        cout << "Registration successful for user \"" << username << "\".\n";
    }

    void displayUsers() const {
        cout << "Total users: " << User::getTotalUsers() << endl;
        for (const auto& user : users) {
            cout << "User: " << user.getUsername() << ", Name: " << user.getName()
                 << ", Contact: " << user.getContactInfo() << endl;
            user.displayPrivileges();  // Display privileges based on the user type
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
                cout << "Login successful! Welcome " << user.getName() << ".\n";
                user.displayPrivileges();  // Show privileges based on user type
                return;
            }
        }
        cout << "Login failed, incorrect username or password.\n";
    }

    void adminRemoveUser() {
        string usernameToRemove;
        cout << "Enter username to remove: ";
        cin >> usernameToRemove;
        admin.removeUser(users, usernameToRemove);  // Admin removes a user
    }
};

// Class to handle the Menu options
class Menu {
public:
    void displayMenu() {
        cout << "1. Register\n2. Login\n3. Display Users\n4. Admin Remove User\n";
    }

    int getUserChoice() {
        int choice;
        while (true) {
            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 4) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 4." << endl;
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
                userManager->Register();
                break;
            case 2:
                userManager->login();
                break;
            case 3:
                userManager->displayUsers();
                break;
            case 4:
                userManager->adminRemoveUser();
                break;
        }
    }

    delete userManager;
    delete menu;

    return 0;
}
