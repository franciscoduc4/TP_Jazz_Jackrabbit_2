#ifndef CLIENT_PLAYER_H_
#define CLIENT_PLAYER_H_

#include <list>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"
#include "../../Common/DTO/player.h"
#include "../../Common/Types/character.h"
#include "../../Common/Types/entity.h"

#include "projectile.h"

class Player {
    std::map<CharacterType, std::string> image_path;
    std::map<CharacterType, std::map<int, std::list<RectangularSprite>>> sprites;
    std::list<Projectile> projectiles;
	std::map<int, std::map<CharacterStateEntity, int>> counts;
    std::map<int, CharacterStateEntity> last_move;
    bool init;
	int width;
	int height;
	int flip;


public:
    Player();

    std::string getPath(CharacterType character);

    std::list<RectangularSprite>::iterator img_coords(CharacterType character, CharacterStateEntity mov_type, int pjId);

	void draw_players(SDL2pp::Window& window, SDL2pp::Renderer& renderer, std::map<CharacterType, std::unique_ptr<SDL2pp::Texture>>& pjs_textures, std::vector<PlayerDTO>& players, int dir_x_screen, int dir_y_screen, uint32_t mainPlayerId);
	
    std::map<CharacterType, std::unique_ptr<SDL2pp::Texture>> getPlayersTextures(SDL2pp::Renderer& renderer);

};

#endif  // CLIENT_PLAYER_H_
