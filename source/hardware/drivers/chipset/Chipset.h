#pragma once

// Interfaces
#include "IChipset.h"
#include "IConfigurator.h"

// Design Patterns
#include "AbstractFactory.h"
#include "Builder.h"
#include "Factory.h"
#include "Singleton.h"

/**
 * @brief The (base) Chipset class
 */
class Chipset : public IChipset
{
       public:
        /**
	 * @brief The Chipset Builder to create new (base) Chipsets
	 */
        class ChipsetBuilder : public Builder<IChipset>
        {
               public:
                 /**
	 	 * @brief The constructor will map the Build-Method to the (base) Builder class
		 */
                ChipsetBuilder() : Builder( ChipsetBuilder::Build )
                {
                }

                /**
		 * @brief The build method that configures and constructs a new Parameter
		 * @param _config The pre build Configurator
		 * @param _name The name of the new chipset
 		 */
                static IChipset* Build( const IConfigurator* _config, const std::string& _name )
                {
                        const std::string label = "Configurator";

                        Factories& factory = Singleton<Factories>::Instance();
                        IConfigurator* config = factory.Construct<IConfigurator>( label );

                        IChipset* chipset = new Chipset( *config, _name );
                        return chipset;
                }

        };

        /** 
	 * @brief The global Chipset Builder 
	 * @details This should be registerd to an (abstract) Factory in Framework
	 */
        static ChipsetBuilder builder;

        /**
	 * @brief The basic constructor
	 * @param _config The Configurator to fill in the default values
	 * @param _name The name of the new Chipset
	 */
        Chipset( const IConfigurator& _config, std::string _name );
};
