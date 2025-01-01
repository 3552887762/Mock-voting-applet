
#ifndef VOTERMENU_HPP
#define VOTERMENU_HPP
#include "main.hpp"
#include "voter.hpp"
#include "candidate.hpp"
#include "votinginfo.hpp"
// ��ʾѡ������˵�
void handlevoter(vector<Candidate>& candidates,Voter& voter);
void showVoterMenu();
void handlevoter(vector<Candidate>& candidates, Voter& voter, VotingInfo& votingInfo);
// ��ʾͶƱ��Ϣ
void showVotingInformation(const std::vector<Candidate>& candidates, const VotingInfo& votingInfo);

// ����ͶƱ����
void handleVoting(vector<Candidate>& candidates, Voter& voter, VotingInfo& votingInfo);
// �����ѡ�������ݵ��ļ�
void saveVotingData(const vector<Candidate>& candidates, const string& filename);
void saveVoterData(const Voter& voter, const string& filename);
void modifyVoterInFile(const Voter& voter);
#endif // VOTERMENU_HPP
