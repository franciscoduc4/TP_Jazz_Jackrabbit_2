#include "episodesList.h"

EpisodesListDTO::EpisodesListDTO() : CommandDTO(Command::EPISODES_LIST) {}

EpisodesListDTO::EpisodesListDTO(std::vector<std::string> episodes) : CommandDTO(Command::EPISODES_LIST) {
    for (uint32_t i = 0; i < episodes.size(); i++) {
        this->episodesMap[i] = episodes[i];
    }
}

std::map<uint32_t, std::string> EpisodesListDTO::getEpisodesMap() const {
    return episodesMap;
}

std::vector<std::string> EpisodesListDTO::getEpisodes() const {
    std::vector<std::string> episodes;
    for (const auto& episode : episodesMap) {
        episodes.push_back(episode.second);
    }
    return episodes;
}
