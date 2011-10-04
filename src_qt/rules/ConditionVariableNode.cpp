#include <QHashIterator>

#include "ConditionVariableNode.h"


namespace CnotiMind
{

	ConditionVariableNode::ConditionVariableNode( const QString& variable, const QString& value, ConditionOperator op, Brain* brain, QObject* parent ) :
		ConditionNode( op, brain, parent ),
		_variable( variable ),
		_value( value ),
		_valueNumeric( value.toInt( &_isValueNumeric ) )
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
			if( _variable.compare( k, Qt::CaseInsensitive ) == 0 )
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
							case ConditionOperatorBigger: return value > _valueNumeric ;
							case ConditionOperatorBiggerOrEqual: return value >= _valueNumeric;
							case ConditionOperatorSmaller: return value < _valueNumeric;
							case ConditionOperatorSmallerOrEqual: return value <= _valueNumeric;
							case ConditionOperatorEqual: return value == _valueNumeric;
							case ConditionOperatorDifferent: return value != _valueNumeric;
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
								case ConditionOperatorBigger: return value > compareValue;
								case ConditionOperatorBiggerOrEqual: return value >= compareValue;
								case ConditionOperatorSmaller: return value < compareValue;
								case ConditionOperatorSmallerOrEqual: return value <= compareValue;
								case ConditionOperatorEqual: return value == compareValue;
								case ConditionOperatorDifferent: return value != compareValue;
							}
							return false;
						}
						// if it is not a number use the code below
					}
				}

				// If one of the value is not a number
				QString strValue = _value;
				tagsToValue( strValue, variables );

				switch( _operator ) // it's a string, just to this 2 operators
				{
					case ConditionOperatorEqual: return QString::compare( strValue, v, Qt::CaseInsensitive ) == 0;
					case ConditionOperatorDifferent: return QString::compare( strValue, v, Qt::CaseInsensitive ) != 0;
				}
				return false;
			}
		}

		// No equal variables found
		return false;
	}

	ConditionVariableNode* ConditionVariableNode::fromXML(const QString &qName, const QXmlAttributes &atts, Brain *brain, QObject *parent)
	{
		if(qName.compare( "Condition", Qt::CaseInsensitive) == 0)
		{
			QString type = atts.value( "type" );
			if( type.compare("Variable", Qt::CaseInsensitive ) == 0 )
			{
				QString key = atts.value( "variable" );
				QString value = atts.value( "compareValue" );
				ConditionOperator op = translateConditionOperator( atts.value( "operator" ) );

				return new ConditionVariableNode( key, value, op, brain, parent );

			}
		}
		return NULL;
	}

}
