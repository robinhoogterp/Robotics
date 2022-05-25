cmake_minimum_required(VERSION 3.0)

project(motor)

set(SERVOS
"Servos/softServo.c"
"Servos/softServo.h"
"Servos/DxlException.cpp"
"Servos/DxlException.hh"
"Servos/DxlServo.cpp"
"Servos/DxlServo.hh"
"Servos/dynamixel.c"
"Servos/dynamixel.h"
"Servos/dxl_hal.c"
"Servos/dxl_hal.h"
) 



# Locate libraries and headers
find_package(WiringPi REQUIRED)

# Include headers
include_directories(.)
include_directories(${WIRINGPI_INCLUDE_DIRS}) 
add_subdirectory(wiringPi)


add_executable(motor Motor.cpp)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
target_link_libraries(motor ${WIRINGPI_LIBRARIES})




