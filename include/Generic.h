#pragma once

#include <string>
#include <map>

class Generic
{
    public:

       	Generic();

	/** 
         *  @brief getName 
         *  @details return the name of the Parameter
         */
        const std::string& getName() const;
 
    	/** 
    	  *  @brief getProperty 
      	*  @details return the value of the requested property
      	*  @param _property the name of the requested property
      	*/
    	virtual const int& getProperty( std::string _property ) const;

    	/** 
      	*  @brief setProperty 
      	*  @details set the requested property
      	*  @param _property the name of the requested property
      	*  @param _value the new value of the property
      	*/
    	virtual void setProperty( std::string _property, int _value );


    protected:

        /** @brief name of the component */
        std::string mName;

	/** @brief the properties of the Parameter */
        std::map< std::string, int > mProperties;
};
