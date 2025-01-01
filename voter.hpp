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
    bool hasVotingRight;  // 表示是否有投票权
public:
    // 构造函数
    Voter(std::string username, std::string password, std::string name, std::string idCard, std::string contact, bool hasVotingRights);
    void setcontact(std::string contact) {
        this->contact = contact;
    }
    // 获取用户名
    std::string getUsername() const;
    std::string getName() const;
    // 获取密码哈希
    std::string getPasswordHash() const;

    // 获取身份证号
    std::string getIdCard() const;

    // 获取联系方式
    std::string getContact() const;
    // 验证密码
    bool validatePassword(const std::string& password) const;
    // 获取投票权状态
    bool hasVotingRights() const { return hasVotingRight; }

    // 设置投票权状态
    void setVotingRights(bool status) { hasVotingRight = status; }

private:
    std::string hashPassword(const std::string& input);
};

#endif // VOTER_HPP
