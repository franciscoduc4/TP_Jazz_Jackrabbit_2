#include "senderThread.h"

SenderThread::SenderThread(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed):
    queue(queue),
    socket(socket),
    was_closed(was_closed),
    closed(false){}

void SenderThread::run() {
    try {
        while (_keep_running) {
            std::unique_ptr<DTO> msg = queue->pop();
            uint8_t msg_size = sizeof(msg);
            socket->sendall(&msg_size, sizeof(uint8_t), &closed);
            socket->sendall(&msg, msg_size, &closed);
            if (was_closed) {
                stop();
            }
        }
    } catch (std::exception e) {
        if (_keep_running) {
            std::cerr << "Ocurrio un error: " << e.what() << '\n';
            stop();
        }
    }
}

SenderThread::~SenderThread() {
    this->join();
}
