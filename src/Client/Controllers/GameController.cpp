#include "GameController.h"

GameController::GameController(Serializer& serializer, Deserializer& deserializer, std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue) :
        serializer(serializer),
        deserializer(deserializer),
        gameQueue(gameQueue) {}