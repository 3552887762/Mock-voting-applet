#ifndef VOTER_HPP
#define VOTER_HPP

#include <string>
using namespace std;
class Voter {
private:
    std::string username;
    std::string passwordHash;
    std::string name;
    std::string idCard;
    std::string contact;
    bool hasVotingRight;  // ��ʾ�Ƿ���ͶƱȨ
public:
    // ���캯��
    Voter(std::string username, std::string password, std::string name, std::string idCard, std::string contact, bool hasVotingRights);
    void setcontact(std::string contact) {
        this->contact = contact;
    }
    // ��ȡ�û���
    std::string getUsername() const;
    std::string getName() const;
    // ��ȡ�����ϣ
    std::string getPasswordHash() const;

    // ��ȡ���֤��
    std::string getIdCard() const;

    // ��ȡ��ϵ��ʽ
    std::string getContact() const;
    // ��֤����
    bool validatePassword(const std::string& password) const;
    // ��ȡͶƱȨ״̬
    bool hasVotingRights() const { return hasVotingRight; }

    // ����ͶƱȨ״̬
    void setVotingRights(bool status) { hasVotingRight = status; }

private:
    std::string hashPassword(const std::string& input);
};

#endif // VOTER_HPP
