#include "voter_registration.hpp"
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

// 简单身份证号码验证函数
bool validateIDCard(const std::string& idCard) {
    return idCard.length() == 18 && idCard.find_first_not_of("0123456789") == std::string::npos;
}

// 简单的联系方式验证函数
bool validateContact(const std::string& contact) {
    if (contact.length() == 11 && contact.find_first_not_of("0123456789") == std::string::npos) {
        return true;  // 手机号码验证
    }
    return false;
}

// 检查用户名是否唯一
bool isUsernameUnique(const std::string& username) {
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
    std::ofstream file("voters.txt", std::ios::app);  

    cout << voter.hasVotingRights() << endl;
    if (file.is_open()) {
        // 保存选民信息：用户名 密码哈希 姓名 身份证哈希 联系方式
        file << voter.getUsername() << " "
            << voter.getPasswordHash() << " "
            << voter.getName() << " "
            << voter.getIdCard() << " "
            << voter.getContact() << " "
            << (voter.hasVotingRights() ? 1 : 0)  // 转换投票权为 1 或 0
            << "\n";
        file.close();
        std::cout << "选民信息保存成功！\n";
    }
    else {
        std::cout << "无法打开文件保存选民信息！\n";
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

    cout << "请输入密码(密码长度必须至少为8个字符): ";
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

    cout << "请输入手机号码：";
    cin >> contact;

    // 验证联系方式格式
    if (!validateContact(contact)) {
        cout << "联系方式格式不正确。\n";
        return;
    }

    // 创建选民对象
    Voter newVoter(username, password, name, idCard, contact,true);

    // 保存选民信息到文件
    saveVoterToFile(newVoter);

    cout << "注册成功！欢迎 " << name << "，您的用户名为 " << username << "。\n";
     
}
