#pragma once

#include <string>
#include <vector>

template< class T >
class Composite
{
    public:

    /**
     * @brief (Composite) - add
     * @details add a new IParameter to the tree
     */
    void add ( T* _node )
    {
        mComponents.push_back( _node ); 
    }

    private:
        /** @brief (Composite) tree of Components */
        std::vector< T* > mComponents;

};



