//
// Created by anselme on 6/30/22.
//

#include "../utils/Service.cpp"

class BranchService : Service {
public:
    explicit BranchService() : Service("branches") {}

    void store(const Branch &branch) {
        fstream outputStream;

        outputStream.open(get_data_store_path(), ios::out | ios::app);

        outputStream << next_id() << ", " << branch.name << "\n";
    }


    vector<Branch> read() {
        vector<Branch> branches;
        fstream fin;

        fin.open(get_data_store_path(), ios::in);

        string line;

        while (getline(fin, line)) {
            std::stringstream ss(line);
            Branch account = from_line(line);

            branches.push_back(account);
        }

        return branches;
    }

    Branch find_by_id(int id) {
        Branch branch{};
        branch.id = -1;

        fstream fin;

        fin.open(get_data_store_path(), ios::in);

        string line;

        while (getline(fin, line))
            if (from_line(line).id == id) {
                branch = from_line(line);

                return branch;
            }

        return branch;
    }

    void delete_by_id(int id) {
        Branch existingBranch = find_by_id(id);

        if (existingBranch.id == -1) {
            cout << "User not available in the system";
        }

        vector<Branch> previousBranches = read();

        fstream outputStream;

        outputStream.open(get_temp_data_store_path(), ios::out | ios::app);

        for (const Branch &branch: previousBranches)
            if (branch.id != id)
                outputStream << branch.id << ", " << branch.name << "\n";

        remove(get_data_store_path().c_str());
        rename(get_temp_data_store_path().c_str(), get_data_store_path().c_str());

        outputStream.close();
    }

    void update_by_id(int id, Branch branchInfo) {

        Branch existingBranch = find_by_id(id);
        if (existingBranch.id == -1) {
            cout << "User not available in the system";
        }

        vector<Branch> previousBranches = read();

        fstream outputStream;

        outputStream.open(get_temp_data_store_path(), ios::out | ios::app);

        for (const Branch &branch: previousBranches)
            if (branch.id != id)
                outputStream << branch.id << ", " << branch.name << "\n";
            else
                outputStream << id << ", " << branchInfo.name << "\n";

        remove(get_data_store_path().c_str());
        rename(get_temp_data_store_path().c_str(), get_data_store_path().c_str());

        outputStream.close();
    }

private:
    static Branch from_line(const string &line) {
        Branch branch;

        std::stringstream ss(line);
        int k = 0;
        while (ss.good()) {
            string substr;

            getline(ss, substr, ',');

            if (k == 0) branch.id = stoi(substr);
            else if (k == 1) branch.name = substr;

            k++;

        }

        return branch;
    }
};