# src/CMakeLists.txt

# Incluir directorios de encabezados
include_directories(${PROJECT_SOURCE_DIR}/src/Common)

# Dependencias
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(fmt REQUIRED)

# Crear biblioteca común
add_library(common
    Common/socket.cpp
    Common/socket.h
    Common/resolver.cpp
    Common/resolver.h
    Common/protocol.cpp
    Common/protocol.h
    Common/Config/ClientConfig.cpp
    Common/Config/ClientConfig.h
    Common/Config/ServerConfig.cpp
    Common/Config/ServerConfig.h
    Common/Constants/lobbyCommands.h
    Common/Constants/playerCommands.h
    Common/Models/character.cpp
    Common/Models/character.h
    Common/Models/enemy.h
    Common/Models/gameStatus.h
    Common/Models/gameTypes.h
    Common/liberror.cpp
    Common/liberror.h
    Common/logger.h
    Common/printer.h
    Common/queue.h
    Common/queueMonitor.cpp
    Common/queueMonitor.h
    Common/resolvererror.cpp
    Common/resolvererror.h
    Common/thread.h
)

target_link_libraries(common yaml-cpp fmt::fmt -pthread)
target_include_directories(common PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

# Servidor
add_executable(server
    Server/main.cpp
    Server/server.cpp
    Server/server.h
    Server/Game/game.cpp
    Server/Game/game.h
    Server/Game/gameMonitor.cpp
    Server/Game/gameMonitor.h
    Server/Game/player.cpp
    Server/Game/player.h
    Server/LobbyCommand/createGameCommand.cpp
    Server/LobbyCommand/createGameCommand.h
    Server/LobbyCommand/invalidCommand.cpp
    Server/LobbyCommand/invalidCommand.h
    Server/LobbyCommand/joinGameCommand.cpp
    Server/LobbyCommand/joinGameCommand.h
    Server/LobbyCommand/listGamesCommand.cpp
    Server/LobbyCommand/listGamesCommand.h
    Server/LobbyCommand/lobbyCommand.cpp
    Server/LobbyCommand/lobbyCommand.h
    Server/Threads/acceptorThread.cpp
    Server/Threads/acceptorThread.h
    Server/Threads/broadcasterThread.cpp
    Server/Threads/broadcasterThread.h
    Server/Threads/gameLoopThread.h
    Server/Threads/gameloopThread.cpp
    Server/Threads/lobbyPlayerThread.cpp
    Server/Threads/lobbyPlayerThread.h
    Server/Threads/receiverThread.cpp
    Server/Threads/receiverThread.h
    Server/Threads/senderThread.cpp
    Server/Threads/senderThread.h
)

target_link_libraries(server common yaml-cpp fmt::fmt -pthread)
target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)

set_target_properties(server
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Cliente (si se implementa más adelante)
# add_executable(client
#     Client/main.cpp
#     Client/client.cpp
#     Client/client.h
#     Client/cmdReaderThread.cpp
#     Client/cmdReaderThread.h
#     Client/receiverThread.cpp
#     Client/receiverThread.h
#     Client/senderThread.cpp
#     Client/senderThread.h
# )
#
# target_link_libraries(client common Qt5::Widgets Qt5::Core SDL2 yaml-cpp fmt::fmt -pthread)
# target_include_directories(client PUBLIC ${PROJECT_SOURCE_DIR}/src/Common)
#
# set_target_properties(client
#     PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
# )
