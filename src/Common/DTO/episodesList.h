#ifndef EPISODES_LIST_H
#define EPISODES_LIST_H

#include <map>
#include <string>
#include <vector>

#include "command.h"

class EpisodesListDTO: public CommandDTO {
private:
    std::map<uint32_t, std::string> episodesMap;

public:
    EpisodesListDTO();
    explicit EpisodesListDTO(std::map<int, std::string> episodes);

    std::map<uint32_t, std::string> getEpisodesMap() const;
    std::map<int, std::string> getEpisodes() const;
};

#endif  // EPISODES_LIST_H
