#!/bin/bash

HIGHLIGHT="\033[1;93m\033[44m"
HIGHLIGHT_INFO="\033[0;30m\033[103m"
HIGHLIGHT_ERROR="\033[1;97m\033[41m"
NC="\033[0m"

# Check if a directory was passed as a parameter
if [ $# -eq 0 ]; then
    echo -e "${HIGHLIGHT_ERROR}Please provide a directory.${NC}"
    echo -e "${HIGHLIGHT_INFO}Usage: ./precommit.sh <directory>${NC}"
    exit 1
fi

# Check if the parameter is a directory
if [ ! -d "$1" ]; then
    echo -e "${HIGHLIGHT_ERROR}$1 is not a directory.${NC}"
    exit 1
fi

# Find all .cpp and .h files in the directory and its subdirectories
files=$(find $1 -name '*.cpp' -o -name '*.h')

# Check if any files were found
if [ -z "$files" ]; then
    echo -e "${HIGHLIGHT_INFO}No .cpp or .h files found in directory $1${NC}"
    exit 0
fi

echo -e "${HIGHLIGHT}Running pre-commit for directory $1${NC}"
# Run pre-commit for all files found
pre-commit run --hook-stage manual --files $files