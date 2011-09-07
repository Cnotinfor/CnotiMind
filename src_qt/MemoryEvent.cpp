#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QDateTime>

#include "MemoryEvent.h"
#include "Perception.h"

namespace CnotiMind
{
	MemoryEvent::MemoryEvent():
		_time( QDateTime::currentDateTime().toMSecsSinceEpoch() )
	{

	}

	/**!

		Creates a memory event with a \a eventName. The event time
		is the local time. This event doesn't have any value associated.

	*/
	MemoryEvent::MemoryEvent( const QString& eventName ):
		_eventName( eventName ),
		_value( QVariant() ),
		_time( QDateTime::currentDateTime().toMSecsSinceEpoch() )
	{

	}

	/**!

		Creates a memory event with a \a key name and a \a value. The event time
		is the local time.

	*/
	MemoryEvent::MemoryEvent(const QString& eventName, const QVariant& value):
		_eventName( eventName ),
		_value( value ),
		_time( QDateTime::currentDateTime().toMSecsSinceEpoch() )
	{

	}

	MemoryEvent::MemoryEvent(const QString& eventName, const QVariant& value, qint64 time):
		_eventName( eventName ),
		_value( value ),
		_time( time )
	{

	}

	/*
		Creates a Memory Event based on a Perception.
	*/
	MemoryEvent::MemoryEvent( const Perception& perception ):
		_eventName( perception.name() ),
		_value( perception.value() ),
		_time( QDateTime::currentDateTime().toMSecsSinceEpoch() )
	{

	}

	const QVariant& MemoryEvent::value() const
	{
		return _value;
	}

	const QString& MemoryEvent::event() const
	{
		return _eventName;
	}

	qint64 MemoryEvent::time() const
	{
		return _time;
	}

	QString MemoryEvent::toXml() const
	{
		QString xml;

		xml = "<MemoryEvent ";

		xml += "event=\"" + _eventName + "\"";
		xml += "value=\"" + _value.toString() + "\"";
		xml += "time=\"" + QString::number( _time ) + "\"";

		xml += "</MemoryEvent>";

		return xml;
	}

	/*
		Compare a memory event with a QString
	*/
	bool MemoryEvent::operator ==( const QString& name )
	{
		return QString::compare( _eventName, name, Qt::CaseInsensitive ) == 0;
	}

	/*
		Two memory events are equal if they have the same event name

		If the values of both events are valid, it test also if the value are equal
	*/
	bool MemoryEvent::operator ==( const MemoryEvent& me )
	{
		if( me._value.isValid() && _value.isValid() )
		{
			return (QString::compare( _eventName, me._eventName, Qt::CaseInsensitive ) == 0) &&
				   (QString::compare( _value.toString(), me._value.toString(), Qt::CaseInsensitive ) == 0);
		}

		return QString::compare( _eventName, me._eventName, Qt::CaseInsensitive ) == 0;
	}

}
