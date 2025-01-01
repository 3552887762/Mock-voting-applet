#ifndef ADMINMENU_HPP
#define ADMINMENU_HPP

#include <vector>
#include "Candidate.hpp"  // ��ѡ������
#include "VotingInfo.hpp" // ͶƱ��Ϣ��
#include "Voter.hpp"      // ͶƱ����
void loadVotersFromFile(const string& filename, vector<Voter>& voters);
void handleAdminMenu(vector<Candidate>& candidates, VotingInfo& votingInfo);
void manageVoters(vector<Voter>& voters);
// ��ʾ����Ա�����˵�
void showAdminMenu();


// ����ͶƱʱ��
void setVotingTime(VotingInfo& votingInfo);

// ��ѯͶƱ���
void showVotingResults(const vector<Candidate>& candidates);
void modifyVoterInFile1(const Voter& voter);
#endif // ADMINMENU_HPP
