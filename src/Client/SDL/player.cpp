#include "player.h"

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "../../Common/sprite.h"

#include "projectile.h"

enum character_type { Jazz, Lori, Spaz };
enum type_mov { Walk, Shoot, Run, Jump, Dash };

Player::Player(int character) {
    switch (character) {
        case Jazz:
            this->image_path = "../assets/Characters/Jazz.png";

            for (int i = 0; i < 8; i++) {
                this->sprites[Walk].push_back(Sprite(57 * i, 790, 57, 46));
                this->sprites[Run].push_back(Sprite(67 * i, 853, 67, 39));
            }

            this->sprites[Shoot].push_back(Sprite(0, 557, 47, 57));
            this->sprites[Shoot].push_back(Sprite(51, 557, 45, 57));
            this->sprites[Shoot].push_back(Sprite(101, 557, 36, 57));
            this->sprites[Shoot].push_back(Sprite(143, 557, 37, 57));
            this->sprites[Shoot].push_back(Sprite(185, 557, 36, 57));
            this->sprites[Shoot].push_back(Sprite(226, 557, 39, 57));
            this->sprites[Shoot].push_back(Sprite(265, 557, 54, 57));

            this->sprites[Jump].push_back(Sprite(0, 1197, 50, 60));
            this->sprites[Jump].push_back(Sprite(53, 1197, 36, 60));
            this->sprites[Jump].push_back(Sprite(89, 1197, 43, 60));
            this->sprites[Jump].push_back(Sprite(132, 1197, 46, 60));
            this->sprites[Jump].push_back(Sprite(178, 1197, 48, 60));
            this->sprites[Jump].push_back(Sprite(226, 1197, 52, 60));
            this->sprites[Jump].push_back(Sprite(278, 1197, 51, 60));
            this->sprites[Jump].push_back(Sprite(329, 1197, 53, 60));
            this->sprites[Jump].push_back(Sprite(383, 1197, 45, 60));
            this->sprites[Jump].push_back(Sprite(429, 1197, 36, 60));
            this->sprites[Jump].push_back(Sprite(465, 1197, 35, 60));
            this->sprites[Jump].push_back(Sprite(500, 1197, 37, 60));

            this->sprites[Dash].push_back(Sprite(0, 909, 45, 65));
            this->sprites[Dash].push_back(Sprite(45, 909, 43, 65));
            this->sprites[Dash].push_back(Sprite(90, 909, 45, 65));
            this->sprites[Dash].push_back(Sprite(135, 909, 52, 65));
            this->sprites[Dash].push_back(Sprite(188, 909, 55, 65));
            this->sprites[Dash].push_back(Sprite(243, 909, 53, 65));
            this->sprites[Dash].push_back(Sprite(295, 909, 65, 65));
            this->sprites[Dash].push_back(Sprite(360, 909, 66, 65));
            this->sprites[Dash].push_back(Sprite(426, 909, 68, 65));
            this->sprites[Dash].push_back(Sprite(495, 909, 67, 65));
            this->sprites[Dash].push_back(Sprite(562, 909, 67, 65));
            this->sprites[Dash].push_back(Sprite(629, 909, 61, 65));
            this->sprites[Dash].push_back(Sprite(690, 909, 58, 65));
            this->sprites[Dash].push_back(Sprite(0, 993, 70, 41));
            this->sprites[Dash].push_back(Sprite(72, 993, 64, 41));
            this->sprites[Dash].push_back(Sprite(137, 993, 69, 41));
            this->sprites[Dash].push_back(Sprite(207, 993, 69, 41));

            break;
        case Lori:
            this->image_path = "../assets/Characters/Lori.png";

            for (int i = 0; i < 8; i++) {
                this->sprites[Walk].push_back(Sprite(51 * i, 556, 51, 51));
                this->sprites[Run].push_back(Sprite(55 * i, 626, 55, 42));
            }

            this->sprites[Shoot].push_back(Sprite(0, 341, 48, 56));
            this->sprites[Shoot].push_back(Sprite(50, 341, 43, 56));
            this->sprites[Shoot].push_back(Sprite(100, 341, 38, 56));
            this->sprites[Shoot].push_back(Sprite(140, 341, 37, 56));
            this->sprites[Shoot].push_back(Sprite(180, 341, 40, 56));
            this->sprites[Shoot].push_back(Sprite(220, 341, 40, 56));

            this->sprites[Jump].push_back(Sprite(0, 963, 48, 70));
            this->sprites[Jump].push_back(Sprite(50, 963, 45, 70));
            this->sprites[Jump].push_back(Sprite(98, 963, 44, 70));
            this->sprites[Jump].push_back(Sprite(145, 963, 45, 70));
            this->sprites[Jump].push_back(Sprite(190, 963, 45, 70));
            this->sprites[Jump].push_back(Sprite(235, 963, 52, 70));
            this->sprites[Jump].push_back(Sprite(288, 963, 52, 70));
            this->sprites[Jump].push_back(Sprite(340, 963, 52, 70));
            this->sprites[Jump].push_back(Sprite(392, 963, 53, 70));
            this->sprites[Jump].push_back(Sprite(445, 963, 37, 70));
            this->sprites[Jump].push_back(Sprite(485, 963, 40, 70));
            this->sprites[Jump].push_back(Sprite(525, 963, 40, 70));
            this->sprites[Jump].push_back(Sprite(565, 963, 40, 70));

            break;
        case Spaz:
            this->image_path = "../assets/Characters/Spaz.png";

            for (int i = 0; i < 8; i++) {
                this->sprites[Walk].push_back(Sprite(50 * i, 747, 50, 45));
            }

            this->sprites[Run].push_back(Sprite(0, 807, 48, 40));
            this->sprites[Run].push_back(Sprite(48, 807, 58, 40));
            this->sprites[Run].push_back(Sprite(106, 807, 52, 40));
            this->sprites[Run].push_back(Sprite(160, 807, 48, 40));
            this->sprites[Run].push_back(Sprite(210, 807, 48, 40));
            this->sprites[Run].push_back(Sprite(260, 807, 54, 40));
            this->sprites[Run].push_back(Sprite(315, 807, 50, 40));
            this->sprites[Run].push_back(Sprite(366, 807, 50, 40));

            this->sprites[Shoot].push_back(Sprite(0, 539, 52, 48));
            this->sprites[Shoot].push_back(Sprite(53, 539, 50, 48));
            this->sprites[Shoot].push_back(Sprite(105, 539, 48, 48));
            this->sprites[Shoot].push_back(Sprite(153, 539, 36, 48));
            this->sprites[Shoot].push_back(Sprite(190, 539, 42, 48));
            this->sprites[Shoot].push_back(Sprite(232, 539, 47, 48));

            this->sprites[Jump].push_back(Sprite(0, 1139, 44, 55));
            this->sprites[Jump].push_back(Sprite(44, 1139, 36, 55));
            this->sprites[Jump].push_back(Sprite(81, 1139, 40, 55));
            this->sprites[Jump].push_back(Sprite(122, 1139, 42, 55));
            this->sprites[Jump].push_back(Sprite(165, 1139, 38, 55));
            this->sprites[Jump].push_back(Sprite(205, 1139, 40, 55));
            this->sprites[Jump].push_back(Sprite(245, 1139, 40, 55));
            this->sprites[Jump].push_back(Sprite(287, 1139, 43, 55));
            this->sprites[Jump].push_back(Sprite(330, 1139, 45, 55));
            this->sprites[Jump].push_back(Sprite(378, 1139, 34, 55));
            this->sprites[Jump].push_back(Sprite(415, 1139, 33, 55));
            this->sprites[Jump].push_back(Sprite(450, 1139, 34, 55));

            break;
    }
}

std::string Player::getPath() { return this->image_path; }


std::list<Sprite>::iterator Player::img_coords(int mov_type, int num_mov) {
    std::list<Sprite>::iterator it = this->sprites[mov_type].begin();
    for (int i = 0; i != num_mov; i++) {
        ++it;
        if (it == this->sprites[mov_type].end()) {
            it = this->sprites[mov_type].begin();
        }
    }
    return it;
}


void Player::shoot(int x, int y, int flip) {
    Projectile p(4, x, y, flip);
    this->projectiles.push_back(p);
}


void Player::draw_projectiles(SDL2pp::Renderer& renderer, SDL2pp::Texture& projectile) {
    std::list<Projectile>::iterator it = this->projectiles.begin();

    while (it != this->projectiles.end()) {
        if (!it->draw_projectile(renderer, projectile)) {
            it = this->projectiles.erase(it);
        } else {
            ++it;
        }
    }
}
