#include <iostream>
#include <string>
#include <map>
using namespace std;

class login {
public:
    void run() {
        map<string, string> users;
        string username, password;

        while (true) {
            cout << "1. Log in\n2. Sign up\n0. Exit\n";
            cout << "Choose option: ";
            int a;
            cin >> a;

            switch (a) {
                case 1:
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;

                    if (users.count(username) && users[username] == password) {
                        cout << "Hello " << username << ", welcome back\n";
                    } else {
                        cout << "Incorrect username and password pair\n";
                    }
                    break;

                case 2: {
                    cout << "Enter username: ";
                    cin >> username;

                    bool passwordsMatch = false;
                    do {
                        cout << "Enter password: ";
                        cin >> password;
                        cout << "Reenter password: ";
                        string password_re;
                        cin >> password_re;

                        if (password == password_re) {
                            passwordsMatch = true;
                            users[username] = password;
                            cout << "Your account has been created\n";
                        } else {
                            cout << "Passwords don't match. Try again.\n";
                        }
                    } while (!passwordsMatch);
                    break;
                }

                case 0:
                    return;

                default:
                    cout << "Wrong input\n";
            }
        }
    }
};

int main() {
    login obj;
    obj.run();
    return 0;
}