//
// Created by anselme on 23/06/22.
//

#include "../utils/Service.cpp"

class AccountService : Service {

public:
    explicit AccountService() : Service("accounts") {}

    void update_by_id(int id, const Account& accountInfo) {

        Account existingAccount = find_by_id(id);
        if (existingAccount.id == -1)
            cout << "User not available in the system";

        vector<Account> previousAccounts = read();

        fstream outputStream;

        outputStream.open(get_temp_data_store_path(), ios::out | ios::app);

        for (const Account &account: previousAccounts) {
            if (account.id != id)
                outputStream << account.id << ", " << account.full_names << ", " << account.account_number << ", "<< account.account_pin << ", " << account.username << "\n";
            else
                outputStream << id << ", " << accountInfo.full_names << ", " << accountInfo.account_number << ", " << accountInfo.account_pin << ", " << accountInfo.username << "\n";
        }

        remove(get_data_store_path().c_str());
        rename(get_temp_data_store_path().c_str(), get_data_store_path().c_str());

        outputStream.close();
    }

    void store(const Account &account) {
        fstream outputStream;

        outputStream.open(get_data_store_path(), ios::out | ios::app);

        outputStream << next_id() << ", " << account.full_names << ", " << account.account_number << ", " << account.account_pin << ", " << account.username << "\n";
    }

    vector<Account> read() {
        vector<Account> accounts;
        fstream fin;

        fin.open(get_data_store_path(), ios::in);

        string line;

        while (getline(fin, line)) {
            std::stringstream ss(line);
            Account account = from_line(line);

            accounts.push_back(account);
        }

        return accounts;
    }

    Account find_by_id(int id) {
        Account account;
        account.id = -1;

        fstream fin;

        fin.open(get_data_store_path(), ios::in);

        string line;

        while (getline(fin, line))
            if (from_line(line).id == id) {
                account = from_line(line);

                return account;
            }

        return account;
    }

    void delete_by_id(int id) {
        Account existingAccount = find_by_id(id);
        if (existingAccount.id == -1) {
            cout << "User not available in the system";
        }

        vector<Account> previousAccounts = read();

        fstream outputStream;

        outputStream.open(get_temp_data_store_path(), ios::out | ios::app);

        for (const Account &account: previousAccounts)
            if (account.id != id)
                outputStream << account.id << ", " << account.full_names << ", " << account.account_number << ", " << account.account_pin << ", " << account.username << "\n";

        remove(get_data_store_path().c_str());
        rename(get_temp_data_store_path().c_str(), get_data_store_path().c_str());

        outputStream.close();
    }

private:
    static Account from_line(const string &line) {
        Account account;

        std::stringstream ss(line);
        int k = 0;
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');

            if (k == 0) account.id = stoi(substr);
            else if (k == 1) account.full_names = substr;
            else if (k == 2) account.account_number = substr;
            else if (k == 3) account.account_pin = substr;
            else if (k == 4) account.username = substr;

            k++;
        }

        return account;
    }
};
