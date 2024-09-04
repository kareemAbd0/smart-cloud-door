
include recipes-core/images/core-image-base.bb

SUMMARY = "Custom image for scd project"

COMPATIBLE_MACHINE = "^rpi$"

IMAGE_FEATURES += "ssh-server-openssh"
IMAGE_INSTALL:append = " packagegroup-rpi-test keypad-module gpio-module lcd-module scd-app postgresql sudo postgresql-init scd-startup"



