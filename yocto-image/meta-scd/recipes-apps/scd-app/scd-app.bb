

SUMMARY = "Smart cloud door application"
DESCRIPTION = "utilises databases to log and authenticate users at corporate doors and departments"

# The license for the recipe
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"


S = "${WORKDIR}"

SRC_URI = "file://main.cpp \
            file://app/app.cpp \
            file://app/app.h \
            file://database/database.cpp \
            file://database/database.h \
            file://hw/keypad.cpp \
            file://hw/keypad.h \
            file://hw/led.cpp \
            file://hw/led.h \
            file://hw/lcd.cpp \
            file://hw/lcd.h \
            file://hw/err.h \
            file://CMakeLists.txt"



DEPENDS += "soci postgresql"

CXXFLAGS += "-std=c++17"


inherit cmake
