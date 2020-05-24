#pragma once

#include "Object.h"
#include <vector>

class Composite:
	virtual public Object
{
public:
	Composite();

	bool Add( Object& _obs );

	/** Object Methods */	
	bool SetProperty( const  std::string& _property, const int& _value ) override;
	bool GetProperty( const  std::string& _property, int& _value ) override;
	bool Reset() override;
	
protected:
	std::vector< Object* > mComponents;

private:
	/* Required to suppress the "no-virtual-move-assign"-Compiler Warning */
	Composite& operator=( Composite&& _other) 
	{
        	return *this;
    	}

};


