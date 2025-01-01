#include "Login.hpp"
#include "Admin.hpp"
#include "votermenu.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <Windows.h>  
#include "main.hpp"
#include "adminmenu.hpp"
#include "voter.hpp"
#include "votinginfo.hpp"
using namespace std;



void handleAdminLogin(vector<Candidate>& candidates,VotingInfo& votingInfo) {
    vector<Admin> admins;  // ���ڴ洢���й���Ա��Ϣ
    const string adminFile = "admin.txt";  // �������Ա��Ϣ������ admin.txt �ļ���

    // ���ļ���ȡ����Ա��Ϣ
    if (!Admin::loadAdminsFromFile(adminFile, admins)) {
        cout << "��ȡ����Ա��Ϣʧ�ܣ�ϵͳ�޷����е�¼��֤��\n";
        return;
    }

    int failedAttempts = 0;  // ��¼��¼ʧ�ܴ���
    while (true) {
        string adminName, adminPassword;
        cout << "���������Ա�û���: ";
        cin >> adminName;
        cout << "���������Ա����: ";
        cin >> adminPassword;

        bool isValid = false;

        // �������й���Ա������û����������Ƿ�ƥ��
        for (const auto& admin : admins) {
            if (admin.validateLogin(adminName, adminPassword)) {
                isValid = true;
                break;
            }
        }

        // ���ƥ�䣬��¼�ɹ�
        if (isValid) {
            cout << "����Ա��¼�ɹ���\n";
            system("pause");
          handleAdminMenu(candidates, votingInfo);
            break;  // ��¼�ɹ����˳�ѭ��
        }
        else {
            cout << "����Ա��¼ʧ�ܣ��û������������\n";
            failedAttempts++;

            if (failedAttempts >= 3) {
                cout << "������¼ʧ��3�Σ�ϵͳ��������30��...\n";
                Sleep(30000);  // Windows����30��
            }
        }
    }
}

// ��ȡѡ����Ϣ
bool loadVoterFromFile(const std::string& username, Voter& voter) {
    std::ifstream file("voters.txt");
    if (!file.is_open()) {
        std::cout << "�޷���ѡ����Ϣ�ļ���\n";
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fileUsername, filePasswordHash, fileName, fileIdCardHash, fileContact;
        int fileVotingRights;  // ���ڶ�ȡͶƱȨ��1��0��

        // ��ȡÿ���е�����
        ss >> fileUsername >> filePasswordHash >> fileName >> fileIdCardHash >> fileContact >> fileVotingRights;

        if (fileUsername == username) {
            // ���ļ��е����ݶ�ȡ�� Voter ����
            voter = Voter(fileUsername, filePasswordHash, fileName, fileIdCardHash, fileContact, fileVotingRights == 1);
            return true;
        }
    }
    return false; // δ�ҵ����û���
}

void handleVoterLogin(vector<Candidate>& candidates, VotingInfo& votingInfo) {
    std::string username, password;
    int loginAttempts = 0;

    while (loginAttempts < 3) {
        std::cout << "������ѡ���û���: ";
        std::cin >> username;

        std::cout << "������ѡ������: ";
        std::cin >> password;

        // ���ļ��м���ѡ����Ϣ
        Voter voter("", "", "", "", "",false); // �յ�Voter����
        if (loadVoterFromFile(username, voter)) {
            // ����ҵ�ѡ����֤����
            if (voter.validatePassword(password)) {
                std::cout << "ѡ���¼�ɹ���\n";
                system("pause");
               handlevoter(candidates,voter, votingInfo);
                break; 
            }
            else {
                std::cout << "����������������롣\n";
            }
        }
        else {
            std::cout << "�û��������ڣ����������롣\n";
        }

        loginAttempts++;
        if (loginAttempts >= 3) {
            std::cout << "������¼ʧ��3�Σ�ϵͳ��������30��...\n";
            Sleep(30000);  // Windows����30��
            loginAttempts = 0; // ���ó��Դ���
        }
    }
}