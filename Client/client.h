#ifndef CLIENT_H
#define CLIENT_H

class Client {
    private:
        char* ip;
        char* port;
    public:
        Client(char* ip, char* port);
        void start();
};

#endif  // CLIENT_H
