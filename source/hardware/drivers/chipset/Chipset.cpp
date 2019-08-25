#include "Chipset.h"

Chipset::ChipsetBuilder Chipset::builder;

Chipset::Chipset( IConfigurator* _config, std::string _name )
{

}

bool Chipset::Update( IChipset *subject )
{
	return false;    
}
