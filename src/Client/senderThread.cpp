#include "senderThread.h"

#include <string>

SenderThread::SenderThread(Protocol& protocol,
        Queue<ProtocolMessage>& cmdsQueue,
        GameStatusMonitor& gameMonitor) : 
        protocol(protocol),
        cmdsQueue(cmdsQueue),
        gameMonitor(gameMonitor) {
}

void SenderThread::run() {
    try {
        while (!(this->protocol.server_closed()) || this->gameMonitor.gameIsRunning()) {
            ProtocolMessage msg = cmdsQueue.pop();
            this->protocol.sendMessage(msg);
        }
    } catch (std::exception &e) {
        if (this->_keep_running) {
            stop();
        }
    }
}

void SenderThread::push_message(const ProtocolMessage& msg) {
    this->cmdsQueue.push(msg);
}

SenderThread::~SenderThread() {
    this->join();
}

