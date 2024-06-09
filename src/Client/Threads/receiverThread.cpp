#include "./receiverThread.h"
#include "../../Common/Types/command.h"

ReceiverThread::ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed) :
        deserializer(deserializer),
        socket(socket),
        was_closed(was_closed),
        closed(false) {}

void ReceiverThread::run() {
    while (!this->was_closed.load() && _keep_running) {
        try {
            Command cmd;
            socket->recvall(&cmd, sizeof(char), &closed);
            uint8_t bufferSize;
            socket->recvall(&bufferSize, sizeof(uint8_t), &closed);
            std::vector<char> buffer(bufferSize);
            socket->recvall(&buffer[0], bufferSize, &closed);
            deserializer.deserialize_msg(cmd, buffer);   
        } catch (const std::exception& e) {
            if (!this->was_closed.load() || _keep_running) {
                std::cerr << "ReceiverThread error: " << e.what() << std::endl;
            }
        }
    }
}
