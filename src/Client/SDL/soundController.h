#ifndef SOUND_CONTROLLER_H
#define SOUND_CONTROLLER_H

#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/Music.hh>

#include <map>
#include <string>
#include <memory>


class SoundController {
    std::map<int, std::string> sounds_paths;
    Mix_Music *backsound;

public:
    SoundController();

    void play_backsound();

    void stop_sound();

    void free_musics();
};

#endif