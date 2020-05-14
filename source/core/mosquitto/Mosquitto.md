Mosquitto {#Mosquitto}
============

The Mosquitto Client will function as the interface between other modules of the Framework.
It is able to connect to a MQTT-Broker.

@dot

digraph {
	rankdir=TB;
	subgraph cluster_1 {
		label="StateMachine";

    		Accept[ shape="box" ]
		Accept -> State1;	

		subgraph c3 {
			State1 -> State2 -> State3 -> State4;
		}
	
		State1 -> Visitor1 [label="visit", style=dashed, arrowhead=odot];
		State2 -> Visitor2 [label="visit", style=dashed, arrowhead=odot];
		State3 -> Visitor3 [label="visit", style=dashed, arrowhead=odot];
		State4 -> Visitor4 [label="visit", style=dashed, arrowhead=odot];
	}
	subgraph cluster_2 {
		label="Client";

		Run -> Accept;
		
    		Visitor1[ shape="box" ]
    		Visitor2[ shape="box" ]
    		Visitor3[ shape="box" ]
    		Visitor4[ shape="box" ]

	}

	{ rank=same; Accept, Run }
	{ rank=same; State1, Visitor1 }
	{ rank=same; State2, Visitor2 }
	{ rank=same; State3, Visitor3 }
	{ rank=same; State4, Visitor4 }

}

@enddot
