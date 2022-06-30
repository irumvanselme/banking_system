//
// Created by anselme on 6/30/22.
//

#include "../utils/Service.cpp"

class TransactionService : Service {
public:
    explicit TransactionService() : Service("transactions") {}

    void store(const Transaction &transaction) {
        fstream outputStream;

        outputStream.open(get_data_store_path(), ios::out | ios::app);

        outputStream << next_id() << ", " << transaction.account_id << ", " << transaction.branch_id << ", " << transaction.amount << ", " << transaction.transactionType << "\n";
    }

    vector<Transaction> read() {
        vector<Transaction> transactions;
        fstream fin;

        fin.open(get_data_store_path(), ios::in);

        string line;

        while (getline(fin, line)) {
            std::stringstream ss(line);
            Transaction account = from_line(line);

            transactions.push_back(account);
        }

        return transactions;
    }

    Transaction find_by_id(int id) {
        Transaction transaction{};
        transaction.id = -1;

        fstream fin;

        fin.open(get_data_store_path(), ios::in);

        string line;

        while (getline(fin, line)) {
            if (from_line(line).id == id) {
                transaction = from_line(line);

                return transaction;
            }
        }

        return transaction;
    }

    void delete_by_id(int id) {
        Transaction existingTransaction = find_by_id(id);
        if (existingTransaction.id == -1) {
            cout << "User not available in the system";
        }

        vector<Transaction> previousTransactions = read();

        fstream outputStream;

        outputStream.open(get_temp_data_store_path(), ios::out | ios::app);

        int _id = 1;
        for (const Transaction &transaction: previousTransactions) {
            if (transaction.id != id) {
                outputStream << _id << ", " << transaction.account_id << ", " << transaction.branch_id << ", " << transaction.amount << ", " << transaction.transactionType << "\n";

                _id++;
            }
        }

        remove(get_data_store_path().c_str());
        rename(get_temp_data_store_path().c_str(), get_data_store_path().c_str());

        outputStream.close();
    }

    void update_by_id(int id, Transaction transactionInfo){

        Transaction existingTransaction = find_by_id(id);
        if (existingTransaction.id == -1) {
            cout << "User not available in the system";
        }

        vector<Transaction> previousTransactions  = read();

        fstream outputStream;

        outputStream.open(get_temp_data_store_path(), ios::out | ios::app);

        int _id = 1;
        for (const Transaction &transaction: previousTransactions) {
            if (transaction.id != id) {
                outputStream << _id << ", " << transaction.account_id << ", " << transaction.branch_id << ", " << transaction.amount << ", " << transaction.transactionType << "\n";
            } else {
                outputStream << _id << ", " << transactionInfo.account_id << ", " << transactionInfo.branch_id << ", " << transactionInfo.amount << ", " << transactionInfo.transactionType << "\n";
            }

            _id++;
        }

        remove(get_data_store_path().c_str());
        rename(get_temp_data_store_path().c_str(), get_data_store_path().c_str());

        outputStream.close();
    }

private:
    static Transaction from_line(const string &line) {
        Transaction transaction{};

        std::stringstream ss(line);
        int k = 0;
        for (string rowElement; ss >> rowElement;) {
            if (rowElement[rowElement.length() - 1] == ',')
                rowElement.pop_back();

            if (k == 0) transaction.id = stoi(rowElement);
            else if (k == 1) transaction.account_id = stoi(rowElement);
            else if (k == 2) transaction.branch_id = stoi(rowElement);
            else if (k == 3) transaction.amount = stod(rowElement);
            else if (k == 4) transaction.transactionType = (ETransactionType) stoi(rowElement);

            k++;
        }

        return transaction;
    }
};