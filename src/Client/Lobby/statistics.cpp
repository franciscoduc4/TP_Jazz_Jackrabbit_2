#include "statistics.h"

#include <utility>
#include "ui_statistics.h"

Statistics::Statistics(QWidget *parent, FinalStats  stats, bool& clientJoinedGame)
        : QMainWindow(parent)
        , ui(new Ui::Statistics)
        , stats(std::move(stats))
        , clientJoinedGame(clientJoinedGame)
{
    ui->setupUi(this);
    displayStats();
    clientJoinedGame = false;
}

Statistics::~Statistics() { delete ui; }

void Statistics::displayStats() {
    std::string winnerName = stats.getWinner();
    std::map<std::string, std::string> players = stats.getPlayers();
    std::map<std::string, std::string> scores = stats.getScores();

    std::string statsText = "Ganador: " + winnerName + "\n\n";

    for (const auto& player : players) {
        std::string playerName = player.first;
        std::string playerCharacter = player.second;
        std::string playerScore = scores[playerName];

        statsText += playerName + " | " + playerCharacter + " | " + playerScore + "\n";
    }

    ui->stats->setText(QString::fromStdString(statsText));
}

