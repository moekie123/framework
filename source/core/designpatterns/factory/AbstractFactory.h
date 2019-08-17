#pragma once

#include "Generic.h"

#include <string>
#include <map>

    class AbstractClass:
        public Generic
    {
        public:
            virtual ~AbstractClass(){}
            virtual Generic* create() = 0;
    };

    template < class Derived  >
    class ConcreteClass : public AbstractClass
    {
        public:
            Generic* create()
            {
                return new Derived( );
            }
    };


template < class T >
class Factory
{
    public:
        void push( std::string _id, AbstractClass* _factory )
        {
            FactoryMap[ _id ] = _factory;
        }
        
        template< class U >
        U* create( std::string _id )
        {
            U* beta = static_cast< U* >( FactoryMap[ _id ]->create() );
            return beta;
        }
    private:
        std::map< std::string, AbstractClass* > FactoryMap;
};
