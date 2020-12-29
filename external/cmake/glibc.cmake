include(ExternalProject)

# Install the Google Test Framework
set( EXTERNAL_PROJECT_NAME ext_glibc )

set( GLIBC_CONFIGURE_FLAGS )
list( APPEND GLIBC_CONFIGRE_FLAGS --prefix=${EXTERNAL_DIR}/output )
list( APPEND GLIBC_CONFIGRE_FLAGS --with-gnu-ld --with-gnu-as )
list( APPEND GLIBC_CONFIGRE_FLAGS libc_cv_forced_unwind=yes libc_cv_c_cleanup=yes )
list( APPEND GLIBC_CONFIGRE_FLAGS libc_cv_gnu89_inline=yes )
list( APPEND GLIBC_CONFIGRE_FLAGS --host=aarch64-linux-gnu )
list( APPEND GLIBC_CONFIGRE_FLAGS --build=x86_64-linux-gnu )
list( APPEND GLIBC_CONFIGRE_FLAGS --without-cvs )
list( APPEND GLIBC_CONFIGRE_FLAGS --disable-nls )
list( APPEND GLIBC_CONFIGRE_FLAGS --disable-sanity-checks )
list( APPEND GLIBC_CONFIGRE_FLAGS --enable-obsolete-rpc )
list( APPEND GLIBC_CONFIGRE_FLAGS --disable-profile )
list( APPEND GLIBC_CONFIGRE_FLAGS --disable-debug )
list( APPEND GLIBC_CONFIGRE_FLAGS --without-selinux )
list( APPEND GLIBC_CONFIGRE_FLAGS --with-tls )
list( APPEND GLIBC_CONFIGRE_FLAGS --enable-kernel=3.7.0 )
list( APPEND GLIBC_CONFIGRE_FLAGS --with-headers=${CMAKE_SOURCE_DIR}/kernel/include )
list( APPEND GLIBC_CONFIGRE_FLAGS --enable-hacker-mode )

# Create external project
ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY git://sourceware.org/git/glibc.git
	GIT_TAG master
	GIT_PROGRESS ON

#	UPDATE_DISCONNECTED ${DISCONNECT}
	
	UPDATE_COMMAND 		""
	CONFIGURE_COMMAND 	./glibc/configure ${GLIBC_CONFIGRE_FLAGS}

	BUILD_COMMAND		make -j4

	INSTALL_COMMAND		make install -j4

	DOWNLOAD_DIR    "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}/glibc"
	BINARY_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"

	TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"
)

set( CMAKE_REQUIRED_INCLUDES "${EXTERNAL_DIR}/output/include/" )

