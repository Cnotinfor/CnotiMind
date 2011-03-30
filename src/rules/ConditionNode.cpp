#include <QtCore/QString>

#include "ConditionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ConditionNode::ConditionNode(const QString& key, const QString& value, ConditionOperator op, Brain* brain, QObject* parent):
		RuleNode( key, value, brain, parent ),
		_operator( op )
	{

	}

	void ConditionNode::exec()
	{

	}

	RuleNode::RuleNodeTypes ConditionNode::type() const
	{
		return Condition;
	}

}
