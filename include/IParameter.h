#pragma once

#include "Generic.h"

#include "Composite.h"
#include "Subject.h"
#include "Observer.h"

#include "IMosquitto.h"

#include <stdexcept>

// Forward Declaration
class IMosquitto;

/**
 * @brief The generic interface class for a Poramater
 */
class IParameter:

//    public Generic,
    public Composite< IParameter >,

    public Observer< IParameter >,
    public Observer< IMosquitto >,

    public Subject< IParameter >
{
    public:

	/** 
	*  @brief reset the parameter to the default valuei
	*  @details TODO should return a bool whether it was succesfull
	* @details (On purpose) This method is not abstract because otherwise it could be generarated by the Factory
	*/
	virtual void Reset()
	{
		throw std::logic_error("Not Implemented");
	}
};
