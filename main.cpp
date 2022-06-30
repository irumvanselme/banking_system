#include "./utils/utility.cpp"

int main() {
    Utility utility;

    string branch_name;
    cout << "Enter the branch name :-";

    getline(cin, branch_name);

    utility.save_branch(branch_name);

    return 0;
}
