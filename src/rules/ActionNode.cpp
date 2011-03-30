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
		_brain->_rules;
	}

	RuleNode::RuleNodeTypes ActionNode::type() const
	{
		return Action;
	}

}
