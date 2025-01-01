#ifndef CANDIDATE_HPP
#define CANDIDATE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
// 参选对象类（Candidate）
class Candidate {
private:
    int id;
    std::string name;
    std::string category;//参选类别
    std::string description;
    int voteCount;//得票数
    bool isActive;

public:
    Candidate(int id, const std::string& name, const std::string& category, const std::string& description)
        : id(id), name(name), category(category), description(description), voteCount(0), isActive(true) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    std::string getDescription() const { return description; }
    int getVoteCount() const { return voteCount; }
    bool getIsActive() const { return isActive; }
    void setIsActive(bool active) { isActive = active; }
    void setdescription(const std::string& description) { this->description = description; }
    void setVoteCount(int count) { voteCount = count; }
    void incrementVoteCount() { voteCount++; }
    void deactivate() { isActive = false; }
};

// 保存参选对象信息到文件
void saveCandidatesToFile(const std::vector<Candidate>& candidates, const std::string& filename);


// 从文件中加载参选对象信息
bool loadCandidatesFromFile(std::vector<Candidate>& candidates, const std::string& filename);

#endif // CANDIDATE_HPP
