// Design Patterns
#include "Composite.h"

Composite::Composite()
{
}

bool Composite::Add( Generic& _gen )
{
        std::string name = mName + "/" + _gen.GetName();
        _gen.SetName( std::string( name ));

        spdlog::debug( "Add [{}]", name );

        mComponents.push_back( &_gen );

        return false;
}

bool Composite::SetProperty( const std::string& _property, const int& _value )
{
        volatile bool res = false;

        if ( mProperties.find( "const" )->second == 1 )
                goto exit;

        res = Object::SetProperty( _property, _value );
        if ( res ) goto exit;

        for ( auto c : mComponents )
        {
                res = c->SetProperty( _property, _value );
                if ( res ) break;
        }

exit:
        return res;
}

bool Composite::GetProperty( const std::string& _property, int& _value )
{
        volatile bool res = false;

        res = Object::GetProperty( _property, _value );
        if ( res ) goto exit;

        for ( auto c : mComponents )
        {
                res = c->GetProperty( _property, _value );
                if ( res ) break;
        }

exit:
        return res;
}

bool Composite::Reset()
{
        volatile bool res = false;

        for ( auto c : mComponents )
        {
                res = c->Reset();
                if ( !res ) break;
        }

       return res;
}
