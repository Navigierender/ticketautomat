#!/bin/bash

echo "Compiling..."
clang++ -Wall -std=c++17 main.cpp errorHandler.cpp ioUtil.cpp moneyUtil.cpp orchestrator.cpp tramUtil.cpp uiUtil.cpp -o tam

if [ $? -eq 0 ]; then
    echo "Compilation successful."
else
    echo "Compilation failed."
fi