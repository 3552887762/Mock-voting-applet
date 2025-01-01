#ifndef VOTER_REGISTRATION_HPP
#define VOTER_REGISTRATION_HPP

#include "Voter.hpp"
#include <string>

// 简单身份证号码验证函数
bool validateIDCard(const std::string& idCard);

// 简单的联系方式验证函数
bool validateContact(const std::string& contact);

// 检查用户名是否唯一
bool isUsernameUnique(const std::string& username);

// 保存选民信息到文件
void saveVoterToFile(const Voter& voter);

// 选民注册处理函数
void handleVoterRegistration();

#endif // VOTER_REGISTRATION_HPP
