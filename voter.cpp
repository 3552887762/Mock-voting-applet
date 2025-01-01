#include "Voter.hpp"
#include <functional>  // for std::hash

// 构造函数
Voter::Voter(std::string username, std::string password, std::string name, std::string idCard, std::string contact, bool hasVotingRight)
    : username(username), passwordHash(password), name(name), idCard(idCard), contact(contact),hasVotingRight(hasVotingRight) {}

// 获取用户名
std::string Voter::getUsername() const {
    return username;
}
std::string Voter::getName() const {
    return name;
}
// 获取密码哈希
std::string Voter::getPasswordHash() const {
    return passwordHash;
}

// 获取身份证号
std::string Voter::getIdCard() const {
    return idCard;
}

// 获取联系方式
std::string Voter::getContact() const {
    return contact;
}

// 哈希加密函数（使用简单的 XOR 运算）
std::string Voter::hashPassword(const std::string& input) {
    std::string encrypted = input;
    for (char& ch : encrypted) {
        ch ^= 123;  // 使用异或操作
    }
    return encrypted;
}
// 验证密码
bool Voter::validatePassword(const std::string& password) const
{
    return getPasswordHash() == password;
}