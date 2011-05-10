#include <QtCore/QString>
#include <QDateTime>

#include "ActionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ActionNode::ActionNode(const QString& name, const QString& value, const QString probability, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_name( name ),
		_value( value ),
		_probability( probability ),
		_probabilityValue( probability.toDouble( &_isProbabilityNumeric ) )
	{

	}

	void ActionNode::exec()
	{
		// if the probability is
		if( _isProbabilityNumeric )
		{
			if( _probabilityValue <= 0 )
			{
				return;
			}
			if( _probabilityValue < 1 )
			{
				// test if it should execute
				if( qrand() * 1.0 / RAND_MAX > _probabilityValue )
				{
					return; // it will not execute
				}
			}
		}
		else
		{
			// if the probability is not a number, return since there are no variables
			// to get the value
			return;
		}

		_brain->executeAction( _name, _value );
	}

	void ActionNode::exec( QHash<QString, QString> &variables )
	{
		// Update the _value
		QString value = _value;
		tagsToValue( value, variables );

		// Test if the value is valid.
		if( !value.isEmpty() )
		{
			_brain->executeAction( _name, value );
		}
	}

	QString ActionNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Action (" + _name + ") value=" + _value;

		return info;
	}

}
