# src/CMakeLists.txt
# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src/Common)

# Dependencies
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(SDL2 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(fmt REQUIRED)

# Create common library
add_subdirectory(Common)

# Server
if(SERVER)
    add_subdirectory(Server)
endif()

# Client
if(CLIENT)
    add_subdirectory(Client)
endif()
