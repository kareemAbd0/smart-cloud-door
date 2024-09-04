SUMMARY = "linux 4x3 matrix keypad linux kernel module"
DESCRIPTION = "${SUMMARY}"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

inherit module

SRC_URI = "file://Makefile \
	file://keypad.c \
	file://keypad.h \
	file://keypad_platform_driver.c \
	file://keypad_platform_driver_data.h \
        file://COPYING \
          "




S = "${WORKDIR}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

