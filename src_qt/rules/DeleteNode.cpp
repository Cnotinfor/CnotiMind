#include "DeleteNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	DeleteNode::DeleteNode(const QString& key, const QString& value, EventPosition position,
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


	DeleteNode *DeleteNode::fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent )
	{
		if( qName.compare( "", Qt::CaseInsensitive ) == 0 )
		{
			QString name = atts.value( "name" );
			QString value = atts.value( "value" );
			EventPosition position = translateEventPosition( atts.value( "position" ) ) ;
			MemoryType memory = translateMemoryType( atts.value( "memory" ) );

			return new DeleteNode( name, value, position, memory, brain, parent );

		}
	}
}
