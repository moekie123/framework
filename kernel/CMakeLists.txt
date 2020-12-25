message( "Configure Kernel" )

include( ExternalProject )

# Name of the kernel build
set( KERNEL_PROJECT_NAME linux )

# Storage location for build and install files
set( KERNEL_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )

# Allow automatic checkout and rebuild
set( KERNEL_UPDATE ON )

if( (NOT ARCHITECTURE) OR (NOT TOOLCHAIN) OR (NOT KERNEL) )
	message( WARNING "compiler defenitions are missing" )
endif()

ExternalProject_Add( ${KERNEL_PROJECT_NAME}
	
	# Git defenition
	GIT_REPOSITORY https://github.com/raspberrypi/linux 
	GIT_TAG rpi-5.4.y
	GIT_PROGRESS ON

	# Custom build command should be executed in root of checked out directory
	BUILD_IN_SOURCE ON

	# Allow automatic checkout and rebuild
	UPDATE_DISCONNECTED NOT ${KERNEL_UPDATE}

	# Build .config from default
	CONFIGURE_COMMAND	export KERNEL=${KERNEL}
#	COMMAND 		make ARCH=${ARCHITECTURE} CROSS_COMPILE=${TOOLCHAIN} bcmrpi3_defconfig -j4
	COMMAND 		cp --update ${KERNEL_DIR}/.config ${CMAKE_SYSROOT} 

	# Build the kernel
	BUILD_COMMAND		make ARCH=${ARCHITECTURE} CROSS_COMPILE=${TOOLCHAIN} INSTALL_MOD_PATH=${KERNEL_DIR}/build Image modules dtbs -j4

	# Install the kernel
	INSTALL_COMMAND 	make ARCH=${ARCHITECTURE} CROSS_COMPILE=${TOOLCHAIN} INSTALL_MOD_PATH=${KERNEL_DIR}/modules modules_install -j4 
	COMMAND			make ARCH=${ARCHITECTURE} CROSS_COMPILE=${TOOLCHAIN} INSTALL_HDR_PATH=${KERNEL_DIR}/include headers_install -j4

	DOWNLOAD_DIR    "${KERNEL_DIR}/download"
	SOURCE_DIR      "${CMAKE_SYSROOT}"
	INSTALL_DIR     "${KERNEL_DIR}/install"

	TMP_DIR         "${KERNEL_DIR}/.temporary"
	LOG_DIR         "${KERNEL_DIR}/.log"
	STAMP_DIR       "${KERNEL_DIR}/.stamp"
)

# Install when working on the RaspberryPi Hardware 
if( ${RPI_HARDWARE} AND ${KERNEL_UPDATE} )
	
	ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} upgrade
		ALWAYS FALSE
		DEPENDEES "install"
		COMMENT "Upgrade kernel"
		COMMAND ${KERNEL}/Install.sh )

endif()


