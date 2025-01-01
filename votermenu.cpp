#include <iostream>
#include "VoterMenu.hpp"  // 包含菜单显示和选民操作的头文件
#include "VotingInfo.cpp"  // 包含投票信息类头文件
#include "Candidate.hpp"  // 包含参选对象类头文件
#include <vector>
#include <ctime>
#include <string>
#include "voter_registration.hpp"
using namespace std;

void handlevoter(vector<Candidate>& candidates,Voter& voter, VotingInfo& votingInfo) {
    int voterChoice;
    time_t now = time(0);  // 在循环开始时初始化now

    while (true) {
        showVoterMenu(); // 显示选民菜单
        cout << "请输入您的选择: ";
        cin >> voterChoice;

        switch (voterChoice) {
        case 1:
            // 投票信息查询
            showVotingInformation(candidates, votingInfo);
            system("pause");
            break;
        case 2:
            // 投票操作
            handleVoting(candidates,voter,votingInfo);
            system("pause");
            break;
        case 3:
            return;
        default:
            cout << "无效的选项，请重新选择。\n";
            break;
        }
    }
}



// 显示选民菜单
void showVoterMenu() {
    system("cls"); // Windows 使用 system("cls");
    cout << "=========================\n";
    cout << " 选民操作菜单\n";
    cout << "=========================\n";
    cout << "1. 投票信息查询\n";
    cout << "2. 投票\n";
    cout << "3. 返回主菜单\n";
    cout << "=========================\n";
}

// 投票信息查询函数
void showVotingInformation(const std::vector<Candidate>& candidates, const VotingInfo& votingInfo) {
    // 输出投票信息
     // 获取并格式化投票开始时间和结束时间
    time_t startTime = votingInfo.getStartTime();
    time_t endTime = votingInfo.getEndTime();

    // 使用ctime将time_t转换为字符串
    char startStr[26], endStr[26];
    ctime_s(startStr, sizeof(startStr), &startTime);
    ctime_s(endStr, sizeof(endStr), &endTime);
    // 输出投票信息
    cout << "投票开始时间: " << startStr;
    cout << "投票结束时间: " << endStr;
    cout << "已投票人数: " << votingInfo.getTotalVotes() << "/" << votingInfo.getTotalVoters() << endl;
    cout << "投票状态: " << votingInfo.getVotingStatus() << endl;
    cout << "\n参选对象信息:\n";
    for (const auto& candidate : candidates) {
        if (candidate.getIsActive()) {
            cout << "参选编号: " << candidate.getId() << "\n";
            cout << "姓名: " << candidate.getName() << "\n";
            cout << "参选类别: " << candidate.getCategory() << "\n";
            cout << "简介: " << candidate.getDescription() << "\n";
            cout << "当前得票数: " << candidate.getVoteCount() << "票\n";
            cout << "----------------------------------\n";
        }
    }
}

// 投票操作函数
void handleVoting(vector<Candidate>& candidates,Voter& voter, VotingInfo& votingInfo) {
    time_t now = time(0);
    if (now < votingInfo.getStartTime() || now > votingInfo.getEndTime()) {
        cout << "当前不在投票时间范围内，无法投票。\n";
        return;
    }

    if (!voter.hasVotingRights()) {
        cout << "您没有投票资格，无法进行投票。\n";
        return;
    }


    int selectedOption;
    cout << "请输入您选择的参选对象编号（1~" << candidates.size() << "）: ";
    cin >> selectedOption;


    if (selectedOption < 1 || selectedOption > candidates.size()) {
        cout << "无效选择，请重新选择。\n";
        return;
    }
    bool finded = false;
    for (auto& candidate : candidates) {
        if (candidate.getId() == selectedOption && candidate.getIsActive()) {
            cout << "您已成功为参选对象 " << candidate.getName() << " 投票！\n";
            finded = true;
            candidate.incrementVoteCount();
        }
    }
    if (!finded) {
        cout << "无效选择，请重新选择。\n";
        return;
    }

    voter.setVotingRights(false);
    

    // 6. 保存投票信息到文件
    modifyVoterInFile(voter);  // 修改选民文件中的投票状态
    saveVotingData(candidates, "candidates.txt");  // 保存参选对象数据
    votingInfo.incrementTotalVotes();  // 增加总投票数
    // 提示操作成功
    cout << "您的投票已成功提交，感谢您的参与！\n";
}

void modifyVoterInFile(const Voter& voter) {
    std::ifstream infile("voters.txt");
    if (!infile.is_open()) {
        std::cout << "无法打开选民文件进行修改！\n";
        return;
    }

    std::vector<Voter> voters;
    std::string line;
    while (getline(infile, line)) {
        std::stringstream ss(line);
        std::string username, passwordHash, name, idCard, contact;
        bool hasVotingRights;

        ss >> username >> passwordHash >> name >> idCard >> contact >> hasVotingRights;

        // 如果用户名匹配，修改选民的投票权状态
        if (username == voter.getUsername()) {
            voters.push_back(Voter(username, passwordHash, name, idCard, contact, false));  // 修改投票权为false
        }
        else {
            voters.push_back(Voter(username, passwordHash, name, idCard, contact, hasVotingRights));
        }
    }
    infile.close();

    // 写回修改后的选民信息
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

// 保存参选对象数据到文件
void saveVotingData(const vector<Candidate>& candidates, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "无法打开文件保存数据！\n";
        return;
    }

    for (const auto& candidate : candidates) {
        file << candidate.getId() << " "
            << candidate.getName() << " "
            << candidate.getCategory() << " "
            << candidate.getDescription() << " "
            << candidate.getVoteCount() << "\n";
    }

    file.close();
}



