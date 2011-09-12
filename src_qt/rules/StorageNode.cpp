#include <QtCore/QString>

#include "StorageNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	StorageNode::StorageNode(const QString& event, const QString& value, MemoryType memory, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memory( memory ),
		_event( event ),
		_value( value ),
		_clearStorage( false )
	{

	}


	/*
		Creates a memory Event and store it in the brain memory
	*/
	void StorageNode::exec()
	{
		// Check if the value and event are valid
		if( _event.isEmpty() || _value.isEmpty() )
		{
			return;
		}

		// Create memory event to add to the memory
		MemoryEvent m( _event, _value );

		_brain->storeToMemory( m, _memory);
	}

	/*

	*/
	void StorageNode::exec( QHash<QString, QString> &variables )
	{
		QString value = _value;
		tagsToValue( value, variables );

		MemoryEvent m( _event, value );

		_brain->storeToMemory( m, _memory);
	}

	/*
		Debug information
	*/
	QString StorageNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Storage event=" + _event + " value=" + _value;

		return info;
	}

	/*!
		Converts XML attributes to a StorageNode
	*/
	StorageNode *StorageNode::fromXML( const QString &qName, const QXmlAttributes &atts, Brain* brain, QObject* parent )
	{
		if( qName.compare( "Storage", Qt::CaseInsensitive ) == 0 )
		{
			QString event = atts.value( "event" );
			QString value = atts.value( "value" );
			MemoryType memory = translateMemoryType( atts.value( "memory" ) );

			return new StorageNode( event, value, memory, brain, parent );

		}
		return NULL;
	}
}
