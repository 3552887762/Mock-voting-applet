#ifndef VOTER_REGISTRATION_HPP
#define VOTER_REGISTRATION_HPP

#include "Voter.hpp"
#include <string>

// �����֤������֤����
bool validateIDCard(const std::string& idCard);

// �򵥵���ϵ��ʽ��֤����
bool validateContact(const std::string& contact);

// ����û����Ƿ�Ψһ
bool isUsernameUnique(const std::string& username);

// ����ѡ����Ϣ���ļ�
void saveVoterToFile(const Voter& voter);

// ѡ��ע�ᴦ����
void handleVoterRegistration();

#endif // VOTER_REGISTRATION_HPP
