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

	/*
		Converts text to the conditional operator
	*/
	ConditionNode::ConditionOperator ConditionNode::translateConditionOperator( const QString &text )
	{
		if( text.compare(">") == 0)
		{
			return ConditionOperatorBigger;
		}
		if( text.compare(">=") == 0)
		{
			return ConditionOperatorBiggerOrEqual;
		}
		if( text.compare("<") == 0)
		{
			return ConditionOperatorSmaller;
		}
		if( text.compare("<=") == 0)
		{
			return ConditionOperatorSmallerOrEqual;
		}
		if( text.compare("==") == 0)
		{
			return ConditionOperatorEqual;
		}
		if( text.compare("!=") == 0)
		{
			return ConditionOperatorDifferent;
		}

		return ConditionOperatorUndefined;
	}

	/**
		Convert texto to a Data Mining operator
	*/
	ConditionNode::DataMiningOperation ConditionNode::translateDataMiningOperator( const QString &text )
	{
		if( QString::compare( text, "max" ) == 0 )
		{
			return Max;
		}
		if( QString::compare( text, "min" ) == 0 )
		{
			return Min;
		}
		if( QString::compare( text, "sum" ) == 0 )
		{
			return Sum;
		}
		if( QString::compare( text, "count" ) == 0 )
		{
			return Count;
		}
		if( QString::compare( text, "mean" ) == 0 )
		{
			return Mean;
		}
		if( QString::compare( text, "exists" ) == 0 )
		{
			return Exists;
		}
		if( QString::compare( text, "last" ) == 0 )
		{
			return Last;
		}
		if( QString::compare( text, "first" ) == 0 )
		{
			return First;
		}
		if( QString::compare( text, "duration" ) == 0 )
		{
			return Duration;
		}
		if( QString::compare( text, "time" ) == 0 )
		{
			return Time;
		}
		return Undefined;
	}

}
