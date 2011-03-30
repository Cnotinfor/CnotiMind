#include <QtCore/QString>
#include <QtCore/QObject>

#include "ConditionPerceptionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ConditionEventNode::ConditionEventNode( const QString& key, const QString& value, ConditionNode::ConditionOperator op, Brain* brain, QObject* parent):
		ConditionNode( key, value, op, brain, parent )
	{

	}

	void ConditionEventNode::exec()
	{

	}

	RuleNode::RuleNodeTypes ConditionEventNode::type() const
	{
		return Condition | Event;
	}

	bool ConditionEventNode::isTrue()
	{
		return true;
	}

}
