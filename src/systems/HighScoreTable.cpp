#include "HighScoreTable.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void HighScoreTable::load(const std::string& path) {
    filePath = path;
    entries.clear();

    std::ifstream file(filePath);
    if (!file.is_open()) return; // pas de fichier au premier lancement : normal

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string label;
        std::string scoreStr;
        if (std::getline(ss, label, ';') && std::getline(ss, scoreStr)) {
            try {
                int score = std::stoi(scoreStr);
                entries.push_back({label, score});
            } catch (...) {
                // ligne corrompue -> ignorée
            }
        }
    }
    sortAndTrim();
}

void HighScoreTable::addEntry(const std::string& label, int score) {
    entries.push_back({label, score});
    sortAndTrim();
    save();
}

void HighScoreTable::sortAndTrim() {
    std::sort(entries.begin(), entries.end(),
              [](const HighScoreEntry& a, const HighScoreEntry& b) {
                  return a.score > b.score;
              });
    if (entries.size() > MAX_ENTRIES) {
        entries.resize(MAX_ENTRIES);
    }
}

void HighScoreTable::save() const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) return;
    for (const auto& e : entries) {
        file << e.label << ";" << e.score << "\n";
    }
}