#include <QtCore/QString>

#include "ConditionDataMiningNode.h"
#include "../Brain.h"


namespace CnotiMind
{

	ConditionDataMiningNode::ConditionDataMiningNode(const QString& key, const QString& value, ConditionNode::ConditionOperator op, ConditionNode::DataMiningOperation dataMiningOperator, Brain::MemoryType memory, Brain* brain, QObject* parent):
		ConditionNode( key, value, op, brain, parent ),
		_dataMiningOperator( dataMiningOperator ),
		_variable( "" ),
		_memory( memory )
	{

	}

	ConditionDataMiningNode::ConditionDataMiningNode(const QString& key, const QString& value, ConditionNode::ConditionOperator op, ConditionNode::DataMiningOperation dataMiningOperator, Brain::MemoryType memory, const QString& variable, Brain* brain, QObject* parent):
		ConditionNode( key, value, op, brain, parent ),
		_dataMiningOperator( dataMiningOperator ),
		_variable( variable ),
		_memory( memory )
	{

	}

	void ConditionDataMiningNode::exec()
	{
		if( isTrue() )
		{
			if( _variable.isEmpty() )
			{
				execChildren();
			}
			else
			{
				QHash<QString,QString> variables;
				variables.insert( _variable, _result );
				execChildren( variables );
			}
		}
	}

	void ConditionDataMiningNode::exec( QHash<QString, QString> &variables )
	{
		if( isTrue() )
		{
			if( !_variable.isEmpty() )
			{
				variables.insert( _variable, _result );
			}
			execChildren( variables );
		}
	}


	const QString& ConditionDataMiningNode::variable() const
	{
		return _variable;
	}

	bool ConditionDataMiningNode::isTrue() const
	{


		switch( _operator )
		{
//			case ConditionOperatorBigger: return e.value() == _valueInt;
//			case ConditionOperatorBiggerOrEqual: return e.value() >= _valueInt;
//			case ConditionOperatorSmaller: return e.value() < _valueInt;
//			case ConditionOperatorSmallerOrEqual: return e.value() <= _valueInt;
//			case ConditionOperatorEqual: return e.value() == _valueInt;
//			case ConditionOperatorDifferent: return e.value() != _valueInt;
		}
		return true;
	}

}
