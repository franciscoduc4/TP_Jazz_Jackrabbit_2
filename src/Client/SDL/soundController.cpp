#include "soundController.h"

#include <iterator>
#include <iostream>

enum s_type { BACKSOUND };

SoundController::SoundController() {
    this->sounds_paths[BACKSOUND] = "../assets/audios/beachBackSound.wav";   
}

void SoundController::play_backsound() {
    backsound = Mix_LoadMUS(this->sounds_paths[BACKSOUND].c_str());
    Mix_PlayMusic(backsound, -1);
}

void SoundController::stop_sound() {
    Mix_PauseMusic();
}

void SoundController::free_musics() {
    Mix_FreeMusic(backsound);

}