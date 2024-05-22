#ifndef PLATFORM_H_ 
#define PLATFORM_H_

#include "vector.h"
#include "character.h"

class Platform {
    private:
        Vector position;
        Vector size; //ancho x alto

    public:
        Platform(Vector startPosition, Vector platformSize): 
        position(startPosition), size(platformSize) {}

        Vector getPosition() const {
            return position;
        }

        Vector getSize() const {
            return size;
        }
        bool isColliding(const Character& character) const {
            // Lógica de detección de colisiones entre la trampa y el personaje
            Vector charPos = character.getPosition();
            return (charPos.x < position.x + size.x && charPos.x 
                    + character.getVelocity().x > position.x 
                    &&
                    charPos.y < position.y + size.y && charPos.y 
                    + character.getVelocity().y > position.y);
        }
};

#endif // PLATFORM_H_   

