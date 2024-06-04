#include "cmdReaderThread.h"

CmdReader::CmdReader(Serializer& serializer, std::shared_ptr<Queue<DTO>>& playerCmdsQueue) :
        serializer(serializer),
        playerCmdsQueue(playerCmdsQueue) {}

void CmdReader::run() {
    while (_keep_running) {
        try {
            DTO cmd = this->playerCmdsQueue.pop();
            this->serializer.serialize(cmd);
        } catch (std::exception &e) {
            if (this->_keep_running) {
                stop();
            }
        }
    }
}