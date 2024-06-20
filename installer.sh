#!/bin/bash

# Set exit when any command fails
set -e

# Update and install dependencies
sudo apt-get update
sudo apt-get install -y build-essential cmake git libyaml-cpp-dev libfmt-dev
sudo apt-get install -y qtbase5-dev qtdeclarative5-dev qt5-qmake qttools5-dev-tools libqt5widgets5 libqt5core5a
sudo apt-get install -y libgtest-dev
sudo apt-get install -y libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev
sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-gfx-dev

# Remove old files if previously installed
if [ -d "build" ]; then
    sudo rm -rf build
fi

# Install the required font
sudo cp assets/Miscellaneous/Jazz-Jackrabbit-2.ttf /usr/share/fonts/

# Create build directory and build the project
sudo mkdir -p build
cd build
sudo cmake ..
sudo make -j$(nproc)
sudo make install
cd ..
