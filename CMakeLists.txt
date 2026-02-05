cmake_minimum_required(VERSION 3.10)
project(ticketautomat CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ticketautomat
    main.cpp
    errorHandler.cpp
    ioUtil.cpp
    moneyUtil.cpp
    orchestrator.cpp
    tramUtil.cpp
    uiUtil.cpp
)
