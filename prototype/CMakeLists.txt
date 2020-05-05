# Collect Framework sources
add_executable( proto-mqtt mosquitto.cpp )
target_link_libraries( proto-mqtt PUBLIC
				framework
				mosquitto
				tinyxml2 )

add_executable( proto-json rapidjson.cpp )
target_link_libraries( proto-json PUBLIC
				framework
				tinyxml2 )

