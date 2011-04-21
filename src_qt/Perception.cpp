#include <QtCore/QString>
#include <QtCore/QVariant>

#include "Perception.h"

namespace CnotiMind
{

	Perception::Perception(const QString& name, const QVariant& value):
		_name( name ),
		_value( value )
	{

	}

	const QString& Perception::name() const
	{
		return _name;
	}

	const QVariant& Perception::value() const
	{
		return _value;
	}

}
