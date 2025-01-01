#include <iostream>
#include "AdminMenu.hpp"
#include "Candidate.hpp"
#include "VotingInfo.hpp"
#include "Voter.hpp"
#include "managevoters.hpp"
#include "votermenu.hpp"
#include "managecandidate.hpp"
using namespace std;

void handleAdminMenu(vector<Candidate>& candidates, VotingInfo& votingInfo) {
    vector<Voter> voters;
    // 初始化选民信息
    loadVotersFromFile("voters.txt", voters);
    int adminChoice;

    while (true) {
        showAdminMenu();  // 显示管理员菜单
        cout << "请输入您的选择: ";
        cin >> adminChoice;

        switch (adminChoice) {
        case 1:
            manageVoters(voters);  // 管理选民信息
            system("pause");
            break;
        case 2:
             setVotingTime(votingInfo);  // 设置投票时间
             system("pause");
            break;
        case 3:
            showVotingResults(candidates);  // 查询投票结果
            system("pause");
            break;
        case 4:
            handleAdminMenu(candidates);
            system("pause");
            return;  
        case 5:
            return;  // 返回主菜单
        default:
            cout << "无效的选项，请重新选择。\n";
            break;
        }
    }
}
// 读取选民信息并初始化Voter对象
void loadVotersFromFile(const string& filename, vector<Voter>& voters) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "无法打开选民信息文件！\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, passwordHash, name, idCard, contact;
        int hasVotingRightsInt;
        ss >> username >> passwordHash >> name >> idCard >> contact >> hasVotingRightsInt;

        // 将投票权转换为bool值
        bool hasVotingRights = (hasVotingRightsInt == 1);

        // 创建 Voter 对象并添加到 voters 向量中
        voters.push_back(Voter(username, passwordHash, name, idCard, contact, hasVotingRights));
    }

    file.close();
}
void manageVoters(std::vector<Voter>& voters) {
    int choice;
    while (true) {
        system("cls");
        cout << "=========================\n";
        std::cout << " 选民管理菜单:\n";
        cout << "=========================\n";
        std::cout << "1. 查看选民信息\n";
        std::cout << "2. 修改选民联系方式\n";
        std::cout << "3. 修改选民投票权限\n";
        std::cout << "4. 返回\n";
        std::cout << "请输入您的选择: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            showAllVoters(voters); system("pause");  // 查看选民信息
            break;
        case 2:
        {
            std::string username;
            std::cout << "请输入选民用户名: ";
            std::cin >> username;
            modifyVoterContact(voters, username); system("pause");  // 修改选民联系方式
            break;
        }
        case 3:
        {
            std::string username;
            std::cout << "请输入选民用户名: ";
            std::cin >> username;
            modifyVoterVotingRights(voters, username); system("pause");  // 修改选民投票权限
            break;
        }
        case 4:
            return;  // 返回
        default:
            std::cout << "无效的选项，请重新选择。\n";
            break;
        }
        for (const auto& voter : voters) {
            modifyVoterInFile1(voter);
        }
    }
}

void modifyVoterInFile1(const Voter& voter) {
    // 打开选民信息文件进行读取
    std::ifstream infile("voters.txt");
    if (!infile.is_open()) {
        std::cout << "无法打开选民文件进行修改！\n";
        return;
    }

    std::vector<Voter> voters;
    std::string line;

    // 读取文件中的所有选民信息
    while (getline(infile, line)) {
        std::stringstream ss(line);
        std::string username, passwordHash, name, idCard, contact;
        bool hasVotingRights;

        ss >> username >> passwordHash >> name >> idCard >> contact >> hasVotingRights;

        // 如果用户名匹配，更新选民信息
        if (username == voter.getUsername()) {
            // 更新选民信息：保存修改后的投票权限和联系方式
            voters.push_back(Voter(username, passwordHash, name, idCard, voter.getContact(), voter.hasVotingRights()));
        }
        else {
            // 对于不需要更新的选民，保持原信息
            voters.push_back(Voter(username, passwordHash, name, idCard, contact, hasVotingRights));
        }
    }
    infile.close();

    // 重新写入修改后的选民信息
    std::ofstream outfile("voters.txt");
    if (!outfile.is_open()) {
        std::cout << "无法重新保存选民文件！\n";
        return;
    }

    // 写入所有选民数据
    for (const auto& voterItem : voters) {
        outfile << voterItem.getUsername() << " "
            << voterItem.getPasswordHash() << " "
            << voterItem.getName() << " "
            << voterItem.getIdCard() << " "
            << voterItem.getContact() << " "
            << (voterItem.hasVotingRights() ? 1 : 0) << "\n";
    }

    outfile.close();
    std::cout << "选民信息已更新！\n";
}

// 显示管理员操作菜单
void showAdminMenu() {
    system("cls");  
    cout << "=========================\n";
    cout << " 管理员操作菜单\n";
    cout << "=========================\n";
    cout << "1. 管理选民信息\n";
    cout << "2. 设置投票时间\n";
    cout << "3. 查询投票结果\n";
    cout << "4. 修改参选对象信息\n";
    cout << "5. 返回主菜单\n";
    cout << "=========================\n";
}

void showVotingResults(const vector<Candidate>& candidates) {
    for (const auto& candidate : candidates) {
        cout << "参选人: " << candidate.getName() << ", 票数: " << candidate.getVoteCount() << endl;
    }

}

void setVotingTime(VotingInfo& votingInfo) {
    cout << "延长小时数："<< endl;
    int hours;
    cin >> hours;
    votingInfo.addendTime(hours*3600);
    cout << "投票时间已延长" << hours << "小时" << endl;
}