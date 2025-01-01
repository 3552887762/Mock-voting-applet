#ifndef VOTINGINFO_H
#define VOTINGINFO_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
// 投票信息

class VotingInfo {
private:
    time_t startTime;
    time_t endTime;
    int totalVoters;
    int totalVotes;

public:
    VotingInfo(time_t start, time_t end, int total, int votes)
        : startTime(start), endTime(end), totalVoters(total), totalVotes(votes) {}

    // Getter 方法
    time_t getStartTime() const { return startTime; }
    time_t getEndTime() const { return endTime; }
    int getTotalVoters() const { return totalVoters; }
    int getTotalVotes() const { return totalVotes; }

    // 投票状态判断方法（假设）
    std::string getVotingStatus() const {
        time_t now = time(0);
        if (now < startTime) return "未开始";
        if (now > endTime) return "已结束";
        return "进行中";
    }
    void addendTime(int time) {
        endTime += time;
    }
    int getRemainingTime() const {
        time_t now = time(0);
        return (endTime - now) > 0 ? (endTime - now) : 0;
    }
    int incrementTotalVotes() { return ++totalVotes; }

};


#endif
