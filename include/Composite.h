#pragma once

#include <string>
#include <vector>

/**
 * @brief This generic class can be used to create a Uniform nested structure of Generic elements
 * @details This generic structional design pattern will be used command all (nested) attached classes.
 */
template< class T >
class Composite
{
    public:

    /**
     * @brief The 'add'-method will store the compontens that should be triggered when a command is send.
     */
    void Add ( T* _node )
    {
        mComponents.push_back( _node ); 
    }

    private:
        std::vector< T* > mComponents;
};
