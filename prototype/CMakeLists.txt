# Collect Framework sources

# Mosquitto Sandbox
add_executable( proto-mqtt mosquitto.cpp )
target_link_libraries( proto-mqtt PUBLIC mosquitto)

# Rapid Json Sandbox
add_executable( proto-json rapidjson.cpp )

# TinyXml2 Sandbox
add_executable( proto-xml tinyxml2.cpp )
target_link_libraries( proto-xml PUBLIC tinyxml2 )

# TinyXml2 Sandbox
add_executable( proto-fsm tinyfsm.cpp )

# Logger Sandbox
add_executable( proto-log spdlog.cpp )

# Driver Sandbox
add_executable( proto-pwm pca9685.cpp )

# CrossCompiler Test
add_executable( crossing experiment.cpp ) 
