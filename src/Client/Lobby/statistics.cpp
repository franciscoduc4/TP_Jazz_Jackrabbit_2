#include "statistics.h"

#include <utility>
#include "ui_statistics.h"

Statistics::Statistics(QWidget *parent, const LobbyMessage& msg, const FinalStats& stats, bool& clientJoinedGame, const uint8_t& playerId)
        : QMainWindow(parent)
        , ui(new Ui::Statistics)
        , stats(stats)
        , msg(msg)
        , playerId(playerId)
        , clientJoinedGame(clientJoinedGame)
{
    ui->setupUi(this);
    displayStats();
    clientJoinedGame = false;
}

Statistics::~Statistics() { delete ui; }

void Statistics::displayStats() {
    if (!clientJoinedGame) {
        ui->stats->setText("No hay estadísticas para mostrar.");
        return;
    }

    if (msg.getMaxPlayers() == 1) {
        QString finalMsg = "Buena Partida!";
        if (stats.getScores().empty()) {
            ui->stats->setText(finalMsg);
            return;
        }

        int score = stats.getScores().at(this->playerId);
        finalMsg += "\n\nPuntaje: " + QString::number(score);
        ui->stats->setText(finalMsg);
        return;
    }

    bool isWinner = this->playerId == stats.getWinner();
    QString finalMsg = isWinner ? "Ganaste!" : "Buena Partida!";
    finalMsg += "\n\nPuntajes:\n";
    for (const auto& [player, score] : stats.getScores()) {
        finalMsg += "Jugador " + QString::number(player) + ": " + QString::number(score) + "\n";
    }
    ui->stats->setText(finalMsg);
}

