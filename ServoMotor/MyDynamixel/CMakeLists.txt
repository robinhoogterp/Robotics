cmake_minimum_required(VERSION 3.0)

project(Test)

set(SRC
"main.cpp"
"ServoClass.cpp"
"BTclient.cpp"
)

set(INCLUDE
"main.h"
"ServoClass.h"
"BTclient.h"
)

# Locate libraries and headers
find_package(WiringPi REQUIRED)
#find_package(Bluetooth REQUIRED)

# Include headers
include_directories(.)
include_directories(src)
include_directories(include)
#include_directories(${LIBBLUETOOTH_LIBRARIES})
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

add_subdirectory(wiringPi)

add_executable(Test ${SRC} ${INCLUDE})

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

target_link_libraries(Test ${WIRINGPI_LIBRARIES})
#target_link_libraries(Test ${LIBBLUETOOTH_LIBRARIES})




