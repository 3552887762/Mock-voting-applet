#include "candidate.hpp"
#include <iostream>

// 保存参选对象信息到文件
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
        std::cout << "参选对象信息已保存到文件。" << std::endl;
    }
    else {
        std::cerr << "无法打开文件进行保存！" << std::endl;
    }
}


bool loadCandidatesFromFile(std::vector<Candidate>& candidates, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件进行加载！" << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);

        // 读取参选对象的各项数据
        int id, voteCount;
        std::string name, category, description, isActiveStr;
        bool isActive;

        ss >> id;

        // 使用getline读取包含空格的字符串字段
        ss >> std::ws;  // 忽略空白字符
        getline(ss, name, ' ');  // 假设name字段使用逗号分隔
        getline(ss, category, ' ');  // 假设category字段使用逗号分隔

        // 读取描述部分
        getline(ss, description,' ');  // 剩余的全部作为description

        ss >> voteCount >> isActiveStr;
        isActive = (isActiveStr == "1");

        // 创建Candidate对象并加入到候选人列表中
        candidates.push_back(Candidate(id, name, category, description));
        candidates.back().setVoteCount(voteCount);
        // 设置候选人的激活状态
        if (!isActive) {
            candidates.back().deactivate();
        }
    }

    file.close();
    return true;
}
