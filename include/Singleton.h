#pragma once

#include <memory>

/**
 * @brief The generic constructional design pattern Singleton
 */
template <typename T>
class Singleton
{
public:

	/**
	 * @brief Get the global class
	 * @return returns the global instance of the class
	 */
	static T& Instance()
    	{
        	if (Singleton::_instance == 0)
        	{
            		Singleton::_instance = CreateInstance();
        	}
		return *(Singleton::_instance);
	}

protected:
    	virtual ~Singleton()
    	{
        	if(Singleton::_instance != 0)
        	{
            		delete Singleton::_instance;
        	}
        	Singleton::_instance = 0;
    	}

	inline explicit Singleton()
	{
		assert(Singleton::_instance == 0);
		Singleton::_instance = static_cast<T*>(this);
	}


private:
	static T* _instance;

	inline static T* CreateInstance()
	{
        	return new T();
	}
};

template<typename T>
T* Singleton<T>::_instance = 0;

