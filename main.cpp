#include <iostream>
#include <string>
#include <cstdlib>
#include "voter_registration.hpp"
#include "login.hpp"
#include "main.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "candidate.hpp"
#include "votinginfo.hpp"
void showMainMenu() {
    system("cls"); 
    cout << "=========================\n";
    cout << "    投票小程序菜单\n";
    cout << "=========================\n";
    cout << "1. 选民注册\n";
    cout << "2. 选民登录\n";
    cout << "3. 管理员登录\n";
    cout << "4. 退出系统\n";
    cout << "=========================\n";
}
// 创建VotingInfo对象的函数
VotingInfo createVotingInfo(const std::vector<Candidate>& candidates, int totalVoters) {
    // 获取当前时间（当前时间戳）
    time_t now = time(0);

    // 设置开始时间（假设为当前时间）
    time_t startTime = now;

    // 设置结束时间（假设为当前时间加1小时）
    time_t endTime = now + 3600; // 1小时后

    // 计算已投票人数（所有候选人的得票数总和）
    int totalVotes = 0;
    for (const auto& candidate : candidates) {
        totalVotes += candidate.getVoteCount();
    }

    // 创建并返回VotingInfo对象
    return VotingInfo(startTime, endTime, totalVoters, totalVotes);
}
int main() {
    int totalVoters = 1000; // 总选民数（假设为1000）
    std::vector<Candidate> candidates;

    if (!loadCandidatesFromFile(candidates, "candidates.txt")) {
        std::cout << "没有找到参选对象信息，正在创建新的参选对象。" << std::endl;
    }
    saveCandidatesToFile(candidates, "candidates.txt");
    VotingInfo votingInfo = createVotingInfo(candidates, totalVoters);
    int choice;

    while (true) {
        showMainMenu();
        cout << "请输入您的选择: ";

        string input;
        getline(cin, input);  // 获取用户输入的整行

        // 尝试将输入转为整数并检查是否成功
        stringstream ss(input);
        if (ss >> choice && ss.eof()) {
            // 输入是一个有效的数字
            switch (choice) {
            case 1:
                handleVoterRegistration();
                system("pause");
                break;
            case 2:
                handleVoterLogin(candidates, votingInfo);
                system("pause");
                break;
            case 3:
                handleAdminLogin(candidates, votingInfo);
                system("pause");
                break;
            case 4:
                cout << "退出系统，感谢使用！\n";
                return 0;
            default:
                cout << "无效的选项，请重新选择。\n";
            }
        }
        else {
            cout << "无效输入，请输入数字选项（1~4）!\n";
        }
    }

    return 0;
}




