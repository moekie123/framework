Spyder Documentation {#mainpage}
============

# Introduction 
This is a framework for building a Robotic Arm.
 
These doxygen generated webpages are describing the code base. 
Detailed design choices are documented here: <a href="https://moekiehome.wpcomstaging.com"> WordPress Pages </a>

The main purpose of this project is learning and discovering of technics and features, including:
 * Implementing reusable design patterns
 * Designing a project architecture's

I'am aware certain design structure's can be improved. But optimazation is (not yet) the main goal.

## Getting started
The source code of the framework can be cloned from github:
```
git clone https://github.com/moekie123/
```

### Setup the Development enviroment
The framework includes a 'setup.sh' that will configure your enviroment
```
$ sudo ./<framework>/enviroment/setup.sh
```

The script automatically:
* Configures the users
* Installs all development tools
	* gcc, g++, cmake
	* doxygen (and graphviz for visualization)
* Test Frameworks
	* Cucumber
* Homebridge

The framework itself can be builded by CMake.
```
$ cmake -Bbuild
```
With the build automatacilly the following external dependencies will be install
* The google test framework 
* The mosquitto broker (library and biniary)
* The RapidJSON Library
* The TinyXml2 Library

## Running the tests
The framework has implemented both TTD (Test Driven Development) with googletest and BDD(Behavior Driven Developement) with cucumber.

The (googletest) unittests can be triggered with
```
$ ctest
```
The unittest results can be opened in doxygen \ref unittest

The cucumber tests can be triggerd:
```
$ make cucumber
```

## Usage


## Deployment
The basic install command should be sufficient to install the framework
```
$ make install
```
Mind that doxygen will install the documentation in '/var/www/html' so you can open it in the broweser.

## Contributing
Until the source of the framework is still at a MAJOR Version '0' there will be no contribution accepted.

## Versioning
\ref ReleaseNotes

## Authors
* **Ron Salm** - *Initial work*

## License
This project is free for use. 

## Acknowledgments

<!-- Every thing below the following line will be printed in the section "Unit Tests"-->
\page unittest Unit Tests    
\htmlinclude gtest.php

