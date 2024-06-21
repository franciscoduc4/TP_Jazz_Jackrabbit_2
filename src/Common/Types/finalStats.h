#ifndef FINALSTATS_H
#define FINALSTATS_H

#include <string>
#include <vector>
#include <map>

struct FinalStats {
    std::string winner;
    std::map<std::string, std::string> players;
    std::map<std::string, std::string> scores;

    FinalStats():
            winner("Nadie"),
            players(),
            scores() {}

    FinalStats(std::string winner, std::map<std::string, std::string> players,
               std::map<std::string, std::string> scores):
            winner(std::move(winner)),
            players(std::move(players)),
            scores(std::move(scores)) {}

    void setWinner(const std::string& name) { winner = name; }

    void addPlayer(const std::string& name, const std::string& character) {
        players[name] = character;
    }

    void addScore(const std::string& name, const std::string& score) {
        scores[name] = score;
    }

    [[nodiscard]] std::string getWinner() const { return winner; }

    [[nodiscard]] std::map<std::string, std::string> getPlayers() const { return players; }

    [[nodiscard]] std::map<std::string, std::string> getScores() const { return scores; }
};

#endif  // FINALSTATS_H
