Design Page {#design}
============

# Introduction 


# Highlevel Overview
@dot
digraph D
{
	rankdir = BT
	graph [ fontsize=12 ];
	node [ fontcolor=black, fontsize=10, margin=0.1, shape=box];
	edge [ fontcolor=black, fontsize=10];

	label="[ Overall Framework Component ]";

	{ rank=same Object };
	{ rank=same Composite, Observer, Subject };
	{ rank=same Generic };
	{ rank=same IParameter, IConfigurator, IDevice, IMosquitto , IActuator};

	Generic -> {Composite, Observer, Subject} -> Object;
	Generic -> Object;
	
	{ rank=same IParameter, IConfigurator, IDevice, IMosquitto , IActuator, ISensor };

	Parameter 	-> IParameter 	 -> Generic;
	Configurator	-> IConfigurator -> Generic;
	Device 		-> IDevice 	 -> Generic;
	Mosquitto 	-> IMosquitto 	 -> Generic;
	
	Actuator 	-> IActuator 	-> Hardware 	-> Generic;
	Sensor 		-> ISensor 	-> Hardware 	-> Generic;
}
@enddot
		  	
