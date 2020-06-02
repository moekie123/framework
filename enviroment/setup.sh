#!/bin/bash

USERNAME="rsalm"
PASSWORD="rsalm"

RPIENV=$(pwd)
FORCE='--yes --allow-unauthenticated --allow-downgrades --allow-remove-essential --allow-change-held-packages'

echo "Start Setup Development Environment Script"
	cd $HOME


echo "Modify users"
	# Assuming this script is executed as root	

	# Change Root Password	
	echo  $PASSWORD":root" | chpasswd

	id -u $USERNAME &> /dev/null
	if [ $? -ne 0 ]; then
		# Create new user
		adduser $USERNAME --gecos "-,-,-,-" --disabled-password
		echo $PASSWORD":"$USERNAME | chpasswd
	fi

	id -u pi &> /dev/null
	if [ $? -ne 1 ]; then
		# Remote Default User
		userdel pi
	fi

echo "Update Dependencies"
	DEBIAN_FRONTEND=noninteractive apt-get -y update
	DEBIAN_FRONTEND=noninteractive apt-get -y upgrade
	
echo "Install Development Toolkit"
	apt-get install gcc g++ cmake vim python universal-ctags $FORCE

echo "Install Kernel Toolkit"
	apt-get install bc bison flex libssl-dev $FORCE
	apt-get install libncurses5-dev $FORCE

echo "Install I2C Toolkit"
	apt-get install i2c-tools $FORCE

echo "Install Documentation Utilities"
	apt-get install gcc g++ doxygen graphviz apache2 $FORCE

echo "Install Boost"
	apt-get install libboost-all-dev --fix-missing $FORCE

echo "Install Git"
	apt-get install git $FORCE
	git config --global user.name "$USERNAME"
	git config --global core.editor "vim"


echo "Configure Enviroment"

files=( ".bash_profile" ".vimrc" ".gdbinit" )

for FILE in "${files[@]}"
do
	ABS="$HOME/"$FILE
	
	if [ -f $ABS ]; then
		echo -e "\e[31m $FILE already exist \e[0m"
	else
		echo "Copy $FILE to home directory"
		ln -s $(pwd)/$FILE $ABS
	fi
done

echo "Link Vim-plugings"
ln -s $(pwd)/vim-plugin/pack ~/.vim/pack 

echo "MQTT-broker"
	# install mosquitto broker, sub & pub
	apt-get install mosquitto mosquitto-clients $FORCE

	# secure broker
	mosquitto_passwd -c /etc/mosquitto/passwd $USERNAME
	mosquitto_passwd -b /etc/mosquitto/passwd $USERNAME $PASSWORD
	
	# copy configuration files
	cp config/etc/mosquitto/mosquitto.conf /etc/mosquitto/
	cp config/etc/mosquitto/conf.d/default.conf /etc/mosquitto/conf.d/

	# configure start on boot service
	systemctl daemon-reload
	systemctl enable mosquitto.service

echo "HomeBridge"
	# install Node.js
	apt-get install -y npm curl nodejs gcc g++ make python $FORCE

	# setup repo
	curl -sL https://deb.nodesource.com/setup_12.x | bash -

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
	apt-get install cucumber $FORCE
	
	# Checkout Repository
	git clone https://github.com/cucumber/cucumber-cpp.git
	cd cucumber-cpp

	# Build Cucumber Framework
	cmake -E make_directory build

	cmake -E chdir build cmake -DBUILD_SHARED_LIBS=on -DCUKE_ENABLE_EXAMPLES=on -DCMAKE_INSTALL_PREFIX=${prefix} ..

	cmake --build build
	
	#cmake --build build --target test

	cmake --build build --target install
	
	# Copy the files to the shared directories
	cp -r include /usr/include/
	cp -r build/src/cucumber-cpp/ /usr/include/
	cp -r build/src/*.so /usr/lib/
	
echo "Install Kernel Enviroment"
	# Checkouot Repository
	git clone --depth=1 https://github.com/raspberrypi/linux /usr/src/
	cp -r linux /usr/src/linux

echo "Finished Setup Development Environment Script"

