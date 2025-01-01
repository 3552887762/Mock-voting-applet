#ifndef MANAGEVOTERS_HPP
#define MANAGEVOTERS_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Voter.hpp" // ����Voter��

// ��ʾѡ��Ļ�����Ϣ
void showAllVoters(const std::vector<Voter>& voters);

// �޸�ѡ����ϵ��ʽ
void modifyVoterContact(std::vector<Voter>& voters, const std::string& username);

// �޸�ѡ��ͶƱȨ��
void modifyVoterVotingRights(std::vector<Voter>& voters, const std::string& username);

#endif // MANAGEVOTERS_HPP
