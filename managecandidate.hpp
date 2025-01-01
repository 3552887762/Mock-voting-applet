#ifndef MANAGECANDIDATE_HPP
#define MANAGECANDIDATE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "candidate.hpp"
#include "voter.hpp"
void addCandidate(std::vector<Candidate>& candidates);
void modifyCandidate(std::vector<Candidate>& candidates, const std::string& id);
void removeCandidate(std::vector<Candidate>& candidates, const std::string& id);
void viewAllCandidates(const std::vector<Candidate>& candidates);
void confirmFinalCandidates(std::vector<Candidate>& candidates);
void showAdmin_Menu(vector<Candidate>& candidates);
void handleAdminMenu(std::vector<Candidate>& candidates);
void banjoin(std::vector<Candidate>& candidates);
#endif // MANAGECANDIDATE_HPP
