#include "Login.hpp"
#include "Admin.hpp"
#include "votermenu.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <Windows.h>  
#include "main.hpp"
#include "adminmenu.hpp"
#include "voter.hpp"
#include "votinginfo.hpp"
using namespace std;



void handleAdminLogin(vector<Candidate>& candidates,VotingInfo& votingInfo) {
    vector<Admin> admins;  // 用于存储所有管理员信息
    const string adminFile = "admin.txt";  // 假设管理员信息保存在 admin.txt 文件中

    // 从文件读取管理员信息
    if (!Admin::loadAdminsFromFile(adminFile, admins)) {
        cout << "读取管理员信息失败，系统无法进行登录验证！\n";
        return;
    }

    int failedAttempts = 0;  // 记录登录失败次数
    while (true) {
        string adminName, adminPassword;
        cout << "请输入管理员用户名: ";
        cin >> adminName;
        cout << "请输入管理员密码: ";
        cin >> adminPassword;

        bool isValid = false;

        // 遍历所有管理员，检查用户名和密码是否匹配
        for (const auto& admin : admins) {
            if (admin.validateLogin(adminName, adminPassword)) {
                isValid = true;
                break;
            }
        }

        // 如果匹配，登录成功
        if (isValid) {
            cout << "管理员登录成功！\n";
            system("pause");
          handleAdminMenu(candidates, votingInfo);
            break;  // 登录成功后退出循环
        }
        else {
            cout << "管理员登录失败，用户名或密码错误。\n";
            failedAttempts++;

            if (failedAttempts >= 3) {
                cout << "连续登录失败3次，系统正在休眠30秒...\n";
                Sleep(30000);  // Windows休眠30秒
            }
        }
    }
}

// 读取选民信息
bool loadVoterFromFile(const std::string& username, Voter& voter) {
    std::ifstream file("voters.txt");
    if (!file.is_open()) {
        std::cout << "无法打开选民信息文件！\n";
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fileUsername, filePasswordHash, fileName, fileIdCardHash, fileContact;
        int fileVotingRights;  // 用于读取投票权（1或0）

        // 读取每行中的数据
        ss >> fileUsername >> filePasswordHash >> fileName >> fileIdCardHash >> fileContact >> fileVotingRights;

        if (fileUsername == username) {
            // 将文件中的数据读取到 Voter 对象
            voter = Voter(fileUsername, filePasswordHash, fileName, fileIdCardHash, fileContact, fileVotingRights == 1);
            return true;
        }
    }
    return false; // 未找到该用户名
}

void handleVoterLogin(vector<Candidate>& candidates, VotingInfo& votingInfo) {
    std::string username, password;
    int loginAttempts = 0;

    while (loginAttempts < 3) {
        std::cout << "请输入选民用户名: ";
        std::cin >> username;

        std::cout << "请输入选民密码: ";
        std::cin >> password;

        // 从文件中加载选民信息
        Voter voter("", "", "", "", "",false); // 空的Voter对象
        if (loadVoterFromFile(username, voter)) {
            // 如果找到选民，验证密码
            if (voter.validatePassword(password)) {
                std::cout << "选民登录成功！\n";
                system("pause");
               handlevoter(candidates,voter, votingInfo);
                break; 
            }
            else {
                std::cout << "密码错误，请重新输入。\n";
            }
        }
        else {
            std::cout << "用户名不存在，请重新输入。\n";
        }

        loginAttempts++;
        if (loginAttempts >= 3) {
            std::cout << "连续登录失败3次，系统正在休眠30秒...\n";
            Sleep(30000);  // Windows休眠30秒
            loginAttempts = 0; // 重置尝试次数
        }
    }
}