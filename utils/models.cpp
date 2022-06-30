//
// Created by anselme on 17/06/22.
//
#include "iostream"

#pragma once

using namespace std;

class Model {};

// ENUMS
enum ETransactionType {
    WITHDRAW, DEPOSE
};

// Models
class Branch: Model {
public:
    int id;
    std::string name;
};

class Account: Model {
public:
    int id;
    std::string full_names;
    std::string account_number;
    std::string username;
    std::string account_pin;
};

class Transaction : Model {
public:
    int id;
    int account_id;
    int branch_id;
    double amount;
    ETransactionType transactionType;
};