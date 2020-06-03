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
	# cd $HOME

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
	git clone https://github.com/Kitware/CMake.git /tmp/CMake
	cd /tmp/CMake
		./bootstrap
  		make install
	cd $RPIENV	

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
	echo "GTest will be installed with the Framework"

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

info "Install BDD Framework (Cucumber)"
	$INSTALL cucumber 
	
	# Checkout Repository
#	git clone https://github.com/cucumber/cucumber-cpp.git
#	cd cucumber-cpp

	# Build Cucumber Framework
#	cmake -E make_directory build

#	cmake -E chdir build cmake -DBUILD_SHARED_LIBS=on -DCUKE_ENABLE_EXAMPLES=on -DCMAKE_INSTALL_PREFIX=${prefix} ..

#	cmake --build build
	
	#cmake --build build --target test

#	cmake --build build --target install
	
	# Copy the files to the shared directories
#	cp -r include /usr/include/
#	cp -r build/src/cucumber-cpp/ /usr/include/
#	cp -r build/src/*.so /usr/lib/
	
info "Install Kernel Enviroment"
	KERNEL_DEST=/usr/src/
	# Checkout Repository
	if [ -f $KERNEL_DEST  ]; then
		git clone --depth=1 https://github.com/raspberrypi/linux $KERNEL_DEST
	fi

	cp -r $RPIENV/linux $KERNEL_DEST

info "MQTT-broker"
	echo "Mosquitto will be installed with the Framework"

	# install mosquitto broker, sub & pub
#	$INSTALL mosquitto mosquitto-clients 

	# secure broker
#	mosquitto_passwd -c /etc/mosquitto/passwd $USERNAME
#	mosquitto_passwd -b /etc/mosquitto/passwd $USERNAME $PASSWORD
	
	# copy configuration files
#	cp config/etc/mosquitto/mosquitto.conf /etc/mosquitto/
#	cp config/etc/mosquitto/conf.d/default.conf /etc/mosquitto/conf.d/

	# configure start on boot service
#	systemctl daemon-reload
#	systemctl enable mosquitto.service

info "HomeBridge"
	echo "Homebridge should be optional"

	# install Node.js
#	$INSTALL -y npm curl nodejs gcc g++ make python 

	# setup repo
#	curl -sL https://deb.nodesource.com/setup_12.x | bash -

	# test node is working
#	node -v

	# upgrade npm (version 6.13.4 has issues with git dependencies)
#	npm install -g npm

	# instasl homebridge
#	npm install -g --unsafe-perm homebridge

	# copy configuration files
#	cp config/var/lib/homebridge/config.json /var/lib/homebridge/
#	cp config/etc/default/homebridge /etc/default/
#	cp config/etc/systemd/system/homebridge.service /etc/systemd/system/
	
	# configure start on boot service
#	systemctl daemon-reload
#	systemctl enable homebridge.service

info "Finished Setup Development Environment Script"

