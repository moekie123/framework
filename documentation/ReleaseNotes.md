Release Notes {#ReleaseNotes}
============

This page provides information regarding 
- Code changes
- New Features

# Version 0.2.0
Improve the fundamentals of the framework

	- Huge Refactoring on all classes
		- Arguments are now given are const refrence

## Core Feature
	- Implemented an argument parser to the Framework
	- Configurator now used a Vistor pattern to search through xml document
	- Mosquitto client added
	- Finite State Machine integrated

## Hardware Features
	- Initial setup for a Actuator added

## Development Enviroment
	- Added PWM-driver demo
	- Extended enviroment setup
		- Create Symbolic links for bash_profile and vim
	- Missing externals force rebuild cmake after download/installation
	
# Version 0.1.0
The initial setup of the framework 

## Development Enviroment
	- Integrated GoogleTest framework
	- Integrated Cucumber framework
	- Version and build number generator
	- Doxygen extend with dynamic untitest
	- Included prototype directory as sandbox for new features
		- Added Mosquitto demo
		- Added RapidJSON demo
		- Added TinyXml2 demo

## Core Features
	- Design patterns added
		- Factory
		- Singleton
		- Builder
		- Composite
	
	- [New Feature] Parameter added to the framework
	- [New Feature] Configurator added to the framework

## Hardeware Features
	- Initial Architecture has been setup
		- Added Device base
		- Added Sensor base
		- Added Actuator base

## Externals
	- Included Version generator
	- Included GoogleTest framework
	- Included Mosquitto library
	- Included RapidJson library
	- Included TinyXml2 library

