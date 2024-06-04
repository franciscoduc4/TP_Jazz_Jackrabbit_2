#ifndef CMD_READER_H
#define CMD_READER_H

#include <memory>

#include "../../Common/queue.h"
#include "../Protocol/serializer.h"
#include "../../Common/thread.h"

class CmdReader : public Thread {
private:
    Serializer& serializer;
    std::shared_ptr<Queue<DTO>>& playerCmdsQueue;

public:
    CmdReader(Serializer& serializer, std::shared_ptr<Queue<DTO>>& playerCmdsQueue);

    void run() override;

    ~CmdReader();
};

#endif  // CMD_READER_H