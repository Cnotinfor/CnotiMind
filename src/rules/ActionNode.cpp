#include <QtCore/QString>

#include "ActionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ActionNode::ActionNode(const QString& key, const QString& value, Brain* brain, QObject* parent):
		RuleNode( key, value, brain, parent )
	{

	}

	void ActionNode::exec()
	{

		_brain->executeAction( _key, _value );
	}

	void ActionNode::exec( QHash<QString, QString> &variables )
	{
		_brain->executeAction( _key, _value );
		// TODO, check variables and test if it needs to be replaced in the value.
	}

}
