#include "episodesList.h"

EpisodesListDTO::EpisodesListDTO(): CommandDTO(Command::EPISODES_LIST) {}

EpisodesListDTO::EpisodesListDTO(std::map<int, std::string> episodes):
        CommandDTO(Command::EPISODES_LIST) {
    for (const auto& [id, mapName]: episodes) {
        episodesMap[id] = mapName;
    }
}

std::map<uint32_t, std::string> EpisodesListDTO::getEpisodesMap() const { return episodesMap; }

std::map<int, std::string> EpisodesListDTO::getEpisodes() const {
    std::map<int, std::string> episodes;
    for (const auto& [id, mapName]: episodesMap) {
        episodes[id] = mapName;
    }
    return episodes;
}
