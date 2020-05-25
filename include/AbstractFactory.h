#pragma once

// Interfaces
#include "IActuator.h"
#include "IChipset.h"
#include "IConfigurator.h"
#include "IDevice.h"
#include "IMosquitto.h"
#include "IParameter.h"

// Design Patterns
#include "Builder.h"
#include "Factory.h"

// Stl-Headers
#include <cstring>
#include <stdexcept>

/**
 * @brief The Abstract Factory holds all Factories as Templates, as a varidic
 * @details The templates should be of base class Factory
 */
template <class... Mixin>
class AbstractFactory : public Mixin...
{
       public:
        /** 
         *  @brief The default constructor
         */
        AbstractFactory() : Mixin()...
        {
        }

        /**
	*  @brief With Construct the Factory will be picked by (template) specialization and the specfic builder in this Factory is choosen by _type   
	*  @details Will throw and exception when _type does not match any builder
	*  @param _type The name of the builder
	*  @param _name The name of the new instance
	*  @return The created class, which is typical a Interface Class
	*/
        template <class T>
        T* Construct( const std::string& _type, const std::string& _name = "" )
        {
                spdlog::trace( "{} {}", __PRETTY_FUNCTION__, _type );

                // Check whether the name excits
                auto search = Factory<T>::mBuilders.find( _type );
                if ( search != Factory<T>::mBuilders.end() )
                {
                        // TODO Assumed Configurator is initialized
                        IConfigurator* config = Factory<IConfigurator>::mBuilders["Configurator"]->Build();

                        T* obj = search->second->Build( config, _name );
                        return obj;
                }

                throw std::invalid_argument( "AbstractFactory: Unknown Builder" );
        }

        /**
	* @brief New builders can be added by registering
	* @details Will throw an exception when _type is already in use
        * @param _type The name of the registered builder
        * @param _builder The actual builder 
	* @return True, when build was succesfull
	*/
        template <class T>
        bool Register( const std::string& _type, Builder<T>* _builder )
        {
                spdlog::trace( "{} {}", __PRETTY_FUNCTION__, _type );

                // Check whether the name already excists
                auto search = Factory<T>::mBuilders.find( _type );
                if ( search == Factory<T>::mBuilders.end() )
                {
                        Factory<T>::mBuilders.emplace( _type, _builder );
                        return true;
                }

                throw std::invalid_argument( "AbstractFactory: Builder already excists" );
        }
};

using Factories = AbstractFactory<Factory<IParameter>,
                                  Factory<IConfigurator>,
                                  Factory<IChipset>,
                                  Factory<IDevice>,
                                  Factory<IMosquitto>,
                                  Factory<IActuator> >;
