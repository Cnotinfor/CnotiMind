#include <QtCore/QString>

#include "ConditionEmotionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ConditionEmotionNode::ConditionEmotionNode(const QString& emotion, const QString& value, ConditionNode::ConditionOperator op, Brain* brain, QObject* parent):
		ConditionNode( emotion, value, op, brain, parent )
	{

	}

	void ConditionEmotionNode::exec()
	{

	}

	RuleNode::RuleNodeTypes ConditionEmotionNode::type() const
	{
		return Condition | Emotion;
	}

	bool ConditionEmotionNode::isTrue() const
	{
		return true;
	}

}
