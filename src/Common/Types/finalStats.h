#ifndef FINALSTATS_H
#define FINALSTATS_H

#include <string>
#include <vector>
#include <map>

struct FinalStats {
    uint8_t winner;
    std::map<uint8_t, int> scores;

    explicit FinalStats(const std::map<uint8_t, int>& scores) : scores(scores) {
        int maxScore = 0;
        for (const auto& [player, score] : scores) {
            if (score > maxScore) {
                maxScore = score;
                winner = player;
            }
        }
    }

    [[nodiscard]] uint8_t getWinner() const { return winner; }
    [[nodiscard]] std::map<uint8_t, int> getScores() const { return scores; }
};

#endif  // FINALSTATS_H
