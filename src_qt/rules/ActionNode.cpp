#include <QtCore/QString>

#include "ActionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ActionNode::ActionNode(const QString& name, const QString& value, Brain* brain, QObject* parent):
		RuleNode( brain, parent ),
		_name( name ),
		_value( value )
	{

	}

	void ActionNode::exec()
	{
		_brain->executeAction( _name, _value );
	}

	void ActionNode::exec( QHash<QString, QString> &variables )
	{
		const QString& value = variableToValue( _value, variables );

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
