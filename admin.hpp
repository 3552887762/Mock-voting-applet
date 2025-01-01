
#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <string>
#include <vector>

class Admin {
private:
    std::string username;
    std::string password;

public:
    // 构造函数
    Admin(const std::string& username, const std::string& password)
        : username(username), password(password) {}

    // 获取用户名
    std::string getUsername() const {
        return username;
    }

    // 获取密码
    std::string getPassword() const {
        return password;
    }

    // 静态函数：读取所有管理员信息
    static bool loadAdminsFromFile(const std::string& filename, std::vector<Admin>& admins);

    // 验证用户名和密码是否匹配
    bool validateLogin(const std::string& inputUsername, const std::string& inputPassword) const {
        return username == inputUsername && password == inputPassword;
    }
};

#endif 
