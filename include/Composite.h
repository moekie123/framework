#pragma once

#include <string>
#include <vector>

/**
 * @brief ( Structional Design Pattern ) Composite
 * @details A generic implementation
 */
template< class T >
class Composite
{
    public:

    /**
     * @brief add
     * @details add a new T to the tree
     */
    void add ( T* _node )
    {
        mComponents.push_back( _node ); 
    }

    private:
        /** @brief (Composite) tree of Components */
        std::vector< T* > mComponents;

};



