#!/bin/bash

USERNAME="rsalm"
PASSWORD="rsalm"

RPIENV= $(pwd)
FORCE= --allow-unauthenticated --allow-downgrades --allow-remove-essential --allow-change-held-packages

echo "Start Setup Development Environment Script"
	cd $HOME

echo "Modify users"

	# Change Root Password	
	echo  $PASSWORD":root" | sudo chpasswd

	id -u $USERNAME
	if [ $? -eq 0 ]; then
		# Create new user
		sudo adduser $USERNAME --gecos "-,-,-,-" --disabled-password
		echo $PASSWORD":"$USERNAME | sudo chpasswd
	fi

	id -u pi
	if [ $? -eq 0 ]; then
		# Remote Default User
		userdel pi
	fi

echo "Update Dependencies"
	apt-get update
	apt-get upgrade

echo "Install Development Toolkit"
	apt-get install gcc g++ cmake git vim python universal-ctags $FORCE

echo "Install Kernel Toolkit"
	apt-get install git bc bison flex libssl-dev $FORCE
	apt-get install libncurses5-dev $FORCE

echo "Install I2C Toolkit"
	apt-get install -y i2c-tools $FORCE

echo "Install Documentation Utilities"
	apt-get install gcc g++ doxygen graphviz apache2 $FORCE

echo "Install Boost"
	apt-get install libboost-all-dev --fix-missing $FORCE

echo "Add Alias"
	cp ~/.bashrc > /tmp/.bashrc

	sed 's/# alias/alias/g' ~/.bashrc 	>> /tmp/.bashrc
	echo "alias='i2cdetect -y 1'" 		>> /tmp/.bashrc

	mv /tmp/.bashrc ~/.bashrc

echo "MQTT-broker"
	# install mosquitto broker, sub & pub
	apt-get install mosquitto mosquitto-clients $FORCE

	# secure broker
	mosquitto_passwd -b /etc/mosquitto/passwd $USERNAME $PASSWORD
	
	# copy configuration files
	cp config/etc/mosquitto/mosquitto.conf /etc/mosquitto/
	cp config/etc/mosquitto/conf.d/default.conf /etc/mosquitto/conf.d/

	# configure start on boot service
	systemctl daemon-reload
	systemctl enable mosquitto.service

echo "HomeBridge"
	# setup repo
	curl -sL https://deb.nodesource.com/setup_12.x | sudo bash -

	# install Node.js
	apt-get install -y nodejs gcc g++ make python $FORCE

	# test node is working
	node -v

	# upgrade npm (version 6.13.4 has issues with git dependencies)
	npm install -g npm

	# instasl homebridge
	npm install -g --unsafe-perm homebridge

	# copy configuration files
	cp config/var/lib/homebridge/config.json /var/lib/homebridge/
	cp config/etc/default/homebridge /etc/default/
	cp config/etc/systemd/system/homebridge.service /etc/systemd/system/
	
	# configure start on boot service
	systemctl daemon-reload
	systemctl enable homebridge.service

echo "Install Code Validator"
	apt-get install cppcheck $FORCE

echo "Install TDD Framework (GTest)"

	echo "GTest will be installed through CMake"
	# Checkout Repository
#	git clone https://github.com/google/googletest.git
#	cd googletest

	# Build Gtest Framework
#	cmake -DBUILD_SHARED_LIBS=ON .
#	make

	# Copy the files to the shared directories
#	cp -r googlemock/include/gmock/ /usr/include/
#	cp -r googletest/include/gtest/ /usr/include/
#	cp lib/libg* /usr/lib/
		
	# Verify gtest is installed
#	ldconfig -v |grep gtest

echo "Install BDD Framework (Cucumber)"
	apt-get install cucumber
	
	# Checkout Repository
	git clone https://github.com/cucumber/cucumber-cpp.git
	cd cucumber-cpp

	# Build Cucumber Framework
	cmake -E make_directory build

	cmake -E chdir build cmake -DBUILD_SHARED_LIBS -DCUKE_ENABLE_EXAMPLES=on -DCMAKE_INSTALL_PREFIX=${prefix} ..

	cmake --build build
	
	#cmake --build build --target test

	cmake --build build --target install
	
	# Copy the files to the shared directories
	cp -r include /usr/include/
	cp -r build/src/cucumber-cpp/ /usr/include/
	cp -r build/src/*.so /usr/lib/
	
echo "Install Kernel Enviroment"
	cd /usr/src/

	# Checkouot Repository
	git clone --depth=1 https://github.com/raspberrypi/linux	
	
	cd /usr/src/linux
	cp $RPIENV/linux/* .

echo "Finished Setup Development Environment Script"
