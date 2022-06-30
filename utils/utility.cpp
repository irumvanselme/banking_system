//
// Created by anselme on 6/30/22.
//

#include <utility>

#include "../utils/headers.h"

#include "../services/account-service.cpp"
#include "../services/transaction-service.cpp"
#include "../services/branch-service.cpp"

class Utility {
private:
    AccountService accountService;
    BranchService branchService;
    TransactionService transactionService;

public:
    void test() {
        cout << "Hello world " << endl;
    }

    void save_branch(string name) {
        Branch branch;
        branch.name = std::move(name);
        branchService.store(branch);
    }

    void save_account(string full_names, string username, string account_pin){
        Account account;
        account.full_names = std::move(full_names);
        account.username = std::move(username);
        account.account_pin = std::move(account_pin);
        account.account_number = generate_account_number();

        accountService.store(account);
    }

private:
    string generate_account_number(){
        return "12345";
    }
};