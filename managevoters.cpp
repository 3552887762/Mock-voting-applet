#include "manageVoters.hpp"

// 显示所有选民的基本信息
void showAllVoters(const std::vector<Voter>& voters) {
    std::cout << "所有选民信息:\n";
    for (const auto& voter : voters) {
        std::cout << "用户名: " << voter.getUsername() << "\n";
        std::cout << "姓名: " << voter.getName() << "\n";
        std::cout << "身份证号: " << voter.getIdCard() << "\n";
        std::cout << "联系方式: " << voter.getContact() << "\n";
        std::cout << "投票权限: " << (voter.hasVotingRights() ? "有" : "没有") << "\n";
        std::cout << "---------------------------\n";
    }
}

// 修改选民联系方式
void modifyVoterContact(std::vector<Voter>& voters, const std::string& username) {
    std::string newContact;
    std::cout << "请输入新的联系方式: ";
    std::cin >> newContact;
    bool flag = false;
    for (auto& voter : voters) {
        if (voter.getUsername() == username) {
            voter.setcontact(newContact);
            flag = true;
            std::cout << "联系方式已更新。\n";
            break;
        }
    }
    if (!flag) {
        std::cout << "未找到该选民。\n";
    }
}

// 修改选民投票权限
void modifyVoterVotingRights(std::vector<Voter>& voters, const std::string& username) {
    bool newVotingRights;
    std::cout << "请输入新的投票权限 (1: 允许投票, 0: 禁止投票): ";
    std::cin >> newVotingRights;
    bool flag = false;
    for (auto& voter : voters) {
        if (voter.getUsername() == username) {
            voter.setVotingRights(newVotingRights);
            flag = true;
            std::cout << "投票权限已更新。\n";
            break;
        }
    }
    if (!flag) {
        std::cout << "未找到该选民。\n";
    }
}
