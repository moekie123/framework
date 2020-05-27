#pragma once

#include <typeinfo>
#include <stdexcept>

// Third-Party
#include <spdlog/spdlog.h>

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
                if ( !IsConstructed() )
                {
                        Singleton::_instance = CreateInstance();
                 }
                return *( Singleton::_instance );
        }

        /**
	 * @brief Configure the singleton with a predefined instance
	 * @param _instance The Pre-Configured Object to store as a Singleton
	 */
        static void Register( T& _instance )
        {
                spdlog::trace( "{} > {}", __PRETTY_FUNCTION__, typeid( T ).name() );

                if ( !IsConstructed() )
                {
                        Singleton::_instance = &_instance;
                        return;
                }

                throw std::invalid_argument( "Singleton: Instance already registerd" );
        }

        /**
	 * @brief Clear the register
	 */
        static void Unregister()
        {
                spdlog::trace( "{} > {}", __PRETTY_FUNCTION__, typeid( T ).name() );

                if ( Singleton::_instance != 0 )
                {
                        delete Singleton::_instance;
                        Singleton::_instance = 0;
                        return;
                }

                spdlog::warn( "Singleton already cleared" );
        }

        /**
	 * @brief Check if instance is already created
	 */
        static bool IsConstructed()
        {
                return ( Singleton::_instance != 0 );
        }

       protected:
        virtual ~Singleton()
        {
                if ( Singleton::_instance != 0 )
                {
                        delete Singleton::_instance;
                }
                Singleton::_instance = 0;
        }

        inline explicit Singleton()
        {
                assert( Singleton::_instance == 0 );
                Singleton::_instance = static_cast<T*>( this );
        }

       private:
        static T* _instance;

        inline static T* CreateInstance()
        {
                spdlog::trace( "{} > {}", __PRETTY_FUNCTION__, typeid( T ).name() );
                return new T();
        }
};

template <typename T>
T* Singleton<T>::_instance = nullptr;
