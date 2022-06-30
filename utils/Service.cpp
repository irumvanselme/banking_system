#include "headers.h"

#pragma once

class Service {
private:
    std::string filename;

protected:
    string get_data_store_path() {
        return "../store/" + filename + ".csv";
    }

    string get_temp_data_store_path() {
        return "../store/temp__" + filename + ".csv";
    }

public:
    explicit Service(std::string filename) : filename(std::move(filename)) {}

protected:
    int next_id() {
        int next_id = 1;

        fstream fin;
        fin.open(get_data_store_path(), ios::in);

        string line;

        while (getline(fin, line))
            next_id++;

        return next_id;
    }
};