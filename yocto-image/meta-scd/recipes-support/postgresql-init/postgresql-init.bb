
SUMMARY = "PostgreSQL initialization script"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://postgresql-init.sh"

# Define where the script should be installed
do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/postgresql-init.sh ${D}${bindir}/postgresql-init.sh
}

FILES_${PN} += "${bindir}/postgresql-init.sh"
