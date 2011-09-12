#include <QHashIterator>

#include "ConditionPropertyNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ConditionPropertyNode::ConditionPropertyNode( const QString& property, const QString& value, ConditionOperator op, Brain* brain, QObject* parent ) :
		ConditionNode( property, value, op, brain, parent )
	{
	}


	/*
		Test the value of the property using the conditional operator
	*/
	bool ConditionPropertyNode::isTrue()
	{
		QHashIterator<QString, QString> it( _brain->_properties );
		while( it.hasNext() )
		{
			it.next();
			const QString& k = it.key();
			const QString& v = it.value();

			// Test if found the property
			if( _key.compare( k, Qt::CaseInsensitive ) == 0 )
			{
				// Try to convert the value from the variable to number
				bool ok;
				qreal valueNumeric = v.toDouble(&ok);

				if( ok && _isValueNumeric ) // if both values are numbers
				{
					switch( _operator )
					{
						case ConditionOperatorBigger: return _valueNumeric > valueNumeric;
						case ConditionOperatorBiggerOrEqual: return _valueNumeric >= valueNumeric;
						case ConditionOperatorSmaller: return _valueNumeric < valueNumeric;
						case ConditionOperatorSmallerOrEqual: return _valueNumeric <= valueNumeric;
						case ConditionOperatorEqual: return _valueNumeric == valueNumeric;
						case ConditionOperatorDifferent: return _valueNumeric != valueNumeric;
					}
					return false;
				}
				else // If one of the value is not a number
				{
					switch( _operator ) // it's a string, just to this 2 operators
					{
						case ConditionOperatorEqual: return QString::compare( _value, v, Qt::CaseInsensitive ) == 0;
						case ConditionOperatorDifferent: return QString::compare( _value, v, Qt::CaseInsensitive ) != 0;
					}
					return false;
				}
			}
		}

		// No equal variables found
		return false;
	}


	QString ConditionPropertyNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Condition type=Property";

		return info + RuleNode::info(depth);
	}

	ConditionPropertyNode* ConditionPropertyNode::fromXML(const QString &qName, const QXmlAttributes &atts, Brain *brain, QObject *parent)
	{
		if(qName.compare( "Condition", Qt::CaseInsensitive) == 0)
		{
			QString type = atts.value( "type" );
			if( type.compare("Property") == 0 )
			{
				QString property = atts.value( "property" );
				QString value = atts.value( "compareValue" );
				ConditionOperator op = translateConditionOperator( atts.value( "operator" ) );

				return new ConditionPropertyNode( property, value, op, brain, parent );

			}
		}
	}


}
