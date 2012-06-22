#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QDateTime>

#include "MemoryEvent.h"
#include "Perception.h"

namespace CnotiMind
{
	MemoryEvent::MemoryEvent():
		_time( eventTime() )
	{

	}

	MemoryEvent::MemoryEvent( const QString& key ):
		_event( key ),
		_value( QVariant() ),
		_time( eventTime() )
	{

	}

	/**!

		Creates a memory event with a \a key name and a \a value. The event time
		is the local time.

	*/
	MemoryEvent::MemoryEvent(const QString& key, const QVariant& value):
		_event( key ),
		_value( value ),
		_time( eventTime() )
	{

	}

	MemoryEvent::MemoryEvent(const QString& key, const QVariant& value, qint64 time):
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
		_time( eventTime() )
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

	qint64 MemoryEvent::time() const
	{
		return _time;
	}

	QString MemoryEvent::toXml() const
	{
		QString xml;

		xml = "<MemoryEvent ";

		xml += "event=\"" + _event + "\" ";
		xml += "value=\"" + _value.toString() + "\" ";
		xml += "time=\"" + QString::number( _time ) + "\" ";

		xml += "/>";

		return xml;
	}

	qint64 MemoryEvent::eventTime()
	{
		return QDateTime::currentDateTime().toMSecsSinceEpoch() * 0.001;	// Return in seconds
	}

	/*
		Compare a memory event with a QString
	*/
	bool MemoryEvent::operator ==( const QString& name )
	{
		return  _event.compare( name, Qt::CaseInsensitive ) == 0;
	}

	/*
		Two memory events are equal if they have the same event name

		If the values of both events are valid, it test also if the value are equal
	*/
	bool MemoryEvent::operator ==( const MemoryEvent& me )
	{
		if( me._value.isValid() && _value.isValid() )
		{
			return (QString::compare( _event, me._event, Qt::CaseInsensitive ) == 0) &&
				   (QString::compare( _value.toString(), me._value.toString(), Qt::CaseInsensitive ) == 0);
		}

		return QString::compare( _event, me._event, Qt::CaseInsensitive ) == 0;
	}

	bool operator ==(const MemoryEvent& event, const QString& name)
	{
		return event._event.compare( name, Qt::CaseInsensitive ) == 0;
	}

	bool operator ==(const QString& name, const MemoryEvent& event)
	{
		return operator ==(event, name);
	}
}
