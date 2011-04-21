#include <QtCore/QString>
#include "Node.h"

namespace CnotiMind
{

	Node::Node(const QString& key, const QString& value):
		_key( key ),
		_value( value )
	{

	}

	const QString& Node::value() const
	{
		return _value;
	}

	const QString& Node::key() const
	{
		return _key;
	}

}
