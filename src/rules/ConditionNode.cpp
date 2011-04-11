#include <QtCore/QString>

#include "ConditionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ConditionNode::ConditionNode(const QString& key, const QString& value, ConditionOperator op, Brain* brain, QObject* parent):
		RuleNode( key, value, brain, parent ),
		_operator( op ),
		_isValueNumeric( false )
	{
		// If not condition operator is set, it uses the Equal Operator
		if(op == ConditionOperatorUndefined)
		{
			_operator = ConditionOperatorEqual;
		}

		// Convert to double
		// If it has sucessefull, the variable _isNumeric is true.
		_valueNumeric = value.toDouble( &_isValueNumeric );
	}

	void ConditionNode::exec()
	{
		// Test if the condition is true. If it is, execute the node
		if( isTrue() )
		{
			execChildren();
		}
	}

	void ConditionNode::exec( QHash<QString,QString>& variables )
	{
		// Test if the condition is true. If it is, execute the node
		if( isTrue() )
		{
			execChildren( variables );
		}
	}

	QString ConditionNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Condition ";

		return info + RuleNode::info(depth);
	}

}
