#include <QtCore/QString>

#include "MemoryEvent.h"

namespace CnotiMind
{

	/**!

		Creates a memory event with a \a key name and a \a value. The event time
		is the local time.

	*/
	MemoryEvent::MemoryEvent(const QString& key, const QString& value):
		Node( key, value ),
		_time( time() )
	{

	}

	MemoryEvent::MemoryEvent(const QString& key, const QString& value, time_t time):
		Node( key, value ),
		_time( time )
	{

	}

	time_t MemoryEvent::time() const
	{
		return _time;
	}

	const QString& MemoryEvent::key() const
	{
		return _key;
	}

	const QString& MemoryEvent::value() const
	{
		return _value;
	}

}
