echo "Framework Profile Loaded"

alias ls='ls $LS_OPTIONS'
alias ll='ls $LS_OPTIONS -l'
alias l='ls $LS_OPTIONS -lA'

alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

alias cdl='cd /usr/src/linux/'

FRAMEWORK="/root/framework"
if [ -d "$FRAMEWORK" ]; then
	alias  cdf='cd '$FRAMEWORK
	alias  cdb='cd '$FRAMEWORK/binairy
	alias  cdi='cd '$FRAMEWORK/include
	
	alias  cds='cd '$FRAMEWORK/source
	alias  cdc='cd '$FRAMEWORK/source/core
	alias cdcp='cd '$FRAMEWORK/source/core/parameter
	alias cdcc='cd '$FRAMEWORK/source/core/configurator
	alias cdcm='cd '$FRAMEWORK/source/core/mosquitto

	alias  cdh='cd '$FRAMEWORK/source/hardware

	alias  cde='cd '$FRAMEWORK/source/enviroment

	alias makef='make --no-print-directory -C '$FRAMEWORK'/build/'

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

