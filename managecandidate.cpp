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
    std::cout << "请输入参选人编号: ";
    std::getline(std::cin, id);
    std::string name, category, description;
    std::cout << "请输入参选人姓名: ";
    std::getline(std::cin, name);

    std::cout << "请输入参选类别: ";
    std::getline(std::cin, category);
    std::cout << "请输入参选简介: ";
    std::getline(std::cin, description);
    
   candidates.push_back(Candidate(stringtointeger(id), name, category, description));
    std::cout << "参选对象 " << name << " 已成功添加。\n";
}


void modifyCandidate(std::vector<Candidate>& candidates, int id) {
    bool found = false;

    for (auto& candidate : candidates) {
        if (id == candidate.getId()) {
            std::string description;
            std::cout << "请输入新的参选简介: ";
            std::getline(std::cin, description);
            candidate.setdescription(description);
            found = true;
            std::cout << "参选对象 " << id << " 的简介已成功更新。\n";
            return;
        }
    }
    if (!found) {
        std::cout << "未找到该参选对象。\n";
    }
}


void removeCandidate(std::vector<Candidate>& candidates, int id) {   
    bool found = false;
    for (auto it = candidates.begin(); it != candidates.end(); ++it) {
        if (it->getId() == id) {

            candidates.erase(it);
            found = true;
            std::cout << "参选对象 " << id << " 已成功删除。\n";
            break;  
        }
    }

    if (!found) {
        std::cout << "未找到该参选对象。\n";
    }

}


void viewAllCandidates(const std::vector<Candidate>& candidates) {
    if (candidates.empty()) {
        std::cout << "当前没有参选对象。\n";
        return;
    }

    std::cout << "参选对象列表：\n";
    for (const auto& candidate : candidates) {
        std::cout << "姓名: " << candidate.getName() << ", 编号: " << candidate.getId()
            << ", 类别: " << candidate.getCategory() << ", 简介: " << candidate.getDescription() << "\n";
    }  
}


void confirmFinalCandidates(std::vector<Candidate>& candidates) {
    if (candidates.empty()) {
        std::cout << "当前没有参选对象。\n";
        return;
    }
    std::cout << "最终参选名单已确认：\n";
    for (const auto& candidate : candidates) {
        if (candidate.getIsActive()) {
            std::cout << "姓名: " << candidate.getName() << ", 编号: " << candidate.getId()
                << ", 类别: " << candidate.getCategory() << ", 简介: " << candidate.getDescription() << "\n";
        }
    }
    std::cout << "参选名单确认完毕。\n";
}


void showAdmin_Menu() {
    system("cls");
    std::cout << "=====================\n";
    std::cout << "管理员操作菜单\n";
    std::cout << "=====================\n";
    std::cout << "1. 添加参选对象\n";
    std::cout << "2. 修改参选对象信息\n";
    std::cout << "3. 删除参选对象\n";
    std::cout << "4. 修改是否参选对象参赛\n";
    std::cout << "5. 查看所有参选对象\n";
    std::cout << "6. 确认最终参选名单\n";
    std::cout << "7. 返回\n";
    std::cout << "=====================\n";
}


void handleAdminMenu(std::vector<Candidate>& candidates) {
    int choice;
    while (true) {
        showAdmin_Menu();
        std::cout << "请输入您的选择: ";
        std::cin >> choice;

        std::cin.ignore();  
        switch (choice) {
        case 1: {
            addCandidate(candidates);  system("pause");
            break;
        }
        case 2: {
            string id;
            std::cout << "请输入要修改的参选人编号: ";
            std::getline(std::cin, id); 
            modifyCandidate(candidates, stringtointeger(id));  system("pause");
            break;
        }
        case 3: {
            string id;
            std::cout << "请输入要修改的参选人编号: ";
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
            std::cout << "无效的选项，请重新选择。\n";
            break;
        }
        saveCandidatesToFile(candidates, "candidates.txt");
    }
}

void banjoin(std::vector<Candidate>& candidates) {
    if (candidates.empty()) {
        std::cout << "当前没有参选对象。\n";
        return;
    }
    cout << "请输入参赛的参选人编号: ";
    string id;
    getline(cin, id);
    //输入0不参赛，1参赛
    string status;
    cout << "请输入参赛状态(0:不参赛, 1:参赛): ";
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
            cout << "修改成功。\n";
        }
    }

   
}