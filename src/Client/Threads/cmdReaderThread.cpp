#include "cmdReaderThread.h"

CmdReader::CmdReader(Serializer& serializer, std::shared_ptr<Queue<std::unique_ptr<DTO>>>& playerCmdsQueue) :
        serializer(serializer),
        playerCmdsQueue(playerCmdsQueue) {}

void CmdReader::run() {
    while (_keep_running) {
        try {
            std::unique_ptr<DTO> cmd(this->playerCmdsQueue->pop());
            this->serializer.sendMsg(cmd);
        } catch (std::exception &e) {
            if (this->_keep_running) {
                stop();
            }
        }
    }
}