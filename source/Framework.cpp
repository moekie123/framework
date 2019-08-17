#include "Framework.h"

/// Include all factories
#include "core/parameter/ParameterFactory.h"

Framework::Framework( int argc, char *argv[] )
{
	ParameterFactory *pf = new ParameterFactory();	
};
