#!/bin/bash

# Set exit when any command fails
set -e

# Remove old files if previously installed
if [ -d "build" ]; then
    sudo rm -rf build
fi