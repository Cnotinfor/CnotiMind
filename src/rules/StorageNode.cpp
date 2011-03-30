#include <QtCore/QString>

#include "StorageNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	StorageNode::StorageNode(const QString& key, const QString& value, Brain::MemoryType memory, Brain* brain, QObject* parent):
		RuleNode( key, value, brain, parent ),
		_memory( memory )
	{

	}

	void StorageNode::exec()
	{

	}

	RuleNode::RuleNodeTypes StorageNode::type() const
	{
		return Storage;
	}

}
