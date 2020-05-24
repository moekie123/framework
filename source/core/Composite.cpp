// Design Patterns
#include "Composite.h"

Composite::Composite()
{
}

bool Composite::Add( Object& _obj )
{
        std::string oName = _obj.GetName();
        _obj.SetName( std::string( mName + "/" + oName ) );

        mComponents.push_back( &_obj );

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
        return false;
}
