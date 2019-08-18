#pragma once

#include "Generic.h"

#include <string>

class Builder
{
	public:
		virtual Generic* build( std::string ) = 0;
};
