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
        int id = 0;

        fstream file;
        file.open(get_data_store_path(), ios::in);

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id_as_string;
            getline(ss, id_as_string, ',');
            id = stoi(id_as_string);
        }

        file.close();
        return id + 1;
    }
};