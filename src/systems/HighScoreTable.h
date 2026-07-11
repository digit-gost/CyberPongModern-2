#pragma once
#include <string>
#include <vector>

struct HighScoreEntry {
    std::string label;
    int score;
};

class HighScoreTable {
public:
    void load(const std::string& path = "scores.txt");
    void addEntry(const std::string& label, int score);
    const std::vector<HighScoreEntry>& getEntries() const { return entries; }

private:
    std::vector<HighScoreEntry> entries;
    std::string filePath = "scores.txt";
    static constexpr size_t MAX_ENTRIES = 5;

    void save() const;
    void sortAndTrim();
};