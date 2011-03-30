#include <QtCore/QString>

#include "RuleNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	RuleNode::RuleNode( const QString& key, const QString& value, Brain* brain, QObject* parent ):
		Node( key, value ),
		QObject( parent ),
		_brain( brain )
	{
	}


	bool RuleNode::isRoot() const
	{
		return false;
	}

}
