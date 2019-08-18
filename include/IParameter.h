#pragma once

#include "Generic.h"

#include "Composite.h"
#include "Subject.h"
#include "Observer.h"

#include <string>
#include <map>

/**
 *  Interface: IParameter
 */
class IParameter:
    public Generic,
    public Composite< IParameter >,
    public Observer< IParameter >,
    public Subject< IParameter >
{
    public:

    /** 
      *  @brief getProperty 
      *  @details return the value of the requested property
      *  @param _property the name of the requested property
      */
    virtual const int& getProperty( std::string _property ) const = 0;

    /** 
      *  @brief setProperty 
      *  @details set the requested property
      *  @param _property the name of the requested property
      *  @param _value the new value of the property
      */
    virtual void setProperty( std::string _property, int _value ) = 0;

    /** 
     *  @brief reset
     *  @details resets the parameter to the default value
     */
    virtual void reset() = 0;

};
