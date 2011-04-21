#if !defined(_MEMORYEVENT_H)
#define _MEMORYEVENT_H

#include <QtCore/QString>
#include <QtCore/QVariant>
#include <ctime>

#include "ObjectToXml.h"

namespace CnotiMind
{

	class Perception;

	class MemoryEvent: public ObjectToXml
	{
	public:

		MemoryEvent( const QString& event, const QVariant& value );
		MemoryEvent( const QString& event, const QVariant& value, time_t time );
		MemoryEvent( const Perception& perception );

		const QVariant& value() const;
		const QString& event() const;
		time_t time() const;

		QString toXml() const;

	protected:
		QString _event;
		QVariant _value;
		time_t _time;
	};

}
#endif  //_MEMORYEVENT_H
