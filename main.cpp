#include <iostream>
#include <string>
#include <cstdlib>
#include "voter_registration.hpp"
#include "login.hpp"
#include "main.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "candidate.hpp"
#include "votinginfo.hpp"
void showMainMenu() {
    system("cls"); 
    cout << "=========================\n";
    cout << "    ͶƱС����˵�\n";
    cout << "=========================\n";
    cout << "1. ѡ��ע��\n";
    cout << "2. ѡ���¼\n";
    cout << "3. ����Ա��¼\n";
    cout << "4. �˳�ϵͳ\n";
    cout << "=========================\n";
}
// ����VotingInfo����ĺ���
VotingInfo createVotingInfo(const std::vector<Candidate>& candidates, int totalVoters) {
    // ��ȡ��ǰʱ�䣨��ǰʱ�����
    time_t now = time(0);

    // ���ÿ�ʼʱ�䣨����Ϊ��ǰʱ�䣩
    time_t startTime = now;

    // ���ý���ʱ�䣨����Ϊ��ǰʱ���1Сʱ��
    time_t endTime = now + 3600; // 1Сʱ��

    // ������ͶƱ���������к�ѡ�˵ĵ�Ʊ���ܺͣ�
    int totalVotes = 0;
    for (const auto& candidate : candidates) {
        totalVotes += candidate.getVoteCount();
    }

    // ����������VotingInfo����
    return VotingInfo(startTime, endTime, totalVoters, totalVotes);
}
int main() {
    int totalVoters = 1000; // ��ѡ����������Ϊ1000��
    std::vector<Candidate> candidates;

    if (!loadCandidatesFromFile(candidates, "candidates.txt")) {
        std::cout << "û���ҵ���ѡ������Ϣ�����ڴ����µĲ�ѡ����" << std::endl;
    }
    saveCandidatesToFile(candidates, "candidates.txt");
    VotingInfo votingInfo = createVotingInfo(candidates, totalVoters);
    int choice;

    while (true) {
        showMainMenu();
        cout << "����������ѡ��: ";

        string input;
        getline(cin, input);  // ��ȡ�û����������

        // ���Խ�����תΪ����������Ƿ�ɹ�
        stringstream ss(input);
        if (ss >> choice && ss.eof()) {
            // ������һ����Ч������
            switch (choice) {
            case 1:
                handleVoterRegistration();
                system("pause");
                break;
            case 2:
                handleVoterLogin(candidates, votingInfo);
                system("pause");
                break;
            case 3:
                handleAdminLogin(candidates, votingInfo);
                system("pause");
                break;
            case 4:
                cout << "�˳�ϵͳ����лʹ�ã�\n";
                return 0;
            default:
                cout << "��Ч��ѡ�������ѡ��\n";
            }
        }
        else {
            cout << "��Ч���룬����������ѡ�1~4��!\n";
        }
    }

    return 0;
}




