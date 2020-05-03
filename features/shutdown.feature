# language: en
Feature: Shutdown
	Dummy Feature to test the cucumber enviroment 
	
	Scenario: Shutdown
		Given the trigger to terminate the framework
		When the IsStopped signal has ben envoked
		Then the framework is stopped
