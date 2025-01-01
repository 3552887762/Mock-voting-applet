#include "manageVoters.hpp"

// ��ʾ����ѡ��Ļ�����Ϣ
void showAllVoters(const std::vector<Voter>& voters) {
    std::cout << "����ѡ����Ϣ:\n";
    for (const auto& voter : voters) {
        std::cout << "�û���: " << voter.getUsername() << "\n";
        std::cout << "����: " << voter.getName() << "\n";
        std::cout << "���֤��: " << voter.getIdCard() << "\n";
        std::cout << "��ϵ��ʽ: " << voter.getContact() << "\n";
        std::cout << "ͶƱȨ��: " << (voter.hasVotingRights() ? "��" : "û��") << "\n";
        std::cout << "---------------------------\n";
    }
}

// �޸�ѡ����ϵ��ʽ
void modifyVoterContact(std::vector<Voter>& voters, const std::string& username) {
    std::string newContact;
    std::cout << "�������µ���ϵ��ʽ: ";
    std::cin >> newContact;
    bool flag = false;
    for (auto& voter : voters) {
        if (voter.getUsername() == username) {
            voter.setcontact(newContact);
            flag = true;
            std::cout << "��ϵ��ʽ�Ѹ��¡�\n";
            break;
        }
    }
    if (!flag) {
        std::cout << "δ�ҵ���ѡ��\n";
    }
}

// �޸�ѡ��ͶƱȨ��
void modifyVoterVotingRights(std::vector<Voter>& voters, const std::string& username) {
    bool newVotingRights;
    std::cout << "�������µ�ͶƱȨ�� (1: ����ͶƱ, 0: ��ֹͶƱ): ";
    std::cin >> newVotingRights;
    bool flag = false;
    for (auto& voter : voters) {
        if (voter.getUsername() == username) {
            voter.setVotingRights(newVotingRights);
            flag = true;
            std::cout << "ͶƱȨ���Ѹ��¡�\n";
            break;
        }
    }
    if (!flag) {
        std::cout << "δ�ҵ���ѡ��\n";
    }
}
