#include <QtCore/QString>
#include <QtCore/QVariant>

#include "MemoryEvent.h"
#include "Perception.h"

namespace CnotiMind
{

	/**!

		Creates a memory event with a \a key name and a \a value. The event time
		is the local time.

	*/
	MemoryEvent::MemoryEvent(const QString& key, const QVariant& value):
		_event( key ),
		_value( value ),
		_time( time() )
	{

	}

	MemoryEvent::MemoryEvent(const QString& key, const QVariant& value, time_t time):
		_event( key ),
		_value( value ),
		_time( time )
	{

	}

	/*
		Creates a Memory Event based on a Perception.
	*/
	MemoryEvent::MemoryEvent( const Perception& perception ):
		_event( perception.name() ),
		_value( perception.value() ),
		_time( time() )
	{

	}

	const QVariant& MemoryEvent::value() const
	{
		return _value;
	}

	const QString& MemoryEvent::event() const
	{
		return _event;
	}

	time_t MemoryEvent::time() const
	{
		return _time;
	}

	QString MemoryEvent::toXml() const
	{
		QString xml;

		xml = "<MemoryEvent ";

		xml += "event=\"" + _event + "\"";
		xml += "value=\"" + _value.toString() + "\"";
		xml += "time=\"" + QString::number( _time ) + "\"";

		xml += "</MemoryEvent>";

		return xml;
	}
}
