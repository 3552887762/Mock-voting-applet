#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <string>
#include "Voter.hpp"
#include "Candidate.hpp"
#include "VotingInfo.hpp"
void handleVoterLogin(vector<Candidate>& candidates,  VotingInfo& votingInfo);
void handleAdminLogin(vector<Candidate>& candidates,VotingInfo& votingInfo);  // ����Ա��¼������
void showAdminMenu();  // ��������һ����ʾ����Ա�˵��ĺ���
#endif // LOGIN_HPP
