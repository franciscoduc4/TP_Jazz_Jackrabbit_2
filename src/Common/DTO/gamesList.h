#ifndef GAMES_LIST_DTO_H_
#define GAMES_LIST_DTO_H_

#include <map>
#include <string>

class GamesListDTO {
private:
    std::map<int32_t, std::string> games;

public:
    GamesListDTO() {}
    explicit GamesListDTO(std::map<int32_t, std::string> games);
    std::map<int32_t, std::string> getGames() const;
    ~GamesListDTO() {}
};


#endif  // GAMES_LIST_DTO_H_
