#include "voter_registration.hpp"
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

// �����֤������֤����
bool validateIDCard(const std::string& idCard) {
    return idCard.length() == 18 && idCard.find_first_not_of("0123456789") == std::string::npos;
}

// �򵥵���ϵ��ʽ��֤����
bool validateContact(const std::string& contact) {
    if (contact.length() == 11 && contact.find_first_not_of("0123456789") == std::string::npos) {
        return true;  // �ֻ�������֤
    }
    return false;
}

// ����û����Ƿ�Ψһ
bool isUsernameUnique(const std::string& username) {
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
    std::ofstream file("voters.txt", std::ios::app);  

    cout << voter.hasVotingRights() << endl;
    if (file.is_open()) {
        // ����ѡ����Ϣ���û��� �����ϣ ���� ���֤��ϣ ��ϵ��ʽ
        file << voter.getUsername() << " "
            << voter.getPasswordHash() << " "
            << voter.getName() << " "
            << voter.getIdCard() << " "
            << voter.getContact() << " "
            << (voter.hasVotingRights() ? 1 : 0)  // ת��ͶƱȨΪ 1 �� 0
            << "\n";
        file.close();
        std::cout << "ѡ����Ϣ����ɹ���\n";
    }
    else {
        std::cout << "�޷����ļ�����ѡ����Ϣ��\n";
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

    cout << "����������(���볤�ȱ�������Ϊ8���ַ�): ";
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

    cout << "�������ֻ����룺";
    cin >> contact;

    // ��֤��ϵ��ʽ��ʽ
    if (!validateContact(contact)) {
        cout << "��ϵ��ʽ��ʽ����ȷ��\n";
        return;
    }

    // ����ѡ�����
    Voter newVoter(username, password, name, idCard, contact,true);

    // ����ѡ����Ϣ���ļ�
    saveVoterToFile(newVoter);

    cout << "ע��ɹ�����ӭ " << name << "�������û���Ϊ " << username << "��\n";
     
}
