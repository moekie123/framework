echo "Framework Profile Loaded"

alias ls='ls $LS_OPTIONS'
alias ll='ls $LS_OPTIONS -l'
alias l='ls $LS_OPTIONS -lA'

alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

alias cdl='cd /usr/src/linux/'

FRAMEWORK='/root/framework'
FRAMEWORK_BUILD=${FRAMEWORK}'/build/'

if [ -d "${FRAMEWORK}" ]; then
	function Rebuild 
	{
       		echo "Rebuild the complete project"
		rm -rf ${FRAMEWORK_BUILD}
		cmake -S${FRAMEWORK} -B${FRAMEWORK_BUILD}
       		make --no-print-directory -C ${FRAMEWORK_BUILD}
	}

	alias  cdf='cd '$FRAMEWORK
	alias  cdb='cd '${FRAMEWORK_BUILD}
	
	alias  cdd='cd '$FRAMEWORK/documentation

	alias  cdi='cd '$FRAMEWORK/include
	alias cdim='cd '$FRAMEWORK/include/mocks

	alias  cde='cd '$FRAMEWORK/external

	alias  cdp='cd '$FRAMEWORK/prototype

	alias  cds='cd '$FRAMEWORK/source
	alias  cdc='cd '$FRAMEWORK/source/core
	alias cdcp='cd '$FRAMEWORK/source/core/parameter
	alias cdcc='cd '$FRAMEWORK/source/core/configurator
	alias cdcm='cd '$FRAMEWORK/source/core/mosquitto

	alias  cdh='cd '$FRAMEWORK/source/hardware

	alias  cdenv='cd '$FRAMEWORK/enviroment

	alias makef='make --no-print-directory -C '${FRAMEWORK_BUILD}
	alias maker='make --no-print-directory -C  ${FRAMEWORK_BUILD} -j4'

	alias documention='make --no-print-directory -C  ${FRAMEWORK_BUILD} -j4 doc_install'

	export FRAMEWORK=$FRAMEWORK
	export FRAMEWORK_TAGS=$FRAMEWORK/tags

	export PATH=$PATH:$FRAMEWORK/binairy/
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

