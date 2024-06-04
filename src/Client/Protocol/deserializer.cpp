#include "deserializer.h"
#include "../Common/command.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"


#include <vector>
#include <map>
#include <cstdint>


void Deserializer::deserialize_msg(DTO& dto) {
    switch (dto.getType()) {
        case COMMANDO_DTO:
            break;
        case LOBBY_DTO:
            break;
        case GAME_DTO:
			return show_snapshot(dto);
	}	
}

void Deserializer::lobby_msg(DTO& dto) {}

void Deserializer::command_msg(DTO& dto) {}

void Deserializer::snapshot_msg(DTO& dto) {
    client.setSnapshot(dto); ???????
}

