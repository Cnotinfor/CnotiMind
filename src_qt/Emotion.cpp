#include <QtCore/QString>
#include <QtGlobal>
#include "Emotion.h"

namespace CnotiMind
{

	Emotion::Emotion():
		_key( "" ),
		_value( 0 ),
		_min( INT_MIN ),
		_max( INT_MAX )
	{

	}

	Emotion::Emotion( const QString& key, qreal value ):
		_key( key ),
		_value( value ),
		_min( INT_MIN ),
		_max( INT_MAX )
	{

	}

	Emotion::Emotion( const QString& key, qreal value, qreal max, qreal min ):
		_key( key ),
		_value( value ),
		_min( min ),
		_max( max )
	{

	}

	qreal Emotion::value() const
	{
		return _value;
	}

	const QString& Emotion::key() const
	{
		return _key;
	}

	qreal Emotion::max()
	{
		return _max;
	}

	qreal Emotion::min()
	{
		return _min;
	}

	/*
		Changes the emotional value.

		Examples. Emotion Max = 10, and Emotion Min = -10
		Current emotional value = 7

		If call setValue(8, 7, 0), the emotional value remain 7, since the parameter max is smaller then the new value

		If call setValue(15, 20, 0), the emotional value changes to 10, since the max emotional value is 10

		Same happens for the minimal value

	*/
	bool Emotion::setValue( qreal newValue, qreal max, qreal min )
	{
		qreal oldValue = _value;

		qreal newMax = qMin( max, _max );
		qreal newMin = qMax( min, _min );

		_value = qBound( newMin, newValue, newMax );

		// Return true if the value changed
		return oldValue != _value;
	}


	/**
		Changes the value of the emotion.
	*/
	bool Emotion::setValue( qreal newValue )
	{
		return setValue( newValue, _max, _min );
	}

	/**
		Add an increment to the value using new max and min.

		If the max and min are higher or lower then the emotion max and min, the emotion
		max and min are used.
	*/
	bool Emotion::addValue( qreal increment, qreal max, qreal min )
	{
		return setValue( _value + increment, max, min);
	}

	/**
		Add an increment to the value
	*/
	bool Emotion::addValue( qreal increment )
	{
		return setValue( _value + increment );
	}

	bool operator==( const Emotion& emotion, const QString& emotionName)
	{
		return QString::compare( emotionName, emotion.key(), Qt::CaseInsensitive ) == 0;
	}

	bool operator==(const QString& emotionName, const Emotion& emotion)
	{
		return QString::compare( emotionName, emotion.key(), Qt::CaseInsensitive ) == 0;
	}

	bool operator==(const Emotion& e1, const Emotion& e2)
	{
		return QString::compare( e1.key(), e2.key(), Qt::CaseInsensitive ) == 0;
	}

	QDataStream& operator<< ( QDataStream & out, const Emotion& e )
	{
		return out << "Emotion: " << e._key << "; value=" << e._value << "; min=" << e._min << "; max=" << e._max;
	}

	QStringList& operator<< ( QStringList& list, const Emotion& e )
	{
		return list << "Emotion: " + e._key + "; value=" + QString::number( e._value ) + "; min=" + QString::number( e._min ) + "; max=" + QString::number( e._max );
	}
}
