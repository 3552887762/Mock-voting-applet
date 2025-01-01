#include "Admin.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool Admin::loadAdminsFromFile(const std::string& filename, std::vector<Admin>& admins) {
    ifstream file(filename);  
    if (!file.is_open()) {
        cout << "�޷��򿪹���Ա��Ϣ�ļ���\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        ss >> username >> password; 
        admins.emplace_back(username, password);  
    }

    return true;
}
