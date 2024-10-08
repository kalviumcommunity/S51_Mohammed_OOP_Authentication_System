#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// Base class: Person
class Person {
protected:
    string name;
<<<<<<< HEAD
    string email;

public:
    Person(string name = "Unknown", string email = "None") : name(name), email(email) {}

    string getName() const { return name; }
    string getEmail() const { return email; }
=======
    string contactInfo;

public:
    Person(string name = "Unknown", string contactInfo = "None") : name(name), contactInfo(contactInfo) {}

    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }
>>>>>>> 2a62fab940d094b37883e5f374251787771198cb
};

// Derived class: User (Single Inheritance from Person)
class User : public Person {
protected:
    string username, password;

public:
    static int totalUsers;

<<<<<<< HEAD
    User(string username, string password, string name, string email)
        : Person(name, email), username(username), password(password) {
=======
    User(string username, string password, string name, string contactInfo)
        : Person(name, contactInfo), username(username), password(password) {
>>>>>>> 2a62fab940d094b37883e5f374251787771198cb
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
<<<<<<< HEAD
    Admin(string username, string password, string name, string email)
        : User(username, password, name, email) {}
=======
    Admin(string username, string password, string name, string contactInfo)
        : User(username, password, name, contactInfo) {}
>>>>>>> 2a62fab940d094b37883e5f374251787771198cb

    void displayPrivileges() const override {
        cout << "Privileges: Can manage users, view logs, and perform administrative tasks.\n";
    }

<<<<<<< HEAD
    void viewUsers(const vector<User>& users) {
        cout << "Total users: " << User::getTotalUsers() << endl;
        for (const auto& user : users) {
            cout << "User: " << user.getUsername() << ", Name: " << user.getName()
                 << ", Email: " << user.getEmail() << endl;
        }
=======
    void removeUser(vector<User>& users, const string& usernameToRemove) {
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].getUsername() == usernameToRemove) {
                users.erase(users.begin() + i);
                cout << "User \"" << usernameToRemove << "\" has been removed by Admin.\n";
                return;
            }
        }
        cout << "User not found!\n";
>>>>>>> 2a62fab940d094b37883e5f374251787771198cb
    }
};

// Derived class: GuestUser (Hierarchical Inheritance from Person)
class GuestUser : public Person {
public:
<<<<<<< HEAD
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
=======
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
>>>>>>> 2a62fab940d094b37883e5f374251787771198cb
    }
};

// Class to handle the Menu options
class Menu {
public:
    void displayMenu() {
<<<<<<< HEAD
        cout << "1. Signup\n2. Login\n3. Guest\n";
=======
        cout << "1. Register\n2. Login\n3. Display Users\n4. Admin Remove User\n";
>>>>>>> 2a62fab940d094b37883e5f374251787771198cb
    }

    int getUserChoice() {
        int choice;
        while (true) {
            cout << "Enter your choice: ";
            cin >> choice;

<<<<<<< HEAD
            if (cin.fail() || choice < 1 || choice > 3) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 3." << endl;
=======
            if (cin.fail() || choice < 1 || choice > 4) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 4." << endl;
>>>>>>> 2a62fab940d094b37883e5f374251787771198cb
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
<<<<<<< HEAD
                userManager->guestLogin();
=======
                userManager->displayUsers();
                break;
            case 4:
                userManager->adminRemoveUser();
>>>>>>> 2a62fab940d094b37883e5f374251787771198cb
                break;
        }
    }

    delete userManager;
    delete menu;

    return 0;
}
