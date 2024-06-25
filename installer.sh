#!/bin/bash

# Set exit when any command fails
set -e

# Update and install dependencies
sudo apt-get update
sudo apt-get install -y build-essential cmake git libyaml-cpp-dev libfmt-dev
sudo apt-get install -y libgl1-mesa-dev libglu1-mesa-dev libglew-dev
sudo apt-get install -y libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev
sudo apt-get install -y libgl-dev libegl-dev libfontconfig1-dev libinput-dev libfontconfig1-dev libfreetype6-dev libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev libxcb1-dev libxcb-cursor-dev libxcb-glx0-dev libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev libxcb-icccm4-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev libxcb-util-dev libxcb-xinerama0-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev

# Install Qt5
sudo apt-get install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
sudo apt-get install -y libqt5widgets5 libqt5gui5 libqt5dbus5 libqt5network5 libqt5core5a

# Install SDL2 and its extensions from Ubuntu repositories
sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

# Install and setup GTest
sudo apt-get install -y libgtest-dev libgmock-dev
cd /usr/src/googletest
sudo cmake .
sudo make
sudo cp lib/*.a /usr/lib

# Update library cache
sudo ldconfig

# Remove old files if previously installed
if [ -d "./build" ]; then
    sudo rm -rf build
fi

# Install the required font
sudo cp ./assets/Miscellaneous/Jazz-Jackrabbit-2.ttf /usr/share/fonts/

# Create build directory and build the project
sudo mkdir -p build
cd build
cmake ..
make -j$(nproc)
sudo make install
