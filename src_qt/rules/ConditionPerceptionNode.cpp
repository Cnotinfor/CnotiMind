#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QListIterator>
#include <QDebug>

#include "ConditionPerceptionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ConditionPerceptionNode::ConditionPerceptionNode( const QString& perception, const QString& value, ConditionOperator op, Brain* brain, QObject* parent):
		ConditionNode( op, brain, parent ),
		_perception( perception ),
		_value( value ),
		_valueNumeric( value.toInt( &_isValueNumeric ) )
	{

	}

	void ConditionPerceptionNode::exec()
	{
		if( isTrue() )
		{
			QHash<QString,QString> variables;

			// get the perception, being handled
			Perception p = _brain->_receivedPerceptions.head();

			variables.insert("[Perception.value]", p.value().toString() );
			execChildren( variables );
		}
	}

	void ConditionPerceptionNode::exec( QHash<QString,QString>& variables )
	{
		if( isTrue() )
		{
			// if the perception value is not in the variables list
			if( ! variables.contains( "[Perception.value]" ) )
			{
				// get the perception, being handled
				Perception p = _brain->_receivedPerceptions.head();

				// Insert the perception value in the variables
				variables.insert("[Perception.value]", p.value().toString() );
			}
			execChildren( variables );
		}
	}

	QString ConditionPerceptionNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Condition type=Perception";

		return info + RuleNode::info(depth);
	}

	/*
		Test if there are perceptions, and test the first queued perception, if it is
		equal to this node perception.

		Optionally the value can be set, and the conditional operator.
	*/
	bool ConditionPerceptionNode::isTrue()
	{
		// Check if there are perceptions to be processed in the brain
		if( !_brain->_receivedPerceptions.isEmpty() )
		{
			// Just test the first perception
			Perception p = _brain->_receivedPerceptions.head();
			// Check if it is the percetion for this Node
			if( _perception.compare( p.name(), Qt::CaseInsensitive ) == 0 )
			{
				if( _value.isEmpty() )
				{
					return true;
				}
				else // test if it should be a perception with a specific value
				{
					bool ok, ok2;
					qreal perceptionValue = p.value().toDouble(&ok);
					qreal nodeValue = _value.toDouble(&ok2);

					if( ok && ok2 )
					{

						switch( _operator )
						{
							case ConditionOperatorBigger: return perceptionValue > nodeValue;
							case ConditionOperatorBiggerOrEqual: return perceptionValue >= nodeValue;
							case ConditionOperatorSmaller: return perceptionValue < nodeValue;
							case ConditionOperatorSmallerOrEqual: return perceptionValue <= nodeValue;
							case ConditionOperatorEqual: return perceptionValue == nodeValue;
							case ConditionOperatorDifferent: return perceptionValue != nodeValue;
						}
						return false;
					}
					else if( p.value().canConvert( QVariant::String ) )
					{
						// If it is a String value, it can only use equal or different operator.
						QString s = p.value().toString();
						switch( _operator )
						{
						case ConditionOperatorEqual:
							return QString::compare( _value, s, Qt::CaseInsensitive) == 0;
						case ConditionOperatorDifferent:
							return QString::compare( _value, s, Qt::CaseInsensitive) != 0;
						}
						return false;
					}
					else
					{
						// The value of the perceptions is not recognized,
						// so this node will return false
						return false;
					}

					// TODO, test the value using the condition Operator
				}
			}
		}

		return false;
	}

	ConditionPerceptionNode* ConditionPerceptionNode::fromXML(const QString &qName, const QXmlAttributes &atts, Brain *brain, QObject *parent)
	{
		if(qName.compare( "Condition", Qt::CaseInsensitive) == 0)
		{
			QString type = atts.value( "type" );
			if( type.compare("Perception", Qt::CaseInsensitive) == 0 )
			{

				QString perception = atts.value( "perception" );
				QString value = atts.value( "value" );
				ConditionOperator op = translateConditionOperator( atts.value( "operator" ) );


				return new ConditionPerceptionNode( perception, value, op, brain, parent );
			}
		}

		return NULL;
	}

}
