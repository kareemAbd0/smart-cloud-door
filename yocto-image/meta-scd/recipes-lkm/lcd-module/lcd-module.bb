SUMMARY = "linux 16x2 linux kernel module"
DESCRIPTION = "${SUMMARY}"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

SRC_URI = "file://Makefile \
	file://lcd.c \
	file://lcd.h \
	file://lcd_platform_driver.c \
	file://lcd_platform_driver_data.h \
        file://COPYING \
          "




S = "${WORKDIR}"

