#include <QtCore/QString>

#include "ConditionDataMiningNode.h"
#include "../Brain.h"


namespace CnotiMind
{

	ConditionDataMiningNode::ConditionDataMiningNode(const QString& key, const QString& value, ConditionNode::ConditionOperator op, ConditionNode::DataMiningOperation dataMiningOperator, Brain* brain, QObject* parent):
		ConditionNode( key, value, op, brain, parent ),
		_dataMiningOperator( dataMiningOperator )
	{

	}

	ConditionDataMiningNode::ConditionDataMiningNode(const QString& key, const QString& value, ConditionNode::ConditionOperator op, ConditionNode::DataMiningOperation dataMiningOperator, const QString& variable, Brain* brain, QObject* parent):
		ConditionNode( key, value, op, brain, parent ),
		_dataMiningOperator( dataMiningOperator ),
		_variable( variable )
	{

	}

	void ConditionDataMiningNode::exec()
	{

	}

	RuleNode::RuleNodeTypes ConditionDataMiningNode::type() const
	{
		return Condition | DataMining;
	}

	const QString& ConditionDataMiningNode::variable() const
	{
		return _variable;
	}

	bool ConditionDataMiningNode::isTrue() const
	{
		return true;
	}

}
