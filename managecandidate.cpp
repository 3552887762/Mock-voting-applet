#include "managecandidate.hpp"
int stringtointeger(string s) {
    int i = 0;
    for (int j = 0; j < s.length(); j++) {
        i = i * 10 + (s[j] - '0');
    }
    return i;
}


void addCandidate(std::vector<Candidate>& candidates) {
    string id;
    std::cout << "�������ѡ�˱��: ";
    std::getline(std::cin, id);
    std::string name, category, description;
    std::cout << "�������ѡ������: ";
    std::getline(std::cin, name);

    std::cout << "�������ѡ���: ";
    std::getline(std::cin, category);
    std::cout << "�������ѡ���: ";
    std::getline(std::cin, description);
    
   candidates.push_back(Candidate(stringtointeger(id), name, category, description));
    std::cout << "��ѡ���� " << name << " �ѳɹ���ӡ�\n";
}


void modifyCandidate(std::vector<Candidate>& candidates, int id) {
    bool found = false;

    for (auto& candidate : candidates) {
        if (id == candidate.getId()) {
            std::string description;
            std::cout << "�������µĲ�ѡ���: ";
            std::getline(std::cin, description);
            candidate.setdescription(description);
            found = true;
            std::cout << "��ѡ���� " << id << " �ļ���ѳɹ����¡�\n";
            return;
        }
    }
    if (!found) {
        std::cout << "δ�ҵ��ò�ѡ����\n";
    }
}


void removeCandidate(std::vector<Candidate>& candidates, int id) {   
    bool found = false;
    for (auto it = candidates.begin(); it != candidates.end(); ++it) {
        if (it->getId() == id) {

            candidates.erase(it);
            found = true;
            std::cout << "��ѡ���� " << id << " �ѳɹ�ɾ����\n";
            break;  
        }
    }

    if (!found) {
        std::cout << "δ�ҵ��ò�ѡ����\n";
    }

}


void viewAllCandidates(const std::vector<Candidate>& candidates) {
    if (candidates.empty()) {
        std::cout << "��ǰû�в�ѡ����\n";
        return;
    }

    std::cout << "��ѡ�����б�\n";
    for (const auto& candidate : candidates) {
        std::cout << "����: " << candidate.getName() << ", ���: " << candidate.getId()
            << ", ���: " << candidate.getCategory() << ", ���: " << candidate.getDescription() << "\n";
    }  
}


void confirmFinalCandidates(std::vector<Candidate>& candidates) {
    if (candidates.empty()) {
        std::cout << "��ǰû�в�ѡ����\n";
        return;
    }
    std::cout << "���ղ�ѡ������ȷ�ϣ�\n";
    for (const auto& candidate : candidates) {
        if (candidate.getIsActive()) {
            std::cout << "����: " << candidate.getName() << ", ���: " << candidate.getId()
                << ", ���: " << candidate.getCategory() << ", ���: " << candidate.getDescription() << "\n";
        }
    }
    std::cout << "��ѡ����ȷ����ϡ�\n";
}


void showAdmin_Menu() {
    system("cls");
    std::cout << "=====================\n";
    std::cout << "����Ա�����˵�\n";
    std::cout << "=====================\n";
    std::cout << "1. ��Ӳ�ѡ����\n";
    std::cout << "2. �޸Ĳ�ѡ������Ϣ\n";
    std::cout << "3. ɾ����ѡ����\n";
    std::cout << "4. �޸��Ƿ��ѡ�������\n";
    std::cout << "5. �鿴���в�ѡ����\n";
    std::cout << "6. ȷ�����ղ�ѡ����\n";
    std::cout << "7. ����\n";
    std::cout << "=====================\n";
}


void handleAdminMenu(std::vector<Candidate>& candidates) {
    int choice;
    while (true) {
        showAdmin_Menu();
        std::cout << "����������ѡ��: ";
        std::cin >> choice;

        std::cin.ignore();  
        switch (choice) {
        case 1: {
            addCandidate(candidates);  system("pause");
            break;
        }
        case 2: {
            string id;
            std::cout << "������Ҫ�޸ĵĲ�ѡ�˱��: ";
            std::getline(std::cin, id); 
            modifyCandidate(candidates, stringtointeger(id));  system("pause");
            break;
        }
        case 3: {
            string id;
            std::cout << "������Ҫ�޸ĵĲ�ѡ�˱��: ";
            std::getline(std::cin, id);
            removeCandidate(candidates, stringtointeger(id));  system("pause");
            break;
        }
        case 4:
            banjoin(candidates);  system("pause");
           
            break;
        case 5:
            viewAllCandidates(candidates);  system("pause");
            viewAllCandidates(candidates);  system("pause");
            break;
        case 6:
            confirmFinalCandidates(candidates);  system("pause");
            break;
        case 7:
            return;
        default:
            std::cout << "��Ч��ѡ�������ѡ��\n";
            break;
        }
        saveCandidatesToFile(candidates, "candidates.txt");
    }
}

void banjoin(std::vector<Candidate>& candidates) {
    if (candidates.empty()) {
        std::cout << "��ǰû�в�ѡ����\n";
        return;
    }
    cout << "����������Ĳ�ѡ�˱��: ";
    string id;
    getline(cin, id);
    //����0��������1����
    string status;
    cout << "���������״̬(0:������, 1:����): ";
    getline(cin, status);
    bool isjoin = false;
    if (status == "0") {
        isjoin = false;
    }
    else {
        isjoin = true;
    }
    for (auto& candidate : candidates) {
        if (candidate.getId() == stringtointeger(id)) {
            candidate.setIsActive(isjoin);
            cout << "�޸ĳɹ���\n";
        }
    }

   
}