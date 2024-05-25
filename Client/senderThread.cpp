#include "senderThread.h"

#include <string>

SenderThread::SenderThread(Protocol& p, Socket& skt, Queue& cmdsQueue): 
    protocol(p), socket(skt), cmdsQueue(cmdsQueue) {
}


void SenderThread::run() {
    try {
        while (this->_keep_running) {
            ProtocolMessage accion = queue.pop();
            this->protocol.sendMessage(msg);
        }
    } catch {
        if (this->_keep_running) {
            stop();
        }
    }
}

void SenderThread::push_message(const ProtocolMessage& msg) {
    this->queue.push(msg);
}

SenderThread::~SendeThread() {
    //cerrar protocolo
    socket.close();
    this->join;
}

