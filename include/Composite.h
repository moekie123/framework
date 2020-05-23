#pragma once

#include "Object.h"
#include <vector>

class Composite:
	virtual public Object
{
public:
	Composite();

	bool Add( Object& obs );

	/** Object Methods */	
	bool SetProperty( const  std::string& property, const int& value ) override;
	bool GetProperty( const  std::string& property, int& value ) override;
	bool Reset() override;
	
protected:
	std::vector< Object* > mComponents;

private:
	/* Required to suppress the "no-virtual-move-assign"-Compiler Warning */
	Composite& operator=( Composite&& other) 
	{
        	return *this;
    	}

};


