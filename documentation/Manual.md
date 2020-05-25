Manual Page {#manual}
============

# Introduction 
This page describes the usage of the Framework and its Development Enviroment

# Framework Arguments
The Framework is able to process arguments given from the command-line.

```
#include "Framework.h"

int main( int argc, char* argv[] )
{
        Framework* f = new Framework( argc, argv );
        return 0;
}
```

The options accepted by the Framework can be viewed with help (--help)
```
$ Framework -h

Usage: Framework [-h]

Options:
  -h, --help        Print this menu and exit.
  -c, --config      The configuation file [default: config.xml].
  -v, --verbose     Turn on the debug.
```

- **--help**
	This will print the menu with options as illustarted above

- **--config**
	With this parameter the configuration file can be changed

- **--verbose**
	Turn on the (speedlogger) debug 

# Development Tools and Commands
With the setup a .bash\_profile will be installed. This profile provides a toolkit with command that will help you develop more effecient.

## Documentation
- **[documentation]**
(Re-)build and (Re-)install the doxygen documentation.

## Naviation Commands
These are extende 'cd' commands

- **[cdf]**  Root of project
- **[cdb]**  Build

- **[cdi]**  Include
- **[cdim]** Mocks

- **[cds]**  Root of source tree

- **[cdc]**  Core
- **[cdcp]** Parameters
- **[cdcc]** Configurator 
- **[cdcm]** Mosquitto

- **[cdh]** Hardware
- **[cdha]** Actuator

- **[cdenv]** Enviroment

- **[cde]**  Externals
- **[cdd]**  Documentation
- **[cdp]**  Prototypes

## Build Commands
- **[rebuild]** Remove the build directory and rebuild the full project

- **[makef]** Normal speed build
- **[maker]** Rapid speed build (-j4)

- **[session]** Tag the target that you are working on
- **[makes]** Build the project that you have selected with the 'session'-command

## Run 
- **[run]** Run the tests that you have selected with the 'session'-command

## Debug
- **[spdlog]** Toggle logging setting between 'info', 'debug' and 'trace'

## VIM-Commands
- **\<F5>** Refactor code style with clang-format 
- **\<F6>** Open the (gdb) debugger 
- **\<F7>** Open the explorer navigator
- **\<F8>** Open the ctags navigator

