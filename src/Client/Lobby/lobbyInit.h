// #include "../client.h"

#ifndef CLIENT_LOBBY_LOBBYINIT_H
#define CLIENT_LOBBY_LOBBYINIT_H

class Client;

class LobbyInit {
public:
    LobbyInit();
    bool launchQT(Client& client, bool& clientJoinedGame);
};

#endif  // CLIENT_LOBBY_LOBBYINIT_H
