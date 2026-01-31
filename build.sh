#!/bin/bash

SOURCE_DIR="src" # Default source directory

if [ -n "$1" ]; then # Check if an argument is provided
    if [ "$1" == "src" ] || [ "$1" == "src_id" ]; then
        SOURCE_DIR="$1"
    else
        echo "Invalid argument: $1. Compiling from 'src' directory by default."
    fi
else
    echo "No source directory specified. Compiling from 'src' directory by default."
fi

echo "Compiling from: $SOURCE_DIR"
clang++ -Wall -std=c++17 -I./"$SOURCE_DIR" "$SOURCE_DIR"/main.cpp "$SOURCE_DIR"/errorHandler.cpp "$SOURCE_DIR"/ioUtil.cpp "$SOURCE_DIR"/moneyUtil.cpp "$SOURCE_DIR"/orchestrator.cpp "$SOURCE_DIR"/tramUtil.cpp "$SOURCE_DIR"/uiUtil.cpp -o build/tam

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running program..."
    ./build/tam
else
    echo "Compilation failed."
fi