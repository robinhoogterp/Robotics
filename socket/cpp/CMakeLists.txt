cmake_minimum_required(VERSION 3.13)
project(start)

set(CMAKE_CXX_STANDARD 14)
set(SOURCES start.cpp include/ randomValues.cpp telemetryPipe.cpp telemetrics.cpp)


add_executable(start ${SOURCES})