Actuator {#Actuator}
============

An actuator is a component of a machine that is responsible for moving and controlling a mechanism or system, for example by opening a valve. In simple terms, it is a "mover". An actuator requires a control signal and a source of energy. (<a href=""https://en.wikipedia.org/wiki/Actuator>Wikipedia</a>)
\warning For this initial example the hierarchy of the actuator is limited to a PWM-Driver. When more types of actuators will be implemented this class needs to be refactored 


# MQTT-Interface

The actuator can process the following MQTT messages:

```
{
	"config": {
		"refresh": 100,
		"log": "info",
		"mode": "active",
		"stepsize": 1,
		"period": 1000000
		"profile": "linear"
	},
	"status": {
		"mode": "active",
		"state": "idle",
		"dutycycle": 1000000,
		"error": "no_error"
	},
	"action": {
		"request": {
			"id": 0,
			"key": 0,
			"value": 0
		},
		"reply": {
			"id": 0,
			"error": "no_error"
		}
	}
}
```

## Message Description

### General
The general prefix for a actuator holds the prefix from the root and defines the pwm port
```
framework/hardware/ ... /actuator/<type>/<id>/
```

- <b>type</b> describes the device type, that should be 'pwm'
- <b>id</b> describes the port on the device that it controls

### Configuration
The actuator can be configured on-the-fly. The following configurations are possible
- <b>.../actuator/pwm/id/config/refresh</b> Determines the refresh rate that actuator reports the status message
- <b>.../actuator/pwm/id/config/log</b> The logging-level [info, warning, debug]
- <b>.../actuator/pwm/id/config/mode</b> The mode of the actuator [active, simulation]
- <b>.../actuator/pwm/id/config/stepsize</b> The step size
- <b>.../actuator/pwm/id/config/period</b> The period of the PWM signal
- <b>.../actuator/pwm/id/config/profile</b> The profile of the slope

### Status
The actuator informs the listener on a interval base the current status
- <b>.../actuator/pwm/id/status</b> The current state of the actuator

The status contains three-fields
- <b>mode</b> the mode of the actuator [active, simulation]
- <b>state</b> the state of the statmachine
- <b>dutycycle</b> The dutycycle of the PWM signal
- <b>error</b> The error

### Action
Listeners can control the actuator with requests. The requests should have the following format:
- <b>.../actuator/pwm/id/action/request</b>

With an data package
- <b>id</b> The action id
- <b>key</b> The action key
- <b>value</b> The action value

The actuator wil reply with an acknowledge when the request has ben accepted 
- <b>id</b> The accepted id
- <b>error</b> error code

# Driver Controller
The servo will be contoller by a (pwm) linux driver. This is driver is conform the linux standard.

Three signals will be controllable 
- <b>id</b> The ID of the port
- <b>period</b> The period of the PWM signal
- <b>dutycycle</b> The dutycycle of the PWM signal

# State Machine
The actuator will go through a statemachine to process new action and execute excisting actions

@dot
	digraph G 
	{
		on -> init;

		init -> idle;
		init -> error;

		idle -> execute;
		idle -> transmit;

		execute -> idle;
		execute -> error;

		transmit -> idle;
		transmit -> error;

		error -> init;
	}
@enddot

- <b>on</b> At startup the actuator start going from on to init


