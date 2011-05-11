#include <QHashIterator>

#include "ConditionVariableNode.h"


namespace CnotiMind
{

	ConditionVariableNode::ConditionVariableNode( const QString& variable, const QString& value, ConditionOperator op, Brain* brain, QObject* parent ) :
		ConditionNode( variable, value, op, brain, parent )
	{
	}

	void ConditionVariableNode::exec()
	{
		// Does nothing, since this Node, need variables to exec
	}

	void ConditionVariableNode::exec( QHash<QString,QString>& variables )
	{
		if( isTrue( variables ) )
		{
			execChildren( variables );
		}
	}

	/*
		Returns false, since it requires variables to work correctly
	*/
	bool ConditionVariableNode::isTrue()
	{
		return false;
	}

	QString ConditionVariableNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Condition type=Variable";

		return info + RuleNode::info(depth);
	}

	/*
		Test the value of the variable using the conditional operator
	*/
	bool ConditionVariableNode::isTrue( QHash<QString,QString>& variables )
	{
		QHashIterator<QString, QString> it( variables );
		while( it.hasNext() )
		{
			it.next();
			const QString& k = it.key();
			const QString& v = it.value();

			// Test if found the variable
			if( QString::compare( _key, k, Qt::CaseInsensitive ) == 0 )
			{
				// Try to convert the value from the variable to number
				bool ok;
				qreal value = v.toDouble(&ok);

				if( ok ) // if the variable value is a number
				{
					if( _isValueNumeric ) // if the value to compare is a number
					{
						switch( _operator )
						{
							case ConditionOperatorBigger: return _valueNumeric > value;
							case ConditionOperatorBiggerOrEqual: return _valueNumeric >= value;
							case ConditionOperatorSmaller: return _valueNumeric < value;
							case ConditionOperatorSmallerOrEqual: return _valueNumeric <= value;
							case ConditionOperatorEqual: return _valueNumeric == value;
							case ConditionOperatorDifferent: return _valueNumeric != value;
						}
						return false;
					}
					else // if it is not a number, test if it is variable
					{
						QString strValue = _value;
						tagsToValue( strValue, variables ); // convert variable tags to number

						qreal compareValue = strValue.toDouble(&ok);

						if(ok) // if it is number
						{
							switch( _operator )
							{
								case ConditionOperatorBigger: return compareValue > value;
								case ConditionOperatorBiggerOrEqual: return compareValue >= value;
								case ConditionOperatorSmaller: return compareValue < value;
								case ConditionOperatorSmallerOrEqual: return compareValue <= value;
								case ConditionOperatorEqual: return compareValue == value;
								case ConditionOperatorDifferent: return compareValue != value;
							}
							return false;
						}
						// if it is not a number use the code below
					}
				}

				// If one of the value is not a number
				switch( _operator ) // it's a string, just to this 2 operators
				{
					case ConditionOperatorEqual: return QString::compare( _value, v, Qt::CaseInsensitive ) == 0;
					case ConditionOperatorDifferent: return QString::compare( _value, v, Qt::CaseInsensitive ) != 0;
				}
				return false;
			}
		}

		// No equal variables found
		return false;
	}

}
