#ifndef MAIN_DEFINED
#define MAIN_DEFINED
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "VotingInfo.hpp"
#include "Candidate.hpp"
using namespace std;
// 显示主菜单
void showMainMenu();
// 创建VotingInfo对象的函数
VotingInfo createVotingInfo(const std::vector<Candidate>& candidates, int totalVoters);
#endif


