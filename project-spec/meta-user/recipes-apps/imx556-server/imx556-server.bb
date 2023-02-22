#
# This file is the imx556-server recipe.
#

SUMMARY = "Simple imx556-server application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://git@github.com:/Deep-In-Sight/imx556_server.git;protocol=ssh"
SRCREV = "da6689ea422ae2e5538f34ebba462ccf413833d1"

S = "${WORKDIR}/git"

FILES_${PN} += "/home/root/imx556_server /home/root/freqmod.txt /home/root/imx556_standard* /home/root/startCamera /home/root/enableAutoStart.sh"

#INSANE_SKIP_${PN} = "ldflags"
TARGET_CC_ARCH += "${LDFLAGS}"

do_compile() {
	     oe_runmake
}

do_install() {
		 mkdir -p ${D}/home/root/
		 cp build/apps/imx556_server ${D}/home/root/
		 cp freqmod.txt ${D}/home/root/
		 cp imx556_standard_*.cfg ${D}/home/root/
		 cp startCamera ${D}/home/root/
		 cp enableAutoStart.sh ${D}/home/root/
		 chmod 755 ${D}/home/root/startCamera
		 chmod 755 ${D}/home/root/enableAutoStart.sh
		 
		 cd ${D}/home/root/
		 ln -s -r imx556_standard_and.cfg imx556_standard.cfg
		
	     #install -m 0755 build/apps/imx556_server ${D}${bindir}
}
