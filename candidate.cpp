#include "candidate.hpp"
#include <iostream>

// �����ѡ������Ϣ���ļ�
void saveCandidatesToFile(const std::vector<Candidate>& candidates, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& candidate : candidates) {
            file << candidate.getId() << " "
                << candidate.getName() << " "
                << candidate.getCategory() << " "
                << candidate.getDescription() << " "
                << candidate.getVoteCount() 
                << " " << (candidate.getIsActive() ? "1" : "0")
                 << std::endl;
        }
        file.close();
        std::cout << "��ѡ������Ϣ�ѱ��浽�ļ���" << std::endl;
    }
    else {
        std::cerr << "�޷����ļ����б��棡" << std::endl;
    }
}


bool loadCandidatesFromFile(std::vector<Candidate>& candidates, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ����м��أ�" << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);

        // ��ȡ��ѡ����ĸ�������
        int id, voteCount;
        std::string name, category, description, isActiveStr;
        bool isActive;

        ss >> id;

        // ʹ��getline��ȡ�����ո���ַ����ֶ�
        ss >> std::ws;  // ���Կհ��ַ�
        getline(ss, name, ' ');  // ����name�ֶ�ʹ�ö��ŷָ�
        getline(ss, category, ' ');  // ����category�ֶ�ʹ�ö��ŷָ�

        // ��ȡ��������
        getline(ss, description,' ');  // ʣ���ȫ����Ϊdescription

        ss >> voteCount >> isActiveStr;
        isActive = (isActiveStr == "1");

        // ����Candidate���󲢼��뵽��ѡ���б���
        candidates.push_back(Candidate(id, name, category, description));
        candidates.back().setVoteCount(voteCount);
        // ���ú�ѡ�˵ļ���״̬
        if (!isActive) {
            candidates.back().deactivate();
        }
    }

    file.close();
    return true;
}
