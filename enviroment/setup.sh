#!/bin/bash

USERNAME="rsalm"
PASSWORD="rsalm"

RPIENV=$(pwd)
INSTALL='apt-get install --yes --allow-unauthenticated --allow-downgrades --allow-remove-essential --allow-change-held-packages'

function info
{
	echo -e "\e[34mBlue $1 \e[0m"
}

function error
{
	echo -e "\e[31mRed $1 \e[0m"
}

info "Start Setup Development Environment Script"

info "Modify users"
	# Assuming this script is executed as root	

	# Change Root Password	
	echo  $PASSWORD":root" | chpasswd

	# Create new user
	id -u $USERNAME &> /dev/null
	if [ $? -ne 0 ]; then
		adduser $USERNAME --gecos "-,-,-,-" --disabled-password
		echo "$PASSWORD:$USERNAME" | chpasswd
	fi

	# Remove default user
	id -u pi &> /dev/null
	if [ $? -ne 1 ]; then
		userdel pi
	fi

info "Update Dependencies"
	DEBIAN_FRONTEND=noninteractive apt-get update 
	DEBIAN_FRONTEND=noninteractive apt-get upgrade 
	
info "Install Development Toolkit"
	$INSTALL gcc g++ vim python universal-ctags build-essential 

info "Install Kernel Toolkit"
	$INSTALL bc bison flex libssl-dev 
	$INSTALL libncurses5-dev 

info "Install I2C Toolkit"
	$INSTALL i2c-tools 

info "Install Documentation Utilities"
	$INSTALL doxygen graphviz apache2 

info "Install Boost"
	$INSTALL libboost-all-dev --fix-missing 

info "Install Git"
	$INSTALL git 
	git config --global user.name "$USERNAME"
	git config --global user.email "$USERNAME"
	git config --global core.editor "vim"

info "Install CMake"
	BUILD_DIR=/tmp/cmake

	git clone https://github.com/Kitware/CMake.git $BUILD_DIR
	cd $BUILD_DIR
		./bootstrap
	cd $RPIENV	

	make -C $BUILD_DIR install

info "Add library directory"
	ldconfig /usr/local/lib

info "Configure Enviroment"
	files=( ".bash_profile" ".vimrc" ".gdbinit" )

	for FILE in "${files[@]}"
	do
		ABS="$HOME/"$FILE
		echo $ABS

		if [ -f $ABS ]; then
			error "- $FILE already exist"
		else
			echo "- Copy $FILE to home directory"
			ln -s $RPIENV/$FILE $ABS
		fi
	done

info "Link Vim-plugings"
	if [ ! -f ~/.vim/ ]; then
		mkdir ~/.vim
	fi

	if [ ! -f ~/.vim/pack ]; then
		ln -s $RPIENV/vim-plugin/pack ~/.vim/pack 
	fi

info "Install Code Validator"
	$INSTALL cppcheck 

info "Install TDD Framework (GTest)"
	BUILD_DIR=/tmp/gtest

	# Checkout Repository
	git clone https://github.com/google/googletest.git $BUILD_DIR

	# Build Gtest Framework
	cmake -S$BUILD_DIR -B$BUILD_DIR/build -DBUILD_SHARED_LIBS=ON
	
	make -C $BUILD_DIR/build install

	# Copy the files to the shared directories
	cp -r $BUILD_DIR/googlemock/include/gmock/ /usr/local/include/
	cp -r $BUILD_DIR/googletest/include/gtest/ /usr/local/include/
	cp $BUILD_DIR/build/lib/libg* /usr/local/lib/

	# Update Library		
	ldconfig

info "Install BDD Framework (Cucumber)"
	BUILD_DIR=/tmp/cucumber

	# Checkout Repository
	git clone https://github.com/cucumber/cucumber-cpp.git $BUILD_DIR

	# Build Cucumber Framework
	cmake -S$BUILD_DIR -B$BUILD_DIR/build -DBUILD_SHARED_LIBS=ON

	make -C $BUILD_DIR/build install

info "Install Kernel Enviroment"
	KERNEL_DEST=/usr/src/
	# Checkout Repository
	if [ -f $KERNEL_DEST  ]; then
		git clone --depth=1 https://github.com/raspberrypi/linux $KERNEL_DEST
	fi

	cp -r $RPIENV/linux $KERNEL_DEST

info "MQTT-broker"
	BUILD_DIR=/tmp/mosquitto

	# Checkout Repository
	git clone https://github.com/eclipse/mosquitto.git $BUILD_DIR

	# Build Cucumber Framework
	cmake -S$BUILD_DIR -B$BUILD_DIR/build -DDOCUMENTATION=OFF -DBUILD_SHARED_LIBS=ON

	make -C $BUILD_DIR/build install

info "MQTT-broker"
	BUILD_DIR=/tmp/mosquitto

	# Checkout Repository
	git clone https://github.com/eclipse/mosquitto.git $BUILD_DIR

	# Build Cucumber Framework
	cmake -S$BUILD_DIR -B$BUILD_DIR/build -DDOCUMENTATION=OFF -DBUILD_SHARED_LIBS=ON

	make -C $BUILD_DIR/build install
	
	ldconfig

	# secure broker
#	mosquitto_passwd -c /etc/mosquitto/passwd $USERNAME
#	mosquitto_passwd -b /etc/mosquitto/passwd $USERNAME $PASSWORD
	
	# copy configuration files
	cp config/etc/mosquitto/mosquitto.conf /usr/local/etc/mosquitto/
	
	if [ ! -f /usr/local/etc/mosquitto/conf.d ]; then
		mkdir /usr/local/etc/mosquitto/conf.d
	fi
	cp config/etc/mosquitto/conf.d/default.conf /usr/local/etc/mosquitto/conf.d/

	# configure start on boot service
	systemctl daemon-reload
	systemctl enable mosquitto.service


info "MQTT-broker"
	BUILD_DIR=/tmp/mosquitto

	# Checkout Repository
	git clone https://github.com/eclipse/mosquitto.git $BUILD_DIR

	# Build Cucumber Framework
	cmake -S$BUILD_DIR -B$BUILD_DIR/build -DDOCUMENTATION=OFF -DBUILD_SHARED_LIBS=ON

	make -C $BUILD_DIR/build install
	
	ldconfig

	# copy configuration files
	cp config/etc/mosquitto/mosquitto.conf /usr/local/etc/mosquitto/
	cp config/etc/systemd/system/mosquitto.servive /etc/systemd/system

	# Create mosquitto user
	id -u mosquitto &> /dev/null
	if [ $? -ne 0 ]; then
		adduser mosquitto --gecos "-,-,-,-" --disabled-password -r -M
	fi

	# configure start on boot service
	systemctl daemon-reload
	systemctl enable mosquitto.service

info "Finished Setup Development Environment Script"

