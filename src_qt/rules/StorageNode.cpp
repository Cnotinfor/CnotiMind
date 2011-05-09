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

	StorageNode::StorageNode( bool clear, MemoryType memory, Brain* brain, QObject* parent ):
		RuleNode( brain, parent ),
		_memory( memory ),
		_clearStorage( clear ),
		_event( "" ),
		_value( "" )
	{

	}

	/*
		Creates a memory Event and store it in the brain memory
	*/
	void StorageNode::exec()
	{
		// Test if the node is for clearing the memory
		if( _clearStorage )
		{
			if( _memory == CnotiMind::WorkingMemory )
			{
				_brain->clearWorkingMemory();
			}
			else
			{
				_brain->clearMemory();
			}
			return;
		}

		// If it is not for clearing, check if the value and event are valid
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
		variableToValue( value, variables );

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
}
