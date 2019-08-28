# Set variable for the generate sources
set(GENERATE_SRCS 	${CMAKE_CURRENT_SOURCE_DIR}/version.cpp)
set(GENERATE_OUTPUT 	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/version)
set(VERSION_OUTPUT 	${CMAKE_SOURCE_DIR}/include/version.h)

# Create command to compile the generate command
add_custom_command(
    OUTPUT ${GENERATE_OUTPUT}
    COMMAND g++ -o ${GENERATE_OUTPUT} ${GENERATE_SRCS}
    DEPENDS ${GENERATE_SRCS}
    )

add_custom_target( version
    COMMAND ${GENERATE_OUTPUT}
        -M ${VERSION_MAJOR}
	-m ${VERSION_MINOR}
	-p ${VERSION_PATCH}
	-a "${VERSION_META}"
	-F "${PROJECT_BINARY_DIR}/.buildnumber"
	-i
	> ${VERSION_OUTPUT}
    DEPENDS ${GENERATE_OUTPUT}
    COMMENT "Generating version tags"
    VERBATIM
    )
