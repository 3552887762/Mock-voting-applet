#include <iostream>
#include <fstream>
#include <string>
#include <functional>  // for std::hash

using namespace std;

class Voter {
private:
    string username;
    string passwordHash;
    string name;
    string idCardHash;
    string contact;

public:
    // ���캯��
    Voter(string username, string password, string name, string idCard, string contact)
        : username(username), passwordHash(hashPassword(password)), name(name), idCardHash(hashPassword(idCard)), contact(contact) {}

    // ��ȡ�û���
    string getUsername() const {
        return username;
    }

    // ��ȡ�����ϣ
    string getPasswordHash() const {
        return passwordHash;
    }

    // ��ȡ���֤�Ź�ϣ
    string getIdCardHash() const {
        return idCardHash;
    }

    // ��ȡ��ϵ��ʽ
    string getContact() const {
        return contact;
    }

private:
    // ��ϣ���ܺ�����ʹ�ü򵥵� XOR ���㣩
    string hashPassword(const string& input) {
        string encrypted = input;
        for (char& ch : encrypted) {
            ch ^= 123;  // ʹ��������
        }
        return encrypted;
    }
};

// �����֤������֤����
bool validateIDCard(const string& idCard) {
    return idCard.length() == 18 && idCard.find_first_not_of("0123456789") == string::npos;
}

// �򵥵���ϵ��ʽ��֤����
bool validateContact(const string& contact) {
    // �����ֻ�������11λ���֣������������ "@" �� "."
    if (contact.length() == 11 && contact.find_first_not_of("0123456789") == string::npos) {
        return true;  // �ֻ�������֤
    }
    if (contact.find('@') != string::npos && contact.find('.') != string::npos) {
        return true;  // �򵥵���������֤
    }
    return false;
}

// ����û����Ƿ�Ψһ
bool isUsernameUnique(const string& username) {
    ifstream file("voters.txt");
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(' ');  // �����û���������֮���ÿո�ֿ�
        string existingUsername = line.substr(0, pos);
        if (existingUsername == username) {
            return false;  // �ҵ��ظ����û���
        }
    }
    return true;
}

// ����ѡ����Ϣ���ļ�
void saveVoterToFile(const Voter& voter) {
    ofstream file("voters.txt", ios::app);
    if (file.is_open()) {
        file << voter.getUsername() << " "
            << voter.getPasswordHash() << " "
            << voter.getContact() << endl;
        file.close();
    }
    else {
        cout << "�޷����ļ�����ѡ����Ϣ��\n";
    }
}

// ѡ��ע�ᴦ����
void handleVoterRegistration() {
    string username, password, name, idCard, contact;

    cout << "�������û���: ";
    cin >> username;

    // ����û����Ƿ�Ψһ
    if (!isUsernameUnique(username)) {
        cout << "���û����ѱ�ע�ᣬ��ѡ�������û�����\n";
        return;
    }

    cout << "����������: ";
    cin >> password;

    // ��֤����ǿ�ȣ����磬����8���ַ����������ֺ���ĸ��
    if (password.length() < 8) {
        cout << "���볤�ȱ�������Ϊ8���ַ���\n";
        return;
    }

    cout << "����������: ";
    cin >> name;

    cout << "���������֤���루18λ����";
    cin >> idCard;

    // ��֤���֤�����ʽ
    if (!validateIDCard(idCard)) {
        cout << "���֤�����ʽ����ȷ��ӦΪ18λ���֡�\n";
        return;
    }

    cout << "��������ϵ��ʽ���ֻ������������䣩��";
    cin >> contact;

    // ��֤��ϵ��ʽ��ʽ
    if (!validateContact(contact)) {
        cout << "��ϵ��ʽ��ʽ����ȷ��\n";
        return;
    }

    // ����ѡ�����
    Voter newVoter(username, password, name, idCard, contact);

    // ����ѡ����Ϣ���ļ�
    saveVoterToFile(newVoter);

    cout << "ע��ɹ�����ӭ " << name << "�������û���Ϊ " << username << "��\n";
}

