# language: en
Feature: Startup
	Dummy Feature to test the cucumber enviroment 
	
	Scenario: Startup
		Given the trigger to initialize the framework
		When the IsStarted signal has ben envoked
		Then the framework is running
