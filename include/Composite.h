#pragma once

// Inheritance, Design Patterns
#include "Object.h"

// Stl-Headers
#include <vector>

/**
 * @brief The (Base) Composite class
 */
class Composite:
	virtual public Object
{
public:
	/**
	 * @brief The default constructor 
	 */
	Composite();

	/**
	 * @brief (Composite-) Nodes and Leafs can be add to the instance by this Add-methods
	 * @param _obs The Object that will observe
	 * TODO This should be the Generic
 	 */
	bool Add( Object& _obs );

	/** Object Methods */	
	bool SetProperty( const  std::string& _property, const int& _value ) override;
	bool GetProperty( const  std::string& _property, int& _value ) override;
	bool Reset() override;
	
protected:
	/** 
	 * @brief The added observers
	 */
	std::vector< Object* > mComponents;

private:
	/* Required to suppress the "no-virtual-move-assign"-Compiler Warning */
	Composite& operator=( Composite&& _other) 
	{
        	return *this;
    	}

};


