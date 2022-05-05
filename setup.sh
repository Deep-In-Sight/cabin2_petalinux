source .petalinux/metadata

PROJECT=$(pwd)
PROJECT_NAME=$(basename $PROJECT)
MODULE=${MODULE:-"vdma-proxy"}
HARDWAREPATH=${PROJECT}
USER_DT=${PROJECT}/project-spec/meta-user/recipes-bsp/device-tree/files/
BOARD_DT=${PROJECT}/components/plnx_workspace/device-tree/device-tree/
KERNEL_SRC=${PROJECT}/build/tmp/work-shared/zynq-generic/kernel-source/
KERNEL_PATCH=${PROJECT}/project-spec/meta-user/recipes-kernel/linux/linux-xlnx/
MODULE_SRC=${PROJECT}/project-spec/meta-user/recipes-modules/${MODULE}/files/
IMAGES=${PROJECT}/images/linux/
PREBUILT=${PROJECT}/pre-built/linux/images/
BOOT_MNT=${BOOT_MNT:-"/media/$USER/boot"}
ROOTFS_MNT=${ROOTFS_MNT:-"/media/$USER/rootfs"}

if grep "ARCH_ARM=y" ${PROJECT}/project-spec/configs/config 1> /dev/null 2>&1 ; then
	ARCH=arm
	echo "ARCH=arm"
elif grep "ARCH_AARCH64=y" ${PROJECT}/project-spec/configs/config 1> /dev/null 2>&1 ; then
	ARCH=AARCH64
	echo "ARCH=aarch64"
else 
	echo Unknow architecture
fi

#create BOOT.BIN
makebootbin() {
	cd $IMAGES
	if [ $ARCH == "arm" ]; then
		petalinux-package --boot --fsbl zynq_fsbl.elf --fpga system.bit --uboot --force
	else
		petalinux-package --boot --fsbl zynqmp_fsbl.elf --fpga system.bit --pmufw pmufw.elf --u-boot --force
	fi
	if [ $? == 0 ]; then
		echo "BOOT.BIN ready"
	else 
		echo "BOOT.BIN generation failed"
	fi
}

#create sd card
makesd() {
	cd $IMAGES
	if [ -f "BOOT.BIN" ]; then
		echo "BOOT.BIN exists, copying"
	else 
		bootbin
	fi
	if [ ! -d $BOOT_MNT ]; then
		echo "$BOOT_MNT not existed, if you mount boot somewhere please set BOOT_MNT then source setup.sh again"
		return
	else
		cp BOOT.BIN boot.scr image.ub $BOOT_MNT
	fi
	if [ ! -d $ROOTFS_MNT ]; then
		echo "$ROOTFS_MNT not existed, if you mount rootfs somewhere please set ROOTFS_MNT then source setup.sh again"
		return
	else
		read -p "Remove old rootfs?(Y/N)" -n 1 -r choice
		if [[ $choice =~ ^[Yy]$ ]]
		then
			sudo rm -rf ${ROOTFS_MNT}/*	
			sudo tar xzvf rootfs.tar.gz -C $ROOTFS_MNT
			echo "Syncing, wait a sec..."
			sync;sync
			echo "Done, sd card can be remove now"
		else
			echo "Skipping rootfs copy"
		fi
	fi
}

release_bsp() {
	cd $PROJECT
	if ls $IMAGES/BOOT.BIN 1> /dev/null 2>&1 ; then
		read -p "Saving prebuilt?(Y/N)" -n 1 -r choice
		if [ $choice =~ ^[Yy]$ ]; then
			rm -rf $PREBUILT
			mkdir -p $PREBUILT
			cp -r ${IMAGES}/ ${PREBUILT}/
			echo "Prebuilt saved"
		else 
			rm -rf $PREBUILT
			echo "No prebuilt included in BSP"
		fi 
	else
		echo "No built images. Saving project configs only"
	fi
	echo "Cleaning"
	petalinux-build -x mrproper -f
	cd ..
	petalinux-package --bsp -p $PROJECT_NAME --output ${PROJECT_NAME}.bsp --force
}

# teleport
alias prj="cd ${PROJECT}"
alias udt="cd ${USER_DT} && ls -lah"
alias bdt="cd ${BOARD_DT} && ls -lah"
alias ksrc="cd ${KERNEL_SRC} && ls -lah"
alias kpatch="cd ${KERNEL_PATCH} && ls -lah"
alias img="cd $IMAGES && ls -lah"
alias module="cd ${MODULE_SRC} && ls -lah"

# shortshortcut
alias clean="petalinux-build -x mrproper -f"
alias config="petalinux-config"
alias configk="petalinux-config -c kernel"
alias configr="petalinux-config -c rootfs"
alias updatehw="petalinux-config --silentconfig --get-hw-description $HARDWAREPATH"
alias build="petalinux-build"
alias buildk="petalinux-build -c kernel"
alias buildr="petalinux-build -c rootfs"
alias buildd="petalinux-build -c device-tree"
alias buildm="petalinux-build -c $MODULE"
alias boot="cd ${PROJECT}; rm -rf ${PREBUILT}/*; mkdir -p ${PREBUILT}; cp -r ${IMAGES}/* ${PREBUILT}/; petalinux-boot --qemu --prebuilt 3"
alias makebb=makebootbin
alias makesd=makesd
alias release=release_bsp
