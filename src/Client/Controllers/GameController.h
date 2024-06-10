#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"
class GameController {
private:
    Serializer& serializer;
    Deserializer& deserializer;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue;
public:
    GameController(Serializer& serializer, Deserializer& deserializer, std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue);

};

#endif  // GAMECONTROLLER_H
