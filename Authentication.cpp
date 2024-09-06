#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class User {
    private: //Encapsulation 
        string username, password;
        static int totalUsers;
        static int totalSuccessfulLogins;
    public:
        User(string username, string password) {
            totalUsers++;
            this->username = username;
            this->password = password;
        }

        string getUsername() const {  //Encapsulation
            return this->username;
        }
        
        string getPassword() const { 
            return this->password;
        }

        static int getTotalUsers(){
            return totalUsers;
        }

        static int getTotalSuccessfulLogins(){
            return totalSuccessfulLogins;
        }
};

int User::totalUsers = 0;
int User::totalSuccessfulLogins = 0;

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
        void Register() {  //Abstraction function
            string username, password;
            getInputs(username, password);

            User newUser(username, password);
            users.push_back(newUser);

            cout << "............Registration successful........." << endl;
        }

        void displayUsers() const {
            cout<<"Total users: "<<User::getTotalUsers()<<endl;
            for (int i = 0; i < users.size(); ++i) {
                cout << "....." << (i + 1) << ". Username: \"" << users[i].getUsername() << "\", Password: \"" << users[i].getPassword() << "\"....." << endl;                
            }
        }


        bool login() {
            string username, password;
            getInputs(username, password);
            
            cout<<"Total Successful Logins: "<<User::getTotalSuccessfulLogins()<<endl;
            for (int i = 0; i < users.size(); ++i) {
                if (users[i].getUsername() == username && users[i].getPassword() == password) {
                    cout << "Login successful!" << endl;
                    return true;
                }
            }
            cout << "Login failed, incorrect username or password." << endl;
            return false;
        }

        void logout() {
            string username, password;
            getInputs(username, password);

            for (int i = 0; i < users.size(); ++i) {
                if (users[i].getUsername() == username && users[i].getPassword() == password) {
                    users.erase(users.begin() + i);
                    cout << "Logout successful and user removed!" << endl;
                    return;
                }
            }
            cout << "Logout failed, user not found." << endl;
        }   
};

class Menu { //Abstraction class...
    public:
        void displayMenu() {
            cout << "1. Register\n2. Login\n3. Display Users\n4. Logout\n";
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
                userManager->logout();
                break;
        }
    }

    delete userManager;
    delete menu;

    return 0;
}
