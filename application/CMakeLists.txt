cmake_minimum_required(VERSION 3.6)
project(smart_cloud_door)

set(CMAKE_CXX_STANDARD 17)




find_package(SOCI REQUIRED postgresql)  # Find SOCI
# Find Boost
find_package(Boost REQUIRED COMPONENTS date_time)  # Specify the components you need

add_executable(smart_cloud_door main.cpp
        database/database.cpp
        database/database.h
        hw/lcd.cpp
        hw/lcd.h
        hw/led.cpp
        hw/led.h
        hw/keypad.cpp
        hw/keypad.h
        app/app.cpp
        app/app.h
        hw/err.h)


target_link_libraries(smart_cloud_door SOCI::soci_core SOCI::soci_postgresql)

# Specify installation
#install(TARGETS smart-cloud-door DESTINATION bin)
