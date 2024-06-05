#include "./receiverThread.h"

ReceiverThread::ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed) :
        deserializer(deserializer),
        socket(socket),
        was_closed(was_closed),
        closed(false) {}

void ReceiverThread::run() {
    while (!this->was_closed.load() && _keep_running) {
        try {
            uint8_t dtoSize;
            socket->recvall(&dtoSize, sizeof(uint8_t), &closed);
            std::unique_ptr<DTO> msgDto;
            socket->recvall(&msgDto, dtoSize, &closed);
            deserializer.deserialize_msg(msgDto);


        } catch (const std::exception& e) {
            if (!this->was_closed.load() || _keep_running) {
                std::cerr << "ReceiverThread error: " << e.what() << std::endl;
            }
        }
    }
}