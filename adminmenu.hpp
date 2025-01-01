#ifndef ADMINMENU_HPP
#define ADMINMENU_HPP

#include <vector>
#include "Candidate.hpp"  // 参选对象类
#include "VotingInfo.hpp" // 投票信息类
#include "Voter.hpp"      // 投票者类
void loadVotersFromFile(const string& filename, vector<Voter>& voters);
void handleAdminMenu(vector<Candidate>& candidates, VotingInfo& votingInfo);
void manageVoters(vector<Voter>& voters);
// 显示管理员操作菜单
void showAdminMenu();


// 设置投票时间
void setVotingTime(VotingInfo& votingInfo);

// 查询投票结果
void showVotingResults(const vector<Candidate>& candidates);
void modifyVoterInFile1(const Voter& voter);
#endif // ADMINMENU_HPP
