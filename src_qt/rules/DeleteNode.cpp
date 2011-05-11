#include "DeleteNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	DeleteNode::DeleteNode(const QString& key, const QString& value, DeletePosition position,
						   MemoryType memory, Brain* brain, QObject* parent ) :
		RuleNode(brain, parent),
		_key( key ),
		_value( value ),
		_memory( memory ),
		_position( position )
	{
	}

	void DeleteNode::exec()
	{
		if(_value.isEmpty())
		{
			_brain->deleteEvent( _key, _position, _memory );
		}
		else
		{
			_brain->deleteEvent( _key, _value, _position, _memory );
		}
	}

	void DeleteNode::exec( QHash<QString, QString>& variables )
	{

		if(_value.isEmpty())
		{
			_brain->deleteEvent( _key, _position, _memory );
		}
		else
		{
			// Test if there are variables in the value
			QString value = _value;
			tagsToValue( value, variables );

			_brain->deleteEvent( _key, value, _position, _memory );
		}
	}

	QString DeleteNode::info( int depth ) const
	{
		return space(depth) + "Delete Node " + _key + ": " + _value + " (" + (_memory == LongTermMemory ? "LTM" : "WM" ) + ")";
	}

}
