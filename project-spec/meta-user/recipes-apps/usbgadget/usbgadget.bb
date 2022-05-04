#
# This file is the usbgadget recipe.
#

SUMMARY = "Simple usbgadget application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://usbgadget \
	"

S = "${WORKDIR}"

inherit update-rc.d

INITSCRIPT_NAME = "usbgadget"
INITSCRIPT_PARAMS = "start 99 S ."

do_install() {
	     install -d ${D}/${sysconfdir}/init.d
	     install -m 0755 ${S}/usbgadget ${D}/${sysconfdir}/init.d/usbgadget
}

FILES_${PN} += "${sysconfdir}/*"
