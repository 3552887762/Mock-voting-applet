#include "Voter.hpp"
#include <functional>  // for std::hash

// ���캯��
Voter::Voter(std::string username, std::string password, std::string name, std::string idCard, std::string contact, bool hasVotingRight)
    : username(username), passwordHash(password), name(name), idCard(idCard), contact(contact),hasVotingRight(hasVotingRight) {}

// ��ȡ�û���
std::string Voter::getUsername() const {
    return username;
}
std::string Voter::getName() const {
    return name;
}
// ��ȡ�����ϣ
std::string Voter::getPasswordHash() const {
    return passwordHash;
}

// ��ȡ���֤��
std::string Voter::getIdCard() const {
    return idCard;
}

// ��ȡ��ϵ��ʽ
std::string Voter::getContact() const {
    return contact;
}

// ��ϣ���ܺ�����ʹ�ü򵥵� XOR ���㣩
std::string Voter::hashPassword(const std::string& input) {
    std::string encrypted = input;
    for (char& ch : encrypted) {
        ch ^= 123;  // ʹ��������
    }
    return encrypted;
}
// ��֤����
bool Voter::validatePassword(const std::string& password) const
{
    return getPasswordHash() == password;
}