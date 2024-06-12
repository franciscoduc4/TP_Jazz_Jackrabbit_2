#ifndef EPISODES_LIST_H
#define EPISODES_LIST_H

#include <vector>
#include <string>
#include <map>
#include "command.h"

class EpisodesListDTO : public CommandDTO {
private:
    std::map<uint32_t, std::string> episodesMap;

public:
    EpisodesListDTO();
    EpisodesListDTO(std::vector<std::string> episodes);

    std::map<uint32_t, std::string> getEpisodesMap() const;
    std::vector<std::string> getEpisodes() const;
};

#endif // EPISODES_LIST_H
