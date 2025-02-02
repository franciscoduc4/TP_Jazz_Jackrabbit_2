#include "soundController.h"
#include "../Common/Config/ClientConfig.h"
#include "../../Common/Types/entity.h"

#include <iterator>
#include <iostream>

enum lvl {BEACH, COLONIUS, HOLIDAIUS};

SoundController::SoundController(uint8_t leveltype) {
    std::vector<SoundType> soundsType{ SoundType::BACKSOUND, SoundType::PLAYERHURT, SoundType::SHOOT, SoundType::GETPOINT, SoundType::INTOXICATED };
    int soundsIndex = 0;
    
    switch (leveltype) {
        case COLONIUS:{
            //COLONIUS
            std::string coloniusBackSound = ClientConfig::getColoniusBacksound();
            this->sounds_paths[soundsType[soundsIndex]] = coloniusBackSound;
            break;
        }
        case HOLIDAIUS: {
            std::string holidaiusBackSound = ClientConfig::getHolidaiusBacksound();
            this->sounds_paths[soundsType[soundsIndex]] = holidaiusBackSound;
            break;

        }
        default:{
            //Beach
            std::string beachBackSound = ClientConfig::getBeachBacksound();
            this->sounds_paths[soundsType[soundsIndex]] = beachBackSound;
            break;
        }
        
    }
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
    }
    Mix_PlayChannel(-1, this->chunks[soundType], 0);
}

void SoundController::play_players_effect(std::vector<PlayerDTO>& players) {
    for (const auto& p: players) {
        switch (p.getState()) {
            //case CharacterStateEntity::SHOOTING:
            //    play_sound_effect(SoundType::SHOOT);
            //    break;
            case CharacterStateEntity::TAKING_DAMAGE:
                play_sound_effect(SoundType::PLAYERHURT);
                break;
            //case CharacterStateEntity::INTOXICATED:
            //    play_sound_effect(SoundType::INTOXICATED);
            //    break;
        }
    }
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