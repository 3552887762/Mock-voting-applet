
#ifndef VOTERMENU_HPP
#define VOTERMENU_HPP
#include "main.hpp"
#include "voter.hpp"
#include "candidate.hpp"
#include "votinginfo.hpp"
// 显示选民操作菜单
void handlevoter(vector<Candidate>& candidates,Voter& voter);
void showVoterMenu();
void handlevoter(vector<Candidate>& candidates, Voter& voter, VotingInfo& votingInfo);
// 显示投票信息
void showVotingInformation(const std::vector<Candidate>& candidates, const VotingInfo& votingInfo);

// 处理投票操作
void handleVoting(vector<Candidate>& candidates, Voter& voter, VotingInfo& votingInfo);
// 保存参选对象数据到文件
void saveVotingData(const vector<Candidate>& candidates, const string& filename);
void saveVoterData(const Voter& voter, const string& filename);
void modifyVoterInFile(const Voter& voter);
#endif // VOTERMENU_HPP
