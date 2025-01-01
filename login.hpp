#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <string>
#include "Voter.hpp"
#include "Candidate.hpp"
#include "VotingInfo.hpp"
void handleVoterLogin(vector<Candidate>& candidates,  VotingInfo& votingInfo);
void handleAdminLogin(vector<Candidate>& candidates,VotingInfo& votingInfo);  // 管理员登录处理函数
void showAdminMenu();  // 假设您有一个显示管理员菜单的函数
#endif // LOGIN_HPP
