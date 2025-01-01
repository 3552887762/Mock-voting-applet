#ifndef MANAGEVOTERS_HPP
#define MANAGEVOTERS_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Voter.hpp" // 引入Voter类

// 显示选民的基本信息
void showAllVoters(const std::vector<Voter>& voters);

// 修改选民联系方式
void modifyVoterContact(std::vector<Voter>& voters, const std::string& username);

// 修改选民投票权限
void modifyVoterVotingRights(std::vector<Voter>& voters, const std::string& username);

#endif // MANAGEVOTERS_HPP
