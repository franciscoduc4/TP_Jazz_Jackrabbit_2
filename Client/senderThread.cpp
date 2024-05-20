#include "senderThread.h"

#include <string>

SenderThread::SenderThread(Protocol& p, Socket& skt, Queue& cmdsQueue): 
    protocol(p), socket(skt), cmdsQueue(cmdsQueue) {
}


SenderThread::run() {
    try {
        while (this->_keep_running) {
            uint8_t accion = queue.pop();
            std::string args; //recibir las caracteristicas de la accion
            ProtocolMessage msg(accion, args);
            this->protocol.sendMessage(msg);
        }
    } catch {
        if (this->_keep_running) {
            stop();
        }
    }
}

SenderThread::~SendeThread() {
    //cerrar protocolo
    socket.close();
    this->join;
}

