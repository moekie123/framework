#pragma once

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
	 */
        virtual void update(T *subject) = 0;
};
