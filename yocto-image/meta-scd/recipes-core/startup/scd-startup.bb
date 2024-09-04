SUMMARY = "scd startup systemd service"
DESCRIPTION = "This recipe installs a systemd service file for kernel modules and the application"

# The license for the recipe
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit systemd

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "scd-startup.service"

SRC_URI:append = " file://scd-startup.service "
FILES:${PN} += "${systemd_unitdir}/system/scd-startup.service"

do_install:append() {
  install -d ${D}/${systemd_unitdir}/system
  install -m 0644 ${WORKDIR}/scd-startup.service ${D}/${systemd_unitdir}/system
}
