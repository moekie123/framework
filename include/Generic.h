#pragma once

// Design Patterns
#include "Composite.h"
#include "Object.h"
#include "Observer.h"
#include "Subject.h"

// Third-Party
#include <rapidjson/document.h>

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

        virtual bool Update( const Generic& _subject ) override;

        virtual bool Update( const IMosquitto& _mqtt, const rapidjson::Document& _jpackage );

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

