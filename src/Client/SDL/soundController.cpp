#include "soundController.h"
#include "../Common/Config/ClientConfig.h"

#include <iterator>
#include <iostream>


SoundController::SoundController() {
    /* this->sounds_paths[SoundType::BACKSOUND] = "../assets/audios/beachBackSound.wav";
    this->sounds_paths[SoundType::PLAYERHURT] = "../assets/audios/playerHurt.WAV";
    this->sounds_paths[SoundType::SHOOT] = "../assets/audios/shoot3.WAV";
    this->sounds_paths[SoundType::GETPOINT] = "../assets/audios/takePoint.WAV"; */
    std::vector<SoundType> soundsType{ SoundType::BACKSOUND, SoundType::PLAYERHURT, SoundType::SHOOT, SoundType::GETPOINT};
    int soundsIndex = 0;
    
    //Beach
    std::string beachBackSound = ClientConfig::getBeachBacksound();
    this->sounds_paths[soundsType[soundsIndex]] = beachBackSound;
    soundsIndex++;
    std::vector<std::string> soundsFiles = ClientConfig::getSoundsFiles();
    for (int i = 0; i < soundsFiles.size(); i++) {
        this->sounds_paths[soundsType[soundsIndex]] = soundsFiles[i];
        soundsIndex++;
    }
}

void SoundController::play_backsound() {
    backsound = Mix_LoadMUS(this->sounds_paths[SoundType::BACKSOUND].c_str());
    Mix_PlayMusic(backsound, -1);
}

void SoundController::stop_backsound() {
    Mix_PauseMusic();
}

void SoundController::play_sound_effect(SoundType soundType) {
    if (!this->chunks[soundType]) {
        this->chunks[soundType] = Mix_LoadWAV(this->sounds_paths[soundType].c_str());
        std::cout << "PASO POR ACA\n";
    }
    Mix_PlayChannel(-1, this->chunks[soundType], 0);
    //playerHurt = Mix_LoadWAV(this->sounds_paths[SoundType::PLAYERHURT].c_str());
    //Mix_PlayChannel(-1, playerHurt, 0);
}

void SoundController::free_musics() {
    Mix_HaltChannel(-1);
    Mix_FreeMusic(backsound);
    std::map<SoundType, Mix_Chunk*>::iterator it = this->chunks.begin();
    while (it != this->chunks.end()) {
        Mix_FreeChunk(it->second);
        it++;
    }

}