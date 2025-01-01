#include <iostream>
#include <fstream>
#include <string>
#include <functional>  // for std::hash

using namespace std;

class Voter {
private:
    string username;
    string passwordHash;
    string name;
    string idCardHash;
    string contact;

public:
    // 构造函数
    Voter(string username, string password, string name, string idCard, string contact)
        : username(username), passwordHash(hashPassword(password)), name(name), idCardHash(hashPassword(idCard)), contact(contact) {}

    // 获取用户名
    string getUsername() const {
        return username;
    }

    // 获取密码哈希
    string getPasswordHash() const {
        return passwordHash;
    }

    // 获取身份证号哈希
    string getIdCardHash() const {
        return idCardHash;
    }

    // 获取联系方式
    string getContact() const {
        return contact;
    }

private:
    // 哈希加密函数（使用简单的 XOR 运算）
    string hashPassword(const string& input) {
        string encrypted = input;
        for (char& ch : encrypted) {
            ch ^= 123;  // 使用异或操作
        }
        return encrypted;
    }
};

// 简单身份证号码验证函数
bool validateIDCard(const string& idCard) {
    return idCard.length() == 18 && idCard.find_first_not_of("0123456789") == string::npos;
}

// 简单的联系方式验证函数
bool validateContact(const string& contact) {
    // 假设手机号码是11位数字，电子邮箱包含 "@" 和 "."
    if (contact.length() == 11 && contact.find_first_not_of("0123456789") == string::npos) {
        return true;  // 手机号码验证
    }
    if (contact.find('@') != string::npos && contact.find('.') != string::npos) {
        return true;  // 简单电子邮箱验证
    }
    return false;
}

// 检查用户名是否唯一
bool isUsernameUnique(const string& username) {
    ifstream file("voters.txt");
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(' ');  // 假设用户名和密码之间用空格分开
        string existingUsername = line.substr(0, pos);
        if (existingUsername == username) {
            return false;  // 找到重复的用户名
        }
    }
    return true;
}

// 保存选民信息到文件
void saveVoterToFile(const Voter& voter) {
    ofstream file("voters.txt", ios::app);
    if (file.is_open()) {
        file << voter.getUsername() << " "
            << voter.getPasswordHash() << " "
            << voter.getContact() << endl;
        file.close();
    }
    else {
        cout << "无法打开文件保存选民信息！\n";
    }
}

// 选民注册处理函数
void handleVoterRegistration() {
    string username, password, name, idCard, contact;

    cout << "请输入用户名: ";
    cin >> username;

    // 检查用户名是否唯一
    if (!isUsernameUnique(username)) {
        cout << "该用户名已被注册，请选择其他用户名。\n";
        return;
    }

    cout << "请输入密码: ";
    cin >> password;

    // 验证密码强度（例如，至少8个字符，包含数字和字母）
    if (password.length() < 8) {
        cout << "密码长度必须至少为8个字符。\n";
        return;
    }

    cout << "请输入姓名: ";
    cin >> name;

    cout << "请输入身份证号码（18位）：";
    cin >> idCard;

    // 验证身份证号码格式
    if (!validateIDCard(idCard)) {
        cout << "身份证号码格式不正确，应为18位数字。\n";
        return;
    }

    cout << "请输入联系方式（手机号码或电子邮箱）：";
    cin >> contact;

    // 验证联系方式格式
    if (!validateContact(contact)) {
        cout << "联系方式格式不正确。\n";
        return;
    }

    // 创建选民对象
    Voter newVoter(username, password, name, idCard, contact);

    // 保存选民信息到文件
    saveVoterToFile(newVoter);

    cout << "注册成功！欢迎 " << name << "，您的用户名为 " << username << "。\n";
}

