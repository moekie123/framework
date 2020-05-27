#pragma once

// Inheritance, Design Patterns
#include "Object.h"

// Stl-Headers
#include <vector>

class Generic;

/**
 * @brief The (Base) Composite class
 */
class Composite : virtual public Object
{
       public:
        /**
	 * @brief The default constructor 
	 */
        Composite();

        /**
	 * @brief (Composite-) Nodes and Leafs can be add to the instance by this Add-methods
	 * @param _gen The Object that will observe
 	 */
        bool Add( Generic& _gen );

        /** Object Methods */
        bool SetProperty( const std::string& _property, const int& _value ) override;
        bool GetProperty( const std::string& _property, int& _value ) override;
        bool Reset() override;

       protected:
        /** 
	 * @brief The added observers
	 */
        std::vector<Generic*> mComponents;

       private:
        /** 
	 * @brief Required to suppress the "no-virtual-move-assign"-Compiler Warning 
	 */
        Composite& operator=( Composite&& _other )
        {
                return *this;
        }
};

/* This file is already included through Generic.h */
#include "Generic.h"
