#pragma once

#include "IChipset.h"

#include "AbstractFactory.h"
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
		public Builder< IChipset >
	{
		public:
		static IChipset* Build( const std::string& _name )
		{
			const std::string label = "Configurator";
			
			Factories& factory = Singleton< Factories >::Instance();
			IConfigurator* config = factory.Construct< IConfigurator >( label );
			
			IChipset* chipset = new Chipset( *config, _name );
			return chipset;
		}

		ChipsetBuilder(): Builder( ChipsetBuilder::Build )
		{
		
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

	/** Observer Methods */
        bool Update( const Subject& ) override;
};


