#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class User {
    private:
        string username, password;
    public:
        User(string name, string pass) {
            this->username = name;
            this->password = pass; 
        }

        string getUsername() const { return username; }
        string getPassword() const { return password; }
};

class UserManager {
    private:
        vector<User> users; 

        void getInputs(string &username, string &password) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
        }

    public:
        void Register() {
            string username, password;
            getInputs(username, password);

            User newUser(username, password);
            users.push_back(newUser);

            cout << "............Registration successful........." << endl;
        }

        void displayUsers() const {
            for (const auto& user : users) {
                cout << "...Username: " << user.getUsername() << ", Password: " << user.getPassword() <<"..."<< endl;                
            }
        }

        bool login() {
            string username, password;
            getInputs(username, password);

            for (const auto& user : users) {
                if (user.getUsername() == username && user.getPassword() == password) {
                    cout << "Login successful!" << endl;
                    return true;
                }
            }
            cout << "Login failed. Incorrect username or password." << endl;
            return false;
        }
};

class Menu {
    public:
        void displayMenu() {
            cout << "1. Register\n2. Login\n3. Display Users\n4. Exit\n";
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
    UserManager userManager;
    Menu menu;
    int choice;

    while (true) {
        menu.displayMenu();
        choice = menu.getUserChoice();

        switch (choice) {
            case 1:
                userManager.Register();
                break;
            case 2:
                userManager.login();
                break;
            case 3:
                userManager.displayUsers();
                break;
            case 4:
                return 0;
        }
    }

    return 0;
}
