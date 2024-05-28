#ifndef QTMONITOR_H
#define QTMONITOR_H

#include <mutex>
#include <string>
#include "../Common/protocol.h"
#include "../Common/serializer.h"
#include "./senderThread.h"
#include "./receiverThread.h"
#include "./lobbyMessage.h"

class QTMonitor{
    private:
        SenderThread& sender;
        ReceiverThread& receiver;
        Serializer serializer;
        std::mutex mutex;
    public:
        QTMonitor(SenderThread& sender, ReceiverThread& receiver);
        void send_message(const std::string& message);
        LobbyMessage recv_message();
};

#endif  // QTMONITOR_H
