#pragma once

#include <stdexcept>

/**
 * @brief The generic behavarioal design pattern Observer
 * @details Should be used in combination with a Subject
 */
template <class T>
class Observer
{
    public:

        Observer() {}
        virtual ~Observer() {}

	/**
	 * @brief The callback when the Subject notifies all subscribtions
	 * @details (On purpose) This method is not abstract because otherwise it could be generarated by the Factory
	 */
        virtual bool Update( const T* subject )
	{	
		throw std::logic_error("Not Implemented");
	}

};
