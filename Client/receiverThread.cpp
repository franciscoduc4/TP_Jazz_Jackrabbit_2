#include "./receiverThread.h"
#include "../Common/Config/ClientConfig.h"

ReceiverThread::ReceiverThread(Protocol& protocol, GameStatusMonitor& monitor) : 
    protocol(protocol),
    serializer(),
    monitor(monitor),
    inLobby(true) {}

LobbyMessage ReceiverThread::recv_msg() {
    ProtocolMessage msg = protocol.recvMessage();
    return this->serializer.parseRecvMessage(msg);
}

void ReceiverThread::run() {
    
    try {
        while (!this->protocol.server_closed() || this->monitor.gameIsRunning()) {
            ProtocolMessage msg = protocol.recvMessage();
            // this->serializer.deserialize(msg);
        }
    } catch (const std::exception& e) {
        // logger.error(__func__, __LINE__, "Exception caught: %s", e.what());
        _keep_running = false;
    }
}

ReceiverThread::~ReceiverThread() {
    //logger.debug(__func__, __LINE__, "ReceiverThread destructor called");
    //this->protocol.close();
    this->join();
}
