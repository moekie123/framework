#!/bin/bash

INSTALLATION=()

while getopts ":fuidbgcetkmh" opt; do
	case ${opt} in
		f)
			INSTALLATION+=('INSTALL_USERS')	;;
		u)
			INSTALLATION+=('INSTALL_DEPENDENCIES')	;;
		i)
			INSTALLATION+=('INSTALL_TOOLKIT') ;;
		d)
			INSTALLATION+=('INSTALL_DOCUMENTATION') ;;
		b)
			INSTALLATION+=('INSTALL_BOOST') ;;
		g)
			INSTALLATION+=('INSTALL_GIT') ;;
		c)
			INSTALLATION+=('INSTALL_CMAKE') ;;
		e)
			INSTALLATION+=('INSTALL_BASH') ;;
		t)
			INSTALLATION+=('INSTALL_TEST') 
			INSTALLATION+=('INSTALL_LIBRARY')
			;; 
		k)
			INSTALLATION+=('INSTALL_KERNEL') ;;
		m)
			INSTALLATION+=('INSTALL_MQTT')
			INSTALLATION+=('INSTALL_LIBRARY') 
			;;
		h )
			echo "Usage:"
			echo "    setup -f		Install and configure the users"
			echo "    setup -u		Update and Upgrade enviroment"
			echo "    setup -i		Install toolkit"
			echo "    setup -d		Install Documentation tools"
			echo "    setup -b		Install Boost"
			echo "    setup -g		Install and configure Git"
			echo "    setup -c		Install CMake"
			echo "    setup -e		Install Enviroment Bash-scripts"
			echo "    setup -t		Install Test Enviroment (gtest, cucumber, ccpcheck)"
			echo "    setup -k		Install (RPI-) Kernel Enviroment"
			echo "    setup -m		Install Mosquitto"
			exit 0
			;;
		\? )
			echo "Invalid Option: -$OPTARG" 1>&2
			exit 1
			;;
  	esac
done

if [ "$#" -ne 0 ] ; then
	printf '%s\n' "${INSTALLATION[@]}"
fi

USERNAME="rsalm"
PASSWORD="rsalm"

RPIENV=$(pwd)
INSTALL='apt-get install --yes --allow-unauthenticated --allow-downgrades --allow-remove-essential --allow-change-held-packages'

function info
{
	echo -e "\e[34m $1 \e[0m"
}

function error
{
	echo -e "\e[31m $1 \e[0m"
}

info "Start Setup Development Environment Script"

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_USERS" ]]; then
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
fi

# Install Bash Enviroment
if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_BASH" ]]; then
info "Configure Enviroment"
	# Copy the following files to the Home-dir
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
	# Use CMake to install CMake (instead of bootstrap)
	$INSTALL vim 

	if [ ! -d ~/.vim/ ]; then
		mkdir ~/.vim
	fi

	if [ ! -d ~/.vim/pack ]; then
		ln -s $RPIENV/vim-plugin/pack ~/.vim/ 
	fi
fi

# Update Platfrom Enviroment
if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_DEPENDENCIES" ]]; then
info "Update Dependencies"
	DEBIAN_FRONTEND=noninteractive apt-get update 
	DEBIAN_FRONTEND=noninteractive apt-get upgrade 
fi

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_TOOLKIT" ]]; then
# Platfrom independend toolkit
info "Install Development Toolkit"
	$INSTALL gcc g++ python universal-ctags build-essential cmake 

# Raspberry pi specifics
info "Install I2C Toolkit"
	$INSTALL i2c-tools 
fi

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_DOCUMENTATION" ]]; then
info "Install Documentation Utilities"
	$INSTALL doxygen graphviz apache2 
fi

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_BOOST" ]]; then
info "Install Boost"
	$INSTALL libboost-all-dev --fix-missing 
fi

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_GIT" ]]; then
info "Install Git"
	$INSTALL git 
	git config --global user.name "$USERNAME"
	git config --global user.email "$USERNAME"
	git config --global core.editor "vim"
fi

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_TEST" ]]; then
info "Install Code Validator"
	$INSTALL cppcheck 

info "Install TDD Framework (GTest)"
	BUILD_DIR=/tmp/gtest

	# Checkout Repository
	git clone https://github.com/google/googletest.git $BUILD_DIR

	# Build Gtest Framework
	cmake -S$BUILD_DIR -B$BUILD_DIR/build -DBUILD_SHARED_LIBS=ON
	
	make  --no-print-directory -C $BUILD_DIR/build install -j4

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

	make  --no-print-directory -C $BUILD_DIR/build install -j4
fi

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_MQTT" ]]; then
info "MQTT-broker"
	BUILD_DIR=/tmp/mosquitto

	# Checkout Repository
	git clone https://github.com/eclipse/mosquitto.git $BUILD_DIR

	# Build Cucumber Framework
	cmake -S$BUILD_DIR -B$BUILD_DIR/build -DDOCUMENTATION=OFF -DBUILD_SHARED_LIBS=ON

	make  --no-print-directory -C $BUILD_DIR/build install -j4

	ldconfig

	# copy configuration files
	cp config/etc/mosquitto/mosquitto.conf /usr/local/etc/mosquitto/
	cp config/etc/systemd/system/mosquitto.service /etc/systemd/system

	# configure start on boot service
	systemctl daemon-reload
	systemctl enable mosquitto.service
fi

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_LIBRARY" ]]; then
info "Add library directory"
	ldconfig /usr/local/lib
fi

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_KERNEL" ]]; then
info "Install Kernel Toolkit"
	$INSTALL bc bison flex libssl-dev 
	$INSTALL libncurses5-dev 

if [ "$#" -eq 0 ] || [[ " ${INSTALLATION[@]} " =~ "INSTALL_CMAKE" ]]; then
info "Install CMake"
	BUILD_DIR=/tmp/cmake

	# Checkout Repository
	git clone https://github.com/Kitware/CMake.git $BUILD_DIR

	# Build Cucumber Framework
	cmake -S$BUILD_DIR -B$BUILD_DIR/build -DCMAKE_USE_OPENSSL=OFF

	make --no-print-directory -C $BUILD_DIR/build install -j4
fi

info "Install Kernel Enviroment"
	KERNEL_DEST=/usr/src/

	# Checkout Repository
	if [ -d $KERNEL_DEST  ]; then
		git clone --depth=1 https://github.com/raspberrypi/linux $KERNEL_DEST/linux
	fi

	# Copy Shortcut script to kernel enviroment
	cp -r $RPIENV/linux $KERNEL_DEST
fi

info "Finished Setup Development Environment Script"

