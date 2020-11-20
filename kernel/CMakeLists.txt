message( "Configure Kernel" )

include(ExternalProject)

set( KERNEL_TMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.temporary")
set( KERNEL_STAMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.stamp")
set( KERNEL_LOG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.log" )

set( KERNEL_UPDATE ON )

# Instal the Google Test Framework
        set( KERNEL_PROJECT_NAME linux )

        ExternalProject_Add( ${KERNEL_PROJECT_NAME}
                GIT_REPOSITORY https://github.com/raspberrypi/linux 
                GIT_TAG rpi-5.4.y
                GIT_PROGRESS ON

                UPDATE_DISCONNECTED KERNEL_UPDATE

		BUILD_IN_SOURCE ON

		CONFIGURE_COMMAND	export KERNEL=kernel7
		COMMAND			make bcm2709_defconfig -j4

		BUILD_COMMAND 		make zImage modules dtbs -j4

		INSTALL_COMMAND 	make INSTALL_MOD_PATH=${CMAKE_CURRENT_SOURCE_DIR}/modules modules_install -j4 
		COMMAND			${CMAKE_CURRENT_SOURCE_DIR}/Install.sh	

                DOWNLOAD_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/${KERNEL_PROJECT_NAME}"
                SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${KERNEL_PROJECT_NAME}"
                INSTALL_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/${KERNEL_PROJECT_NAME}"

                TMP_DIR         "${KERNEL_TMP_DIR}/${KERNEL_PROJECT_NAME}"
                STAMP_DIR       "${KERNEL_STAMP_DIR}/${KERNEL_PROJECT_NAME}"
                LOG_DIR         "${KERNEL_LOG_DIR}/${KERNEL_PROJECT_NAME}"
        )

