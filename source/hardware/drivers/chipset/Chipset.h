#pragma once

#include "IChipset.h"

#include "Factory.h"
#include "Builder.h"
#include "Singleton.h"

#include "IConfigurator.h"

/**
 * @brief The (base) Chipset class
 */
class Chipset:
    public IChipset
{
    public:

 	/**
	 * @brief The Chipset Builder to create new (base) Chipsets
	 */
	class ChipsetBuilder:
		public Builder
	{
		public:
		Generic* Build( std::string _name ) override
		{
			Factory& factory = Singleton< Factory >::Instance();

			auto config = factory.Create< IConfigurator >( "Configurator", "configuration.xml" );
			return new Chipset( config, _name );
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
   	Chipset( IConfigurator* _config, std::string _name );

        void Update( IChipset *subject) override;
};


