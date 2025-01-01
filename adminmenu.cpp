#include <iostream>
#include "AdminMenu.hpp"
#include "Candidate.hpp"
#include "VotingInfo.hpp"
#include "Voter.hpp"
#include "managevoters.hpp"
#include "votermenu.hpp"
#include "managecandidate.hpp"
using namespace std;

void handleAdminMenu(vector<Candidate>& candidates, VotingInfo& votingInfo) {
    vector<Voter> voters;
    // ��ʼ��ѡ����Ϣ
    loadVotersFromFile("voters.txt", voters);
    int adminChoice;

    while (true) {
        showAdminMenu();  // ��ʾ����Ա�˵�
        cout << "����������ѡ��: ";
        cin >> adminChoice;

        switch (adminChoice) {
        case 1:
            manageVoters(voters);  // ����ѡ����Ϣ
            system("pause");
            break;
        case 2:
             setVotingTime(votingInfo);  // ����ͶƱʱ��
             system("pause");
            break;
        case 3:
            showVotingResults(candidates);  // ��ѯͶƱ���
            system("pause");
            break;
        case 4:
            handleAdminMenu(candidates);
            system("pause");
            return;  
        case 5:
            return;  // �������˵�
        default:
            cout << "��Ч��ѡ�������ѡ��\n";
            break;
        }
    }
}
// ��ȡѡ����Ϣ����ʼ��Voter����
void loadVotersFromFile(const string& filename, vector<Voter>& voters) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "�޷���ѡ����Ϣ�ļ���\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, passwordHash, name, idCard, contact;
        int hasVotingRightsInt;
        ss >> username >> passwordHash >> name >> idCard >> contact >> hasVotingRightsInt;

        // ��ͶƱȨת��Ϊboolֵ
        bool hasVotingRights = (hasVotingRightsInt == 1);

        // ���� Voter ������ӵ� voters ������
        voters.push_back(Voter(username, passwordHash, name, idCard, contact, hasVotingRights));
    }

    file.close();
}
void manageVoters(std::vector<Voter>& voters) {
    int choice;
    while (true) {
        system("cls");
        cout << "=========================\n";
        std::cout << " ѡ�����˵�:\n";
        cout << "=========================\n";
        std::cout << "1. �鿴ѡ����Ϣ\n";
        std::cout << "2. �޸�ѡ����ϵ��ʽ\n";
        std::cout << "3. �޸�ѡ��ͶƱȨ��\n";
        std::cout << "4. ����\n";
        std::cout << "����������ѡ��: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            showAllVoters(voters); system("pause");  // �鿴ѡ����Ϣ
            break;
        case 2:
        {
            std::string username;
            std::cout << "������ѡ���û���: ";
            std::cin >> username;
            modifyVoterContact(voters, username); system("pause");  // �޸�ѡ����ϵ��ʽ
            break;
        }
        case 3:
        {
            std::string username;
            std::cout << "������ѡ���û���: ";
            std::cin >> username;
            modifyVoterVotingRights(voters, username); system("pause");  // �޸�ѡ��ͶƱȨ��
            break;
        }
        case 4:
            return;  // ����
        default:
            std::cout << "��Ч��ѡ�������ѡ��\n";
            break;
        }
        for (const auto& voter : voters) {
            modifyVoterInFile1(voter);
        }
    }
}

void modifyVoterInFile1(const Voter& voter) {
    // ��ѡ����Ϣ�ļ����ж�ȡ
    std::ifstream infile("voters.txt");
    if (!infile.is_open()) {
        std::cout << "�޷���ѡ���ļ������޸ģ�\n";
        return;
    }

    std::vector<Voter> voters;
    std::string line;

    // ��ȡ�ļ��е�����ѡ����Ϣ
    while (getline(infile, line)) {
        std::stringstream ss(line);
        std::string username, passwordHash, name, idCard, contact;
        bool hasVotingRights;

        ss >> username >> passwordHash >> name >> idCard >> contact >> hasVotingRights;

        // ����û���ƥ�䣬����ѡ����Ϣ
        if (username == voter.getUsername()) {
            // ����ѡ����Ϣ�������޸ĺ��ͶƱȨ�޺���ϵ��ʽ
            voters.push_back(Voter(username, passwordHash, name, idCard, voter.getContact(), voter.hasVotingRights()));
        }
        else {
            // ���ڲ���Ҫ���µ�ѡ�񣬱���ԭ��Ϣ
            voters.push_back(Voter(username, passwordHash, name, idCard, contact, hasVotingRights));
        }
    }
    infile.close();

    // ����д���޸ĺ��ѡ����Ϣ
    std::ofstream outfile("voters.txt");
    if (!outfile.is_open()) {
        std::cout << "�޷����±���ѡ���ļ���\n";
        return;
    }

    // д������ѡ������
    for (const auto& voterItem : voters) {
        outfile << voterItem.getUsername() << " "
            << voterItem.getPasswordHash() << " "
            << voterItem.getName() << " "
            << voterItem.getIdCard() << " "
            << voterItem.getContact() << " "
            << (voterItem.hasVotingRights() ? 1 : 0) << "\n";
    }

    outfile.close();
    std::cout << "ѡ����Ϣ�Ѹ��£�\n";
}

// ��ʾ����Ա�����˵�
void showAdminMenu() {
    system("cls");  
    cout << "=========================\n";
    cout << " ����Ա�����˵�\n";
    cout << "=========================\n";
    cout << "1. ����ѡ����Ϣ\n";
    cout << "2. ����ͶƱʱ��\n";
    cout << "3. ��ѯͶƱ���\n";
    cout << "4. �޸Ĳ�ѡ������Ϣ\n";
    cout << "5. �������˵�\n";
    cout << "=========================\n";
}

void showVotingResults(const vector<Candidate>& candidates) {
    for (const auto& candidate : candidates) {
        cout << "��ѡ��: " << candidate.getName() << ", Ʊ��: " << candidate.getVoteCount() << endl;
    }

}

void setVotingTime(VotingInfo& votingInfo) {
    cout << "�ӳ�Сʱ����"<< endl;
    int hours;
    cin >> hours;
    votingInfo.addendTime(hours*3600);
    cout << "ͶƱʱ�����ӳ�" << hours << "Сʱ" << endl;
}