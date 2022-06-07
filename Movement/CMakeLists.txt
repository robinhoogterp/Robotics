cmake_minimum_required(VERSION 3.0)
project(movement)
# Locate libraries and headers
find_package(WiringPi REQUIRED)
# Include headers
include_directories(.)
include_directories(${WIRINGPI_INCLUDE_DIRS})
#add_subdirectory(wiringPi)
add_executable(movement Movement.cpp)
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(keyboard ${WIRINGPI_LIBRARIES})

