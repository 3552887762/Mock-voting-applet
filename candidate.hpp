#ifndef CANDIDATE_HPP
#define CANDIDATE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
// ��ѡ�����ࣨCandidate��
class Candidate {
private:
    int id;
    std::string name;
    std::string category;//��ѡ���
    std::string description;
    int voteCount;//��Ʊ��
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

// �����ѡ������Ϣ���ļ�
void saveCandidatesToFile(const std::vector<Candidate>& candidates, const std::string& filename);


// ���ļ��м��ز�ѡ������Ϣ
bool loadCandidatesFromFile(std::vector<Candidate>& candidates, const std::string& filename);

#endif // CANDIDATE_HPP
