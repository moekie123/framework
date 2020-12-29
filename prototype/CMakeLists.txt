# Collect Framework sources

#  Kernel Sandbox
add_executable( proto-kernel kernel.cpp )
target_link_libraries( proto-kernel PRIVATE spdlog )

# Mosquitto Sandbox
add_executable( proto-mqtt mosquitto.cpp )
target_link_libraries( proto-mqtt PRIVATE mosquitto )

# Rapid Json Sandbox
add_executable( proto-json rapidjson.cpp )

# TinyXml2 Sandbox
add_executable( proto-xml tinyxml2.cpp )
target_link_libraries( proto-xml PRIVATE tinyxml2 )

# TinyXml2 Sandbox
add_executable( proto-fsm tinyfsm.cpp )

# Logger Sandbox
add_executable( proto-log spdlog.cpp )
target_link_libraries( proto-log PRIVATE spdlog )

# Driver Sandbox
add_executable( proto-pwm pca9685.cpp )
