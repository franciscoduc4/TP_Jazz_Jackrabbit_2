#include "./receiverThread.h"

ReceiverThread::ReceiverThread(Deserializer& deserializer, std::shared_pty<Socket>& socket, std::atomic<bool>& was_closed) :
        deserializer(deserializer),
        socket(socket),
        was_closed(was_closed),
        closed(false) {}

void ReceiverThread::run() {
    while (!this->was_closed.load() && _keep_running) {
        try {
            uint8_t dtoSize;
            socket->recvall(&dtoSize, sizeof(uint8_t), &was_closed);
            DTO msgDto;
            socket->recvall(&msgDto, dtoSize, &was_closed);
            deserializer.deserialize_msg(msgDto);


        } catch (const std::exception& e) {
            if (!this->was_closed.load() || _keep_running) {
                std::cerr << "ReceiverThread error: " << e.what() << std::endl;
            }
        }
    }
}