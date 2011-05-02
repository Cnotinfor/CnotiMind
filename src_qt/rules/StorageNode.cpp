#include <QtCore/QString>

#include "StorageNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	StorageNode::StorageNode(const QString& event, const QString& value, MemoryType memory, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_memory( memory ),
		_event( event ),
		_value( value )
	{

	}

	/*
		Creates a memory Event and store it in the brain memory
	*/
	void StorageNode::exec()
	{
		MemoryEvent m( _event, _value );

		_brain->storeToMemory( m, _memory);
	}

	/*

	*/
	void StorageNode::exec( QHash<QString, QString> &variables )
	{
		MemoryEvent m( _event, variableToValue( _value, variables ) );

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
