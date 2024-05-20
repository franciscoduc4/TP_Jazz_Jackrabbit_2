#include "./receiverThread.h"
#include "Common/Config/ClientConfig.h"

ReceiverThread::ReceiverThread(Socket& socket, Protocol& protocol) : 
    socket(socket), 
    protocol(protocol),
    serializer(),
    logger(ClientConfig::getLogger()) {}


void ReceiverThread::run() {
    while (!socket.isClosed() && this->_keep_running) {
        try {
            ProtocolMessage msg = protocol.recvMessage(socket);
            this->serializer.deserialize(msg);
        } catch (const std::exception& e) {
            logger.error(__func__, __LINE__, "Exception caught: %s", e.what());
            _keep_running = false;
        }
    }
}

ReceiverThread::~ReceiverThread() {
    logger.debug(__func__, __LINE__, "ReceiverThread destructor called");
    this->protocol.close();
    this->join();
}
