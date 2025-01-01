
#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <string>
#include <vector>

class Admin {
private:
    std::string username;
    std::string password;

public:
    // ���캯��
    Admin(const std::string& username, const std::string& password)
        : username(username), password(password) {}

    // ��ȡ�û���
    std::string getUsername() const {
        return username;
    }

    // ��ȡ����
    std::string getPassword() const {
        return password;
    }

    // ��̬��������ȡ���й���Ա��Ϣ
    static bool loadAdminsFromFile(const std::string& filename, std::vector<Admin>& admins);

    // ��֤�û����������Ƿ�ƥ��
    bool validateLogin(const std::string& inputUsername, const std::string& inputPassword) const {
        return username == inputUsername && password == inputPassword;
    }
};

#endif 
