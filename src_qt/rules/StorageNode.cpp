#include <QtCore/QString>

#include "StorageNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	StorageNode::StorageNode(const QString& key, const QString& value, MemoryType memory, Brain* brain, QObject* parent):
		RuleNode( key, value, brain, parent ),
		_memory( memory )
	{

	}

	/*
		Creates a memory Event and store it in the brain memory
	*/
	void StorageNode::exec()
	{
		MemoryEvent m( _key, _value );

		_brain->storeToMemory( m, _memory);
	}

	/*

	*/
	void StorageNode::exec( QHash<QString, QString> &variables )
	{
		MemoryEvent m( _key, variableToValue( _value, variables ) );

		_brain->storeToMemory( m, _memory);
	}

	QString StorageNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Storage key=" + _key + " value=" + _value;

		return info + RuleNode::info(depth);
	}
}
