#pragma once

// Design Patterns
#include "Composite.h"
#include "Object.h"
#include "Observer.h"
#include "Subject.h"

class IMosquitto;
/**
 * @brief The (Base) Generic class combines all fundamental design patterns as one object
 */
class Generic : virtual public Object,
                public Composite,
                public Observer,
                public Subject
{
       public:
        Generic();

        virtual ~Generic() = default;

        /**
	 * @brief The callback for the Mosquitto client.
	 * @details, Most of the classes that inherent Generic will be able to talk with Mosquitto.
		     There for this specialized Mosquitto Observer Callback is added.
		     Other call from Subject will still call the Generic Observe::Update
	 * @param _subject The instance that invokes this method
	 * 	TODO Package should be a a RadidJson document
	 * @return True, when Update was succesfull
	 */
        virtual bool Update( const IMosquitto& _mqtt, const std::string& _package );

        /* Observer Methods */
        virtual bool Update( const Generic& _subject ) override;

       private:
        /** 
	 * @brief Required to suppress the "no-virtual-move-assign"-Compiler Warning 
	 */
        Generic& operator=( Generic&& _other )
        {
                return *this;
        }
};

// Interfaces
#include "IMosquitto.h"

