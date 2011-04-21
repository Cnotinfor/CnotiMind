#include <QtCore/QString>

#include "ActionNode.h"
#include "../Brain.h"

namespace CnotiMind
{

	ActionNode::ActionNode(const QString& key, const QString& value, Brain* brain, QObject* parent):
		RuleNode( key, value, brain, parent )
	{

	}

	void ActionNode::exec()
	{
		_brain->executeAction( _key, _value );
	}

	void ActionNode::exec( QHash<QString, QString> &variables )
	{
		const QString& value = variableToValue( _value, variables );

		// Test if the value is valid.
		if( !value.isEmpty() )
		{
			_brain->executeAction( _key, value );
		}
	}

	QString ActionNode::info( int depth ) const
	{
		QString info;

		info += space(depth) + "Action (" + _key + ") value=" + _value;

		return info + RuleNode::info(depth);
	}

}
