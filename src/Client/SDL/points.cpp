#include "points.h"

#include <SDL2pp/SDL2pp.hh>
#include <list>

enum lvl { lvl1, lvl2 };
enum points { RedGem, GoldCoin, SilverCoin };

Points::Points(int level_type) {
	this->draw_width = 20;
	this->draw_height = 20;
	

	this->sprites[RedGem].push_back(Sprite(145, 1240, 31, 30));
	this->sprites[RedGem].push_back(Sprite(176, 1240, 29, 30));
	this->sprites[RedGem].push_back(Sprite(205, 1240, 28, 30));
	this->sprites[RedGem].push_back(Sprite(233, 1240, 29, 30));
	this->sprites[RedGem].push_back(Sprite(262, 1240, 29, 30));
	this->sprites[RedGem].push_back(Sprite(291, 1240, 29, 30));
	this->sprites[RedGem].push_back(Sprite(320, 1240, 29, 30));
	this->sprites[RedGem].push_back(Sprite(349, 1240, 30, 30));
	
	this->sprites[GoldCoin].push_back(Sprite(481, 1218, 27, 27));
	this->sprites[GoldCoin].push_back(Sprite(508, 1218, 35, 27));
	this->sprites[GoldCoin].push_back(Sprite(533, 1218, 23, 27));
	this->sprites[GoldCoin].push_back(Sprite(556, 1218, 19, 27));
	this->sprites[GoldCoin].push_back(Sprite(575, 1218, 15, 27));
	this->sprites[GoldCoin].push_back(Sprite(590, 1218, 10, 27));
	this->sprites[GoldCoin].push_back(Sprite(600, 1218, 15, 27));
	this->sprites[GoldCoin].push_back(Sprite(615, 1218, 19, 27));
	this->sprites[GoldCoin].push_back(Sprite(634, 1218, 24, 27));
	this->sprites[GoldCoin].push_back(Sprite(658, 1218, 26, 27));
	this->sprites[GoldCoin].push_back(Sprite(684, 1218, 26, 27));
	this->sprites[GoldCoin].push_back(Sprite(710, 1218, 26, 27));
	this->sprites[GoldCoin].push_back(Sprite(736, 1218, 24, 27));
	this->sprites[GoldCoin].push_back(Sprite(760, 1218, 19, 27));
	this->sprites[GoldCoin].push_back(Sprite(779, 1218, 15, 27));
	this->sprites[GoldCoin].push_back(Sprite(794, 1218, 10, 27));
	this->sprites[GoldCoin].push_back(Sprite(804, 1218, 14, 27));
	this->sprites[GoldCoin].push_back(Sprite(818, 1218, 18, 27));
	this->sprites[GoldCoin].push_back(Sprite(836, 1218, 23, 27));
	this->sprites[GoldCoin].push_back(Sprite(859, 1218, 23, 27));
	
	this->sprites[SilverCoin].push_back(Sprite(482, 1266, 27, 26));
	this->sprites[SilverCoin].push_back(Sprite(509, 1266, 33, 26));
	this->sprites[SilverCoin].push_back(Sprite(532, 1266, 23, 26));
	this->sprites[SilverCoin].push_back(Sprite(555, 1266, 18, 26));
	this->sprites[SilverCoin].push_back(Sprite(573, 1266, 14, 26));
	this->sprites[SilverCoin].push_back(Sprite(587, 1266, 10, 26));
	this->sprites[SilverCoin].push_back(Sprite(597, 1266, 15, 26));
	this->sprites[SilverCoin].push_back(Sprite(612, 1266, 19, 26));
	this->sprites[SilverCoin].push_back(Sprite(631, 1266, 24, 26));
	this->sprites[SilverCoin].push_back(Sprite(655, 1266, 26, 26));
	this->sprites[SilverCoin].push_back(Sprite(681, 1266, 26, 26));
	this->sprites[SilverCoin].push_back(Sprite(707, 1266, 27, 26));
	this->sprites[SilverCoin].push_back(Sprite(734, 1266, 24, 26));
	this->sprites[SilverCoin].push_back(Sprite(758, 1266, 19, 26));
	this->sprites[SilverCoin].push_back(Sprite(777, 1266, 15, 26));
	this->sprites[SilverCoin].push_back(Sprite(792, 1266, 10, 26));
	this->sprites[SilverCoin].push_back(Sprite(802, 1266, 15, 26));
	this->sprites[SilverCoin].push_back(Sprite(817, 1266, 19, 26));
	this->sprites[SilverCoin].push_back(Sprite(836, 1266, 24, 26));
	this->sprites[SilverCoin].push_back(Sprite(860, 1266, 15, 26));
	
	
	
	switch (level_type) {
		case lvl1:
			this->cant_redgems = 5;
			this->cant_goldcoin = 10;
			this->cant_silvercoin = 20;
	
	}
	int i;
	int x = 0; 
	int y = 100;
	for (i = 0; i < this->cant_redgems; i++) {
		std::vector v({x, y});
		this->redgems.push_back(v);
		x += 90;
		
	}
	this->counts.push_back(0);

	y += 100;
	x = 0;
	for (i = 0; i < this->cant_goldcoin; i++) {
		std::vector v2({x, y});
		this->goldcoin.push_back(v2);
		x += 60;
		
	}
	this->counts.push_back(0);

	y += 100;
	x = 0;
	for (i = 0; i < this->cant_silvercoin; i++) {
		std::vector v3({x, y});
		this->silvercoin.push_back(v3);
		x += 40;		
	}
	this->counts.push_back(0);
	

}


std::list<Sprite>::iterator Points::actual_sprite_coord(int typepoint) {
	std::list<Sprite>::iterator it = this->sprites[typepoint].begin();
	for (int i = 0; i < this->counts[typepoint]; i++) {
		++it;
		if (it == this->sprites[typepoint].end()) {
			it = this->sprites[typepoint].begin();
		}
	}
	return it;
}

void Points::draw_points(SDL2pp::Renderer& renderer, SDL2pp::Texture& points) {
	int index_x = 0;
	int index_y = 1;
	std::list<Sprite>::iterator it;
	for (int i = 0; i < this->cant_redgems; i++) {
		it = actual_sprite_coord(RedGem);
		renderer.Copy(points, SDL2pp::Rect(it->x, it->y, it->width, it->height), 
				SDL2pp::Rect(this->redgems[i][index_x], this->redgems[i][index_y], this->draw_width, this->draw_height), 0.0, SDL2pp::NullOpt, 0);
	}
	this->counts[RedGem]++;
	

	for (int i = 0; i < this->cant_goldcoin; i++) {
		it = actual_sprite_coord(GoldCoin);
		renderer.Copy(points, SDL2pp::Rect(it->x, it->y, it->width, it->height), 
				SDL2pp::Rect(this->goldcoin[i][index_x], this->goldcoin[i][index_y], this->draw_width, this->draw_height), 0.0, SDL2pp::NullOpt, 0);
	}
	this->counts[GoldCoin]++;	
	
	
	for (int i = 0; i < this->cant_silvercoin; i++) {
		it = actual_sprite_coord(SilverCoin);
		renderer.Copy(points, SDL2pp::Rect(it->x, it->y, it->width, it->height), 
				SDL2pp::Rect(this->silvercoin[i][index_x], this->silvercoin[i][index_y], this->draw_width, this->draw_height), 0.0, SDL2pp::NullOpt, 0);
	}	
	this->counts[SilverCoin]++;		
	
}


void Points::verify_point_obtained(SDL2pp::Rect& player_rect) {
	int index_x = 0;
	int index_y = 1;
	int i = 0;
	bool obtained = false;
	std::vector<std::vector<int>>::iterator it = this->redgems.begin();
	while (it != this->redgems.end()) {
		SDL2pp::Rect gem_rect = SDL2pp::Rect(this->redgems[i][index_x], this->redgems[i][index_y], this->draw_width, this->draw_height);
		if (gem_rect.GetIntersection(player_rect) != SDL2pp::NullOpt) {
			this->cant_redgems--;
			obtained = true;
			break;
		}
		++it;
		i++;
	}
	if (obtained) {
		this->redgems.erase(it);
		return;
	}
	
	i = 0;
	it = this->goldcoin.begin();
	while (it != this->goldcoin.end()) {
		SDL2pp::Rect goldcoin_rect = SDL2pp::Rect(this->goldcoin[i][index_x], this->goldcoin[i][index_y], this->draw_width, this->draw_height);
		if (goldcoin_rect.GetIntersection(player_rect) != SDL2pp::NullOpt) {
			this->cant_goldcoin--;
			obtained = true;
			break;
		}
		++it;
		i++;
	}
	if (obtained) {
		this->goldcoin.erase(it);
		return;
	}
	i = 0;
	it = this->silvercoin.begin();
	while (it != this->silvercoin.end()) {
		SDL2pp::Rect silver_rect = SDL2pp::Rect(this->silvercoin[i][index_x], this->silvercoin[i][index_y], this->draw_width, this->draw_height);
		if (silver_rect.GetIntersection(player_rect) != SDL2pp::NullOpt) {
			this->cant_silvercoin--;
			obtained = true;
			break;
		}
		++it;
		i++;
	}
	if (obtained) {
		this->silvercoin.erase(it);
		return;
	}



}
