echo "Framework Profile Loaded"

shopt -s expand_aliases  

alias ls='ls $LS_OPTIONS'
alias ll='ls $LS_OPTIONS -l'
alias l='ls $LS_OPTIONS -lA'

alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

alias cdl='cd /usr/src/linux/'

# Verify (local) Running Hardware

MACHINE=$(uname -m)

if [ "$MACHINE" = "armv7l" ]; 
then
	DEVICE="RaspberryPi"
else
	DEVICE="VirtualMachine"
fi
export HARDWARE=$DEVICE

FRAMEWORK='/root/framework'
FRAMEWORK_BUILD=${FRAMEWORK}'/build/'

# Default the main build
SESSION='Framework'

if [ -d "${FRAMEWORK}" ]; then

	# Configure Enviroment Variable
	export FRAMEWORK=$FRAMEWORK

	export TAGS=$FRAMEWORK/tags
	export SESSION=$SESSION

	export PATH=$PATH:$FRAMEWORK/binary/

	# Navigation aliasses
	alias  cdf='cd '$FRAMEWORK
	alias  cdb='cd '${FRAMEWORK_BUILD}
	
	alias  cdd='cd '$FRAMEWORK/documentation

	alias  cdi='cd '$FRAMEWORK/include
	alias cdim='cd '$FRAMEWORK/include/mocks

	alias  cde='cd '$FRAMEWORK/external
	alias  cdec='cd '$FRAMEWORK/external/cmake

	alias  cdp='cd '$FRAMEWORK/prototype

	alias  cds='cd '$FRAMEWORK/source
	alias  cdc='cd '$FRAMEWORK/source/core
	alias cdcp='cd '$FRAMEWORK/source/core/parameter
	alias cdcc='cd '$FRAMEWORK/source/core/configurator
	alias cdcm='cd '$FRAMEWORK/source/core/mosquitto

	alias  cdh='cd '$FRAMEWORK/source/hardware
	alias cdha='cd '$FRAMEWORK/source/hardware/actuators

	alias  cdenv='cd '$FRAMEWORK/enviroment

	# Build shortcuts
	alias makef='make --no-print-directory -C ${FRAMEWORK_BUILD} VERBOSE=1'
	alias maker='make --no-print-directory -C  ${FRAMEWORK_BUILD} -j4'
	alias makes='make --no-print-directory -C  ${FRAMEWORK_BUILD} -j4 '${SESSION} 

	function rebuild 
	{
       		echo "Rebuild the complete project"
		rm -rf ${FRAMEWORK_BUILD}
		cmake -S${FRAMEWORK} -B${FRAMEWORK_BUILD} -DCMAKE_BUILD_TYPE=Debug
       		make --no-print-directory -C ${FRAMEWORK_BUILD}
	}

	# Documentation shortcuts
	alias documention='make --no-print-directory -C  ${FRAMEWORK_BUILD} -j4 doc_install'

	# Execution shortcut
	alias run=${SESSION}

	# Shortcut specifier
	function session()
	{
		if [ ! -z "$1" ]; then
			SESSION=$1	
		else
			SESSION="Framework"
		fi
		
		echo "Session [$SESSION]"
		export SESSION=$SESSION
	
		alias makes='make --no-print-directory -C  ${FRAMEWORK_BUILD} '${SESSION}
		alias run=${SESSION}
	}

	# Speed Logger Debug
	export SPDLOG_LEVEL="info"
	function spdlog()
	{
		if [ $SPDLOG_LEVEL == "info" ]; then
			export SPDLOG_LEVEL="debug"
		elif [ $SPDLOG_LEVEL == "debug" ]; then
			export SPDLOG_LEVEL="trace"
		elif [ $SPDLOG_LEVEL == "trace" ]; then
			export SPDLOG_LEVEL="info"
		else
			# Reset when enviroment variable is corrupt
			export SPDLOG_LEVEL="info"
		fi
		echo "LogLevel [${SPDLOG_LEVEL}]"
	}
fi

DRIVER_I2C=false

DRIVER_PWM='/sys/class/pwm/pwmchip0'
if [ -d "$DRIVER_PWM" ]; then
	alias cdpwm='cd '$DRIVER_PWM

	DRIVER_I2C=true
fi

if [ "$DRIVER_I2C" = true ]; then
	alias i2c='i2cdetect -y 1'
fi


