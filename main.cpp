#include "./utils/utility.cpp"

int main() {
    Utility utility;

    string full_names, username, account_pin;
    cout << "Enter the full names name :-";
    getline(cin, full_names);

    cout << "Enter the username name :-";
    getline(cin, username);

    cout << "Enter the PIN name :-";
    getline(cin, account_pin);

    utility.save_account(full_names, username, account_pin);

    return 0;
}
