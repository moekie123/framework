#include "Chipset.h"

Chipset::ChipsetBuilder Chipset::builder;

Chipset::Chipset( const IConfigurator& _config, std::string _name )
{

}

bool Chipset::Update( const IChipset* subject )
{
	return false;    
}
