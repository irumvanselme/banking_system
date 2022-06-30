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
};