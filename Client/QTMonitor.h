#ifndef QTMONITOR_H
#define QTMONITOR_H

#include <mutex>
#include "../Common/protocol.h"
#include "../Common/serializer.h"
#include "./lobbyMessage.h"

class QTMonitor{
    private:
        Protocol& protocol;
        SenderThread& sender;
        ReceiverThread& receiver;
        Serializer serializer;
        std::mutex mutex;
    public:
        QTMonitor(Protocol& protocol, SenderThread& sender, ReceiverThread& receiver);
        void sendMessage(const LobbyMessage& message);
        ProtocolMessage receiveMessage();
};

#endif  // QTMONITOR_H
