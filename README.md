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

## Getting Started
The source code of the framework can be cloned from github:
```
git clone https://github.com/moekie123/ xxx
```

### Setup the Development enviroment
The installation of your development enviroment is documenent on <a href="https://moekiehome.wpcomstaging.com">WordPress</a>

In summary it describes how to get a automatated script:
```
$ git clone http://github.com/moekie123/rpi-env/setup.sh
$ sudo ./setup.sh
```

The script automatically installs:
* [GoogleTest]
* [Doxygen]

## Running the tests
The framework has implemented both TTD (Test Driven Development) with googletest and BDD(Behavior Driven Developement) with cucumber.

The (googletest) unittests can be triggered with
```
$ make test
```

The cucumber tests can be triggerd:
<TODO: Implemented Cuccumber Test>

## Deployment
The basic install command should be sufficient to install the framework
```
$ make install
```

Mind that doxygen will install the documentation in '/var/www/html' so you can open it in the broweser.


## Contributing

Untill the source of the framework is still at a MAJOR Version '0' there will be no contribution accepted.

## Versioning
<TODO: Create Release branches>

## Authors
* **Ron Salm** - *Initial work*

## License
This project is free for use. 

## Acknowledgments

