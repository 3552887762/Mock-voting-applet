#ifndef MAIN_DEFINED
#define MAIN_DEFINED
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "VotingInfo.hpp"
#include "Candidate.hpp"
using namespace std;
// ��ʾ���˵�
void showMainMenu();
// ����VotingInfo����ĺ���
VotingInfo createVotingInfo(const std::vector<Candidate>& candidates, int totalVoters);
#endif


