#ifndef SOUND_CONTROLLER_H
#define SOUND_CONTROLLER_H

#include "../../Common/Types/sounds.h"
#include "../../Common/DTO/player.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Music.hh>

#include <map>
#include <string>
#include <memory>


class SoundController {
    std::map<SoundType, std::string> sounds_paths;
    std::map<SoundType, Mix_Chunk*> chunks;
    Mix_Music *backsound;
    //Mix_Chunk *playerHurt;

public:
    SoundController(uint8_t leveltype);

    void play_backsound();

    void stop_backsound();

    void play_sound_effect(SoundType soundType);

    void play_players_effect(std::vector<PlayerDTO>& players);

    void free_musics();
};

#endif