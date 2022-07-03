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

        outputStream << next_id() << ", " << transaction.account_id << ", " << transaction.branch_id << ", "  << transaction.amount << ", " << transaction.transactionType << "\n";
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

        while (getline(fin, line))
            if (from_line(line).id == id)
                return from_line(line);

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

        for (const Transaction &transaction: previousTransactions)
            if (transaction.id != id)
                outputStream << transaction.id << ", " << transaction.account_id << ", " << transaction.branch_id << ", " << transaction.amount << ", " << transaction.transactionType << "\n";


        remove(get_data_store_path().c_str());
        rename(get_temp_data_store_path().c_str(), get_data_store_path().c_str());

        outputStream.close();
    }

    void update_by_id(int id, Transaction transactionInfo) {

        Transaction existingTransaction = find_by_id(id);
        if (existingTransaction.id == -1)
            cout << "User not available in the system";

        vector<Transaction> previousTransactions = read();

        fstream outputStream;

        outputStream.open(get_temp_data_store_path(), ios::out | ios::app);

        for (const Transaction &transaction: previousTransactions)
            if (transaction.id != id)
                outputStream << transaction.id << ", " << transaction.account_id << ", " << transaction.branch_id << ", " << transaction.amount << ", " << transaction.transactionType << "\n";
            else
                outputStream << id << ", " << transactionInfo.account_id << ", " << transactionInfo.branch_id << ", " << transactionInfo.amount << ", " << transactionInfo.transactionType << "\n";

        remove(get_data_store_path().c_str());
        rename(get_temp_data_store_path().c_str(), get_data_store_path().c_str());

        outputStream.close();
    }

private:
    static Transaction from_line(const string &line) {
        Transaction transaction{};

        std::stringstream ss(line);
        int k = 0;
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');

            if (k == 0) transaction.id = stoi(substr);
            else if (k == 1) transaction.account_id = stoi(substr);
            else if (k == 2) transaction.branch_id = stoi(substr);
            else if (k == 3) transaction.amount = stod(substr);
            else if (k == 4) transaction.transactionType = (ETransactionType) stoi(substr);

            k++;
        }

        return transaction;
    }
};