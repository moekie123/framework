
				@dot
					digraph D
					{
						graph [ fontsize=12 ];
						node [ fontcolor=black, fontsize=10, margin=0.1];
						edge [ fontcolor=black, fontsize=10];
						label="[Generated from StateMachine.cpp]";

						 sIdle -> sIdle [label="eCycle"] 
 sIdle -> sIdle [label="eTerminate"] 
 sInitializing -> sInitializing [label="eCycle"] 
 sInitializing -> sConfiguring [label="eSucces"] 
 sInitializing -> sCleanup [label="eFailed"] 
 sInitializing -> sCleanup [label="eTerminate"] 
 sConfiguring -> sConfiguring [label="eCycle"] 
 sConfiguring -> sConnecting [label="eSucces"] 
 sConfiguring -> sDestroy [label="eDestroy"] 
 sConfiguring -> sDestroy [label="eTerminate"] 
 sConnecting -> sConnecting [label="eCycle"] 
 sConnecting -> sListening [label="eSucces"] 
 sConnecting -> sDestroy [label="eDestroy"] 
 sConnecting -> sDestroy [label="eTerminate"] 
 sListening -> sListening [label="eCycle"] 
 sListening -> sDisconnecting [label="eTerminate"] 
 sDisconnecting -> sDisconnecting [label="eCycle"] 
 sDisconnecting -> sDestroy [label="eSucces"] 
 sDisconnecting -> sDisconnecting [label="eFailure"] 
 sDisconnecting -> sDestroy [label="eTerminate"] 
 sDestroy -> sDestroy [label="eCycle"] 
 sDestroy -> sCleanup [label="eSucces"] 
 sDestroy -> sDestroy [label="eFailed"] 
 sDestroy -> sCleanup [label="eTerminate"] 
 sCleanup -> sCleanup [label="eCycle"] 
 sCleanup -> sIdle [label="eSucces"] 
 sCleanup -> sIdle [label="eFailed"] 
 sCleanup -> sIdle [label="eTerminate"] 
					}
				@enddot
		  	