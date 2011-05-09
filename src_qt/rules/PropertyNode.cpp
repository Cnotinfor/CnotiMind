#include "PropertyNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	PropertyNode::PropertyNode( const QString& key, const QString& value, Brain* brain, QObject* parent ):
		RuleNode( brain, parent ),
		_key( key ),
		_value( value )
	{

	}

	void PropertyNode::exec()
	{
		_brain->_properties.insert( _key, _value );
	}

	void PropertyNode::exec( QHash<QString, QString>& variables )
	{
		// Convert tags that can be in the value of the property
		QString value = _value;
		this->tagsToValue( value, variables );

		_brain->_properties.insert( _key, value );
	}

	QString PropertyNode::info( int depth ) const
	{
		return space(depth) + "Property " + _key + ": " + _value;
	}

}
