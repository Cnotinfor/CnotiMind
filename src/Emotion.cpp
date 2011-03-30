#include <QtCore/QString>
#include "Emotion.h"

namespace CnotiMind
{

	Emotion::Emotion( const QString& key, int value ):
		_key( key ),
		_value( value )
	{

	}

	Emotion::Emotion( const QString& key, int value, int max, int min ):
		_key( key ),
		_value( value ),
		_min( min ),
		_max( max )
	{

	}

	int Emotion::value() const
	{
		return _value;
	}

	const QString& Emotion::key() const
	{
		return _key;
	}

}
