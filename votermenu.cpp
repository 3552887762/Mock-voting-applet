#include <iostream>
#include "VoterMenu.hpp"  // �����˵���ʾ��ѡ�������ͷ�ļ�
#include "VotingInfo.cpp"  // ����ͶƱ��Ϣ��ͷ�ļ�
#include "Candidate.hpp"  // ������ѡ������ͷ�ļ�
#include <vector>
#include <ctime>
#include <string>
#include "voter_registration.hpp"
using namespace std;

void handlevoter(vector<Candidate>& candidates,Voter& voter, VotingInfo& votingInfo) {
    int voterChoice;
    time_t now = time(0);  // ��ѭ����ʼʱ��ʼ��now

    while (true) {
        showVoterMenu(); // ��ʾѡ��˵�
        cout << "����������ѡ��: ";
        cin >> voterChoice;

        switch (voterChoice) {
        case 1:
            // ͶƱ��Ϣ��ѯ
            showVotingInformation(candidates, votingInfo);
            system("pause");
            break;
        case 2:
            // ͶƱ����
            handleVoting(candidates,voter,votingInfo);
            system("pause");
            break;
        case 3:
            return;
        default:
            cout << "��Ч��ѡ�������ѡ��\n";
            break;
        }
    }
}



// ��ʾѡ��˵�
void showVoterMenu() {
    system("cls"); // Windows ʹ�� system("cls");
    cout << "=========================\n";
    cout << " ѡ������˵�\n";
    cout << "=========================\n";
    cout << "1. ͶƱ��Ϣ��ѯ\n";
    cout << "2. ͶƱ\n";
    cout << "3. �������˵�\n";
    cout << "=========================\n";
}

// ͶƱ��Ϣ��ѯ����
void showVotingInformation(const std::vector<Candidate>& candidates, const VotingInfo& votingInfo) {
    // ���ͶƱ��Ϣ
     // ��ȡ����ʽ��ͶƱ��ʼʱ��ͽ���ʱ��
    time_t startTime = votingInfo.getStartTime();
    time_t endTime = votingInfo.getEndTime();

    // ʹ��ctime��time_tת��Ϊ�ַ���
    char startStr[26], endStr[26];
    ctime_s(startStr, sizeof(startStr), &startTime);
    ctime_s(endStr, sizeof(endStr), &endTime);
    // ���ͶƱ��Ϣ
    cout << "ͶƱ��ʼʱ��: " << startStr;
    cout << "ͶƱ����ʱ��: " << endStr;
    cout << "��ͶƱ����: " << votingInfo.getTotalVotes() << "/" << votingInfo.getTotalVoters() << endl;
    cout << "ͶƱ״̬: " << votingInfo.getVotingStatus() << endl;
    cout << "\n��ѡ������Ϣ:\n";
    for (const auto& candidate : candidates) {
        if (candidate.getIsActive()) {
            cout << "��ѡ���: " << candidate.getId() << "\n";
            cout << "����: " << candidate.getName() << "\n";
            cout << "��ѡ���: " << candidate.getCategory() << "\n";
            cout << "���: " << candidate.getDescription() << "\n";
            cout << "��ǰ��Ʊ��: " << candidate.getVoteCount() << "Ʊ\n";
            cout << "----------------------------------\n";
        }
    }
}

// ͶƱ��������
void handleVoting(vector<Candidate>& candidates,Voter& voter, VotingInfo& votingInfo) {
    time_t now = time(0);
    if (now < votingInfo.getStartTime() || now > votingInfo.getEndTime()) {
        cout << "��ǰ����ͶƱʱ�䷶Χ�ڣ��޷�ͶƱ��\n";
        return;
    }

    if (!voter.hasVotingRights()) {
        cout << "��û��ͶƱ�ʸ��޷�����ͶƱ��\n";
        return;
    }


    int selectedOption;
    cout << "��������ѡ��Ĳ�ѡ�����ţ�1~" << candidates.size() << "��: ";
    cin >> selectedOption;


    if (selectedOption < 1 || selectedOption > candidates.size()) {
        cout << "��Чѡ��������ѡ��\n";
        return;
    }
    bool finded = false;
    for (auto& candidate : candidates) {
        if (candidate.getId() == selectedOption && candidate.getIsActive()) {
            cout << "���ѳɹ�Ϊ��ѡ���� " << candidate.getName() << " ͶƱ��\n";
            finded = true;
            candidate.incrementVoteCount();
        }
    }
    if (!finded) {
        cout << "��Чѡ��������ѡ��\n";
        return;
    }

    voter.setVotingRights(false);
    

    // 6. ����ͶƱ��Ϣ���ļ�
    modifyVoterInFile(voter);  // �޸�ѡ���ļ��е�ͶƱ״̬
    saveVotingData(candidates, "candidates.txt");  // �����ѡ��������
    votingInfo.incrementTotalVotes();  // ������ͶƱ��
    // ��ʾ�����ɹ�
    cout << "����ͶƱ�ѳɹ��ύ����л���Ĳ��룡\n";
}

void modifyVoterInFile(const Voter& voter) {
    std::ifstream infile("voters.txt");
    if (!infile.is_open()) {
        std::cout << "�޷���ѡ���ļ������޸ģ�\n";
        return;
    }

    std::vector<Voter> voters;
    std::string line;
    while (getline(infile, line)) {
        std::stringstream ss(line);
        std::string username, passwordHash, name, idCard, contact;
        bool hasVotingRights;

        ss >> username >> passwordHash >> name >> idCard >> contact >> hasVotingRights;

        // ����û���ƥ�䣬�޸�ѡ���ͶƱȨ״̬
        if (username == voter.getUsername()) {
            voters.push_back(Voter(username, passwordHash, name, idCard, contact, false));  // �޸�ͶƱȨΪfalse
        }
        else {
            voters.push_back(Voter(username, passwordHash, name, idCard, contact, hasVotingRights));
        }
    }
    infile.close();

    // д���޸ĺ��ѡ����Ϣ
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

// �����ѡ�������ݵ��ļ�
void saveVotingData(const vector<Candidate>& candidates, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "�޷����ļ��������ݣ�\n";
        return;
    }

    for (const auto& candidate : candidates) {
        file << candidate.getId() << " "
            << candidate.getName() << " "
            << candidate.getCategory() << " "
            << candidate.getDescription() << " "
            << candidate.getVoteCount() << "\n";
    }

    file.close();
}



