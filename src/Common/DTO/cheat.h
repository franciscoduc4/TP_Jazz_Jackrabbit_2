#ifndef CHEATDTO_H
#define CHEATDTO_H

#include <memory>

#include "command.h"

enum class Cheat : char {
    END_GAME,
    RESET_SCORES
};
class CheatDTO : public CommandDTO {
protected:
    Cheat cheat;
public:
    explicit CheatDTO(Cheat cheat) : CommandDTO(Command::CHEAT), cheat(cheat) {}

    [[nodiscard]] Cheat getCheat() const {
        return cheat;
    }

    [[nodiscard]] std::vector<char> getData() const override {
        std::vector<char> data;
        data.push_back(static_cast<char>(cheat));
        return data;
    }

    [[nodiscard]] std::unique_ptr<DTO> clone() const override {
        return std::make_unique<CheatDTO>(cheat);
    }
};


#endif  // CHEATDTO_H
