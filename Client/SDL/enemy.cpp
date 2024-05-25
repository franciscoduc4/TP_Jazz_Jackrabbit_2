#include "enemy.h"

enum type_enemies { Turtle, Schartzen, YellowMons };
enum actions { Walk, Attack, Death };

Enemy::Enemy(int enemy) {
	switch(enemy) {
		case Turtle:
			this->path = "../assets/Enemies/TurtleEnemies.png";
			this->y_src[Walk] = 56;
			this->y_src[Attack] = 120;
			this->y_src[Death] = 9;
			
			this->heights[Walk] = 56;
			this->heights[Attack] = 50;
			this->heights[Death] = 42;
			
			this->widths[Walk][12] = 67;
			this->widths[Walk][80] = 69;
			this->widths[Walk][150] = 68;
			this->widths[Walk][220] = 66;
			this->widths[Walk][290] = 68;
			this->widths[Walk][360] = 61;
			this->widths[Walk][422] = 65;
			this->widths[Walk][487] = 65;
			this->widths[Walk][555] = 61;
			this->widths[Walk][616] = 63;
			this->widths[Walk][680] = 66;
			this->widths[Walk][746] = 68;
			
			this->widths[Attack][5] = 58;
			this->widths[Attack][63] = 60;
			this->widths[Attack][123] = 60;
			this->widths[Attack][183] = 77;
			this->widths[Attack][260] = 95;
			this->widths[Attack][357] = 99;
			this->widths[Attack][458] = 114;
			this->widths[Attack][572] = 120;
			this->widths[Attack][692] = 114;
			this->widths[Attack][809] = 84;
			this->widths[Attack][893] = 60;
			
			this->widths[Death][384] = 75;
			this->widths[Death][460] = 70;
			this->widths[Death][530] = 62;
			this->widths[Death][592] = 52;
			this->widths[Death][644] = 47;
			this->widths[Death][691] = 42;
			
			break;
		case Schartzen: 
			this->path = "../assets/Enemies/Schwartzenguard.png";
			this->y_src[Walk] = 6;
			//this->y_src[Attack] = ;
			this->y_src[Death] = 207;
			
			this->heights[Walk] = 56;
			//this->heights[Attack] = ;
			this->heights[Death] = 61;
			
			this->widths[Walk][11] = 65;
			this->widths[Walk][79] = 59;
			this->widths[Walk][142] = 46;
			this->widths[Walk][190] = 53;
			this->widths[Walk][248] = 66;
			this->widths[Walk][316] = 73;
			this->widths[Walk][391] = 61;
			this->widths[Walk][452] = 53;
			this->widths[Walk][505] = 50;
			this->widths[Walk][555] = 67;
			
			
			this->widths[Death][384] = 41;
			this->widths[Death][426] = 44;
			this->widths[Death][470] = 61;
			this->widths[Death][531] = 56;
			this->widths[Death][531] = 56;
			this->widths[Death][531] = 56;
			this->widths[Death][531] = 56;
			this->widths[Death][531] = 56;
			
			break;
			
		case YellowMons:
			this->path = "../assets/Enemies/Enemies.png";
			this->y_src[Walk] = 9;
			this->y_src[Attack] = 75;
			this->y_src[Death] = 10;
			
			this->heights[Walk] = 66;
			this->heights[Attack] = 78;
			this->heights[Death] = 63;
			
			this->widths[Walk][14] = 70;
			this->widths[Walk][93] = 62;
			this->widths[Walk][161] = 53;
			this->widths[Walk][214] = 77;
			this->widths[Walk][300] = 58;
			this->widths[Walk][365] = 60;
			this->widths[Walk][430] = 67;
			this->widths[Walk][505] = 70;
			this->widths[Walk][593] = 73;
			this->widths[Walk][675] = 70;
			this->widths[Walk][750] = 75;
			this->widths[Walk][830] = 77;
			
			this->widths[Attack][355] = 45;
			this->widths[Attack][410] = 60;
			this->widths[Attack][475] = 62;
			this->widths[Attack][542] = 60;
			this->widths[Attack][614] = 70;
			this->widths[Attack][695] = 46;
			
			this->widths[Death][917] = 33;
			this->widths[Death][953] = 36;
			this->widths[Death][990] = 35;
			this->widths[Death][1030] = 35;
			this->widths[Death][1030] = 35;
			this->widths[Death][1030] = 35;
			this->widths[Death][1030] = 35;
			this->widths[Death][1030] = 35;

			
			break;

	}
}

std::string Enemy::getPath() {
	return this->path;
}

int Enemy::getYsrc(int mov_type) {
	return this->y_src[mov_type];
}

std::map<int, int>::iterator Enemy::widthSrc(int mov_type, int num_mov) {
	std::map<int, int>::iterator it = this->widths[mov_type].begin();
	for (int i = 0; i != num_mov; i++) {
		++it;
		if (it == this->widths[mov_type].end()) {
			it = this->widths[mov_type].begin();
		}
	}
	return it;
}

int Enemy::heightSrc(int mov_type) {
	return this->heights[mov_type];
}

